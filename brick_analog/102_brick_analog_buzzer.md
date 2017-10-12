# #102 Buzzer Brick

<center>![](../img/BUZZER102/102.jpg)
<!--COLORME-->

## Overview
圧電ブザーを使ったBrickです。I/Oピンより、鳴らす音や音の長さを制御することができます。

## Connecting
アナログコネクタ(A0〜A5)、またはデジタルコネクタ(2〜13)のいずれかに接続します。今回はD13にBuzzer Brickを、A0には、Angle Brickをつないでください。

![](/img/100_analog/connect/102_buzzer_connect.jpg)

## Schematic
![](/img/100_analog/schematic/102_buzzer.png)

## Sample Code
###PWMによる出力

D12コネクタにBuzzer Brickを接続し、ビープ音を鳴らしています。#104 Angle Brickを使うことにより周波数をかえることができます。
音の波形は矩形波でPWM出力します。マイコンが高速にスイッチングすることにより、特別なコンバータを使わずに周波数や波長が変えやすくモーター制御などによく使われます。highとlowの割合をディーティー比といいます。

PWM出力するためにはTIM(タイマー)を使用します。PWMの周波数は、タイマーつまり、マイコンのクロック周波数に依存します。この周波数をPPL回路やプリスケーラなどで加工してタイマーの周波数に使用します。

STM32CubeMXを起動します。Pinout設定で、USART2,ADC1,TIM3を設定します。
![](../img/BUZZER102/Pinout_Buzzer.png)


TIM3の設定画面で分周する値を決めます。highとLowが等しいディーティー比５０％の128と数値を入力します。プリスケーラは21504です。数値を変更すると、出せる周波数範囲が変わります。

![](../img/BUZZER102/TIM3_Buzzer_Clock.png)

それぞれ選択し以下、設定してきます。
![](../img/BUZZER102/TIM3_SELECT.png)

ADC設定画面です。NVIC Setting（割り込みコントローラ）にチェックインします。
![](../img/BUZZER102/NVIC_Buzzer.png)

クロックの設定画面です。ここでは今回は変更はしません。
![](../img/BUZZER102/Clock_Buzzer.png)


Generatecordeを選択します。すると自動的に初期のコードが生成されます。

maic.cのソースコード抜粋（ヘッダー部分）
```c
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */


#include <stdio.h>
#include <string.h>

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

int a_Value,adc_fin=0;
```

AngleBrickからアナログ値を読み取るコールバック関数です。

```c

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	a_Value=HAL_ADC_GetValue(hadc);
	adc_fin=1;
}

```

pwmを出力する関数です。

```c

void pwmConf(int val)
{
	static int period=-1;
	static int with=-1;
	TIM_OC_InitTypeDef sConfigOC;

		period=val+10;
		with=period/2;

 	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_DeInit(&htim3);
	htim3.Init.Period = period;
	HAL_TIM_PWM_Init(&htim3);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = with;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);

}


```

main関数を以下のように追記してください。

```c

/* USER CODE BEGIN 0 */

char message[15];

int main(void)
{

  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */
	HAL_ADC_Start_IT(&hadc1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		sprintf(message,"%3d\n\r",a_Value>>4);
    HAL_UART_Transmit(&huart2,(uint8_t*)message,strlen(message),0x1111);

			pwmConf(a_Value>>4);

		HAL_Delay(1);
		HAL_ADC_Start_IT(&hadc1);	  
  }
}


```

###ビープ音でドレミを演奏。
BuzzerBrickをD12に差し込み、STM32CubeMXから新たにプロジェクトを立ち上げます。
ピンは、以下のようになります。PA0からPWM出力します。
![](../img/BUZZER102/Pinout_Select_Doremi.png)

クロックを設定します。の内部クロックHSI RCT 16Mhz内部クロックから、PLLを使い逓倍して、Prescalerで分割させ、Timerclocksの周波数を84MHzまで大きくします。
![](../img/BUZZER102/ClockConfing.png)

設定画面に移動してTIM3を選びます。
![](../img/BUZZER102/Config_SELECT.png)

プリスケーラーを５に設定します。
![](../img/BUZZER102/TIM3_prescara.png)

Generatecordeします。


main.cのファイルです。（抜粋）

以下のコードを追記します。valueは幅となります。
ディーティー比は５０％であり、その半分が波長となります。

```c

void soundBeep(uint16_t value)
{
	uint16_t widht;
	TIM_OC_InitTypeDef sConfigOC;

	widht=value/2;

 	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_DeInit(&htim3);
	htim3.Init.Period = value;
	HAL_TIM_PWM_Init(&htim3);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = widht;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);

}

```

main関数は以下のようにします。前に、タイマークロックは８４MHZ、プリスケーラは５に設定したことによりそれぞれの音階の周期を求めます。

```c

int main(void)
{

  /* USER CODE BEGIN 1 */
uint16_t codeF[8]={0xFAD5,0xDF78,0xC716,0xBBEA,0xA769,0x9525,0x84E0,0x7D6A};
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */

	MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
		for (int i=0;i<8;i++){
			soundBeep(codeF[i]);
			HAL_Delay(1500);
		}

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}


```

## 構成Parts
- 圧電ブザー

## GitHub
