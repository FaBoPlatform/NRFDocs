# #113 IR Receiver Brick

<center>![](../img/IR_RECEIVER113/113.png)
<!--COLORME-->

## Overview
フォトトランジスタを使った赤外線受信Brickです。

I/Oピンから赤外線受信のON/OFFを取得することができます。

## Connecting

アナログコネクタ(A0〜A5)、またはデジタルコネクタ(2〜13)のいずれかに接続します。
![](/img/100_analog/connect/113_ir_receiver_connect.jpg)

## Parts Specification
| Document |
|:--|
| [L-51ROPT1D1](http://akizukidenshi.com/catalog/g/gI-04211/) |
| [2SC1815L-Y](http://akizukidenshi.com/catalog/g/gI-06475/) |

## Schematic
![](/img/100_analog/schematic/113_ir_receive.png)

## Sample Code
###ピン変化割り込み処理によるLED点灯
A1コネクタに赤外線受信Brick、A0コネクタにLED Brickを接続し、赤外線を受信したらLEDを発光させます。
リモコン等をIR_RECEIVE Brickにリモコンに送信します。赤外線の受光があったとき、電圧がHighとなります。LowからHigh(raise)があったとき、LED Brickを点灯させます。

STM32CubeMXを起動して、UART2をAnsynchrous,PA0は、OUTPUT,PA1 EXT1とします。
<center>![](../img/IR_RECEIVER113/Pinout113.png)
ClockSettingsは、以下のようにします。
<center>![](../img/IR_RECEIVER113/ClockSettings.png)
NVIC_Settingsは以下のように設定します。
<center>![](../img/IR_RECEIVER113/NVIC_Settings.png)

下記のコードが自動で生成されます。ClockSettingsで決めた設定が繁栄され、HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);が追加され割り込み処理は優先順位が決められます。

main.c
```c
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

```

main.cファイルの一部
GPIOの初期化には、EXTI interruptの初期化も行われる。GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;とし、電圧上昇を処理のトリガーとする。
```c
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

}
```


32f4xx_it.cファイル（一部）
32f4xx_it.cに下記を追記します。今回main.cのmaic関数には、追記しません。
```c
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

	 if(__HAL_GPIO_EXTI_GET_FLAG(GPIO_PIN_1)){
		 GPIOA -> ODR = 0x01;   
		 }

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}
```
リセットボタンを押すと、起動します。

##赤外線リモコンから出すパルス波形の幅を取得。
赤外線のリモコンをご用意ください。リモコンから出す赤外線のhighとlowの時間の長さを調べます。
A0にIR ReceiverBrickを接続して、STM32CubeMXを起動してください。

ピン設定します。
<center>![](../img/IR_RECEIVER113/PinoutConfigration_width.png)
下記のように TimerClocksがともに84Mhzになるように、クロックを設定します。
<center>![](../img/IR_RECEIVER113/ClockConfigration_width.png)
TIM1をえらんで
<center>![](../img/IR_RECEIVER113/Configration_width.png)
プリスケーラ値は８３に設定します。ピリオドは65535にします。
<center>![](../img/IR_RECEIVER113/TIM_Configration_width.png)
CodeGenerateを実行ます。

main.cファイルの一部
stdio.hとstring.hをインクルード

```c
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
```

main関数
波形の立ち上がりを待ってタイマーをスタートさせ、立下りでタイマーをストップさせます。

```c
int main(void)
{

  /* USER CODE BEGIN 1 */

		char str[15];
		int timevalue_low,timevalue_high;



  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//受信待機メッセージ
			sprintf(str,"Listening OK\n\r");
			HAL_UART_Transmit(&huart2,(uint8_t *)&str,strlen(str),0010);

		while(1){
			//立ち上がりするのを待機
			while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_SET);
			while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET);

			//タイマーをスタートさせる。
			htim1.Instance->CNT=0;
			HAL_TIM_Base_Start(&htim1);

			//立ち下げを待機
			while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_SET);

			//タイマーをストップさせ、時刻を記録。
			timevalue_high = htim1.Instance->CNT;
			HAL_TIM_Base_Stop(&htim1);

			//タイマーのカウントを０にして、タイマー再スタート。
			htim1.Instance->CNT=0;
			HAL_TIM_Base_Start(&htim1);

			//立ち上げするのを待機
			while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET);

			//タイマーをストップさせる時刻を記録。
			timevalue_low = htim1.Instance->CNT;
			HAL_TIM_Base_Stop(&htim1);

			//結果をターミナルに出力。
			sprintf(str,"high:%d.%03d\n\r",(timevalue_high/1000),(timevalue_high%1000));
			HAL_UART_Transmit(&huart2,(uint8_t *)&str,strlen(str),0010);

			sprintf(str,"low:%d.%03d\n\r",(timevalue_low/1000),(timevalue_low%1000));
			HAL_UART_Transmit(&huart2,(uint8_t *)&str,strlen(str),0010);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		}

  }
  /* USER CODE END 3 */

}

```


リセットボタンを押すと起動します。赤外線リモコンからIR ReceiverBrickに向かって送信してみてください。
Teratermを起動して、確認してください。



## 構成Parts
- 赤外線フォトトランジスタ

## GitHub
