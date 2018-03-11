# Visual Studioの開発環境の構築

# CommandLineTool Install

コマンドラインツールを使えば、ターミナルからJ-Linkの設定なしでファームウェアを簡単に焼くことができます。

## J-Linkのインストール

https://www.segger.com/downloads/jlink より J-Link Software and Documentation pack for macOSをダウンロードし、インストールします。

![](/img/osx/osx001.png)

![](/img/osx/osx002.png)

![](/img/osx/osx003.png)

## gcc-armのインストール

> brew cask install gcc-arm-embedded

## nrf5x-toolsのインストール

> brew cask install nrf5x-command-line-tools

## Visual Studio Codeのインストール

https://code.visualstudio.com/ からVisual Studio Codeをダウンロードし、インストールします。

![](/img/osx/osx004.png)

## フォルダの作成

config, nRF51822, nRF52832, srcフォルダを作成します。

![](/img/osx/osx005.png)

## taskの作成

[Shift + Command + P]を実行し、タスク構成の作成を選択します。

![](/img/osx/osx006.png)

![](/img/osx/osx007.png)

![](/img/osx/osx008.png)

![](/img/osx/osx009.png)


./src/.vscode/tasks.json
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build 51",
            "type": "shell",
            "command": "make -C ../nRF51822/gcc/ DEBUG=YES",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        },
        {
            "label": "Clean 51",
            "type": "shell",
            "command": "make -C ../nRF51822/gcc/ clean",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        },
        {
            "label": "Flash 51",
            "type": "shell",
            "command": "make -C ../nRF51822/gcc/ flash",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        },
        {
            "label": "Flash SoftDevice 51",
            "type": "shell",
            "command": "make -C ../nRF51822/gcc/ flash_softdevice",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        },
        {
            "label": "Run GDB-Server 51",
            "type": "shell",
            "command": "JLinkGDBServer -select USB -device nrf51822 -if SWD -speed 1000 -noir",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        },
        {
            "label": "Build 52",
            "type": "shell",
            "command": "make -C ../nRF52832/gcc/ DEBUG=YES",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        },
        {
            "label": "Clean 52",
            "type": "shell",
            "command": "make -C ../nRF52832/gcc/ clean",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        },
        {
            "label": "Flash 52",
            "type": "shell",
            "command": "make -C ../nRF52832/gcc/ flash",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        },
        {
            "label": "Flash SoftDevice 52",
            "type": "shell",
            "command": "make -C ./nRF52832/gcc/ flash_softdevice",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        },
        {
            "label": "Run GDB-Server 52",
            "type": "shell",
            "command": "JLinkGDBServer -select USB -device nrf52 -if SWD -speed 1000 -noir",
            "group": "build",
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            }
        }
    ]
}
```

## gcc関連ファイル(nRF51821)

nRF51822/gcc/Makefile
```c
PROJECT_NAME     := BLETest
TARGETS          := $(PROJECT_NAME)
OUTPUT_DIRECTORY := _build

SDK_ROOT := ./../../../Test/sdk12
PROJ_DIR := ../..

$(OUTPUT_DIRECTORY)/$(TARGETS).out: \
  LINKER_SCRIPT  := gcc_nrf51.ld
# Source files common to all targets
SRC_FILES += \
  $(SDK_ROOT)/components/toolchain/gcc/gcc_startup_nrf51.S \
  $(SDK_ROOT)/components/toolchain/system_nrf51.c \
  $(PROJ_DIR)/src/main.c \
  $(PROJ_DIR)/src/beacon.c \
  $(SDK_ROOT)/components/libraries/timer/app_timer.c \
  $(SDK_ROOT)/components/libraries/util/app_error.c \
  $(SDK_ROOT)/components/libraries/util/app_error_weak.c \
  $(SDK_ROOT)/components/libraries/util/app_util_platform.c \
  $(SDK_ROOT)/components/softdevice/common/softdevice_handler/softdevice_handler.c \
  $(SDK_ROOT)/components/drivers_nrf/clock/nrf_drv_clock.c \
  $(SDK_ROOT)/components/drivers_nrf/common/nrf_drv_common.c \
  $(SDK_ROOT)/components/ble/common/ble_advdata.c \

# Include folders common to all targets
INC_FOLDERS += \
  $(PROJ_DIR)/config \
  $(PROJ_DIR)/src \
  $(SDK_ROOT)/components/device \
  $(SDK_ROOT)/components/toolchain \
  $(SDK_ROOT)/components/toolchain/cmsis/include \
  $(SDK_ROOT)/examples/bsp \
  $(SDK_ROOT)/components/drivers_nrf/hal \
  $(SDK_ROOT)/components/libraries/button \
  $(SDK_ROOT)/components/libraries/util \
  $(SDK_ROOT)/components/softdevice/s130/headers \
  $(SDK_ROOT)/components/libraries/timer \
  $(SDK_ROOT)/components/drivers_nrf/delay \
  $(SDK_ROOT)/components/softdevice/common/softdevice_handler \
  $(SDK_ROOT)/components/libraries/log \
  $(SDK_ROOT)/components/libraries/log/src \
  $(SDK_ROOT)/components/drivers_nrf/clock \
  $(SDK_ROOT)/components/drivers_nrf/common \
  $(SDK_ROOT)/components/ble/common \

# Libraries common to all targets
LIB_FILES += \

# C flags common to all targets
CFLAGS += -DBOARD_CUSTOM 
CFLAGS += -DSOFTDEVICE_PRESENT
CFLAGS += -DNRF51
CFLAGS += -DS130
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -DNRF51822
CFLAGS += -DNRF_SD_BLE_API_VERSION=2
CFLAGS += -DBLE_ADVERTISING_ENABLED
CFLAGS += -DBSP_DEFINES_ONLY
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs
CFLAGS +=  -Wall -Werror -O3
CFLAGS += -mfloat-abi=soft
# keep every function in separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums 
# generate dependency output file
CFLAGS += -MP -MD

ifeq ($(DEBUG),yes)
CFLAGS += -O -g3
else
CFLAGS += -O3
endif

# C++ flags common to all targets
CXXFLAGS += \

# Assembler flags common to all targets
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DBOARD_CUSTOM 
ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DNRF51
ASMFLAGS += -DS130
ASMFLAGS += -DBLE_STACK_SUPPORT_REQD
ASMFLAGS += -DNRF51822
ASMFLAGS += -DNRF_SD_BLE_API_VERSION=2

# Linker flags
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys

.PHONY: $(TARGETS) default all clean help flash 
# Default target - first one defined
default: $(TARGETS)

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo 	$(TARGETS)
	@echo 	flash_softdevice

TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc

include $(TEMPLATE_PATH)/Makefile.common
$(foreach target, $(TARGETS), $(call define_target, $(target)))
-include $(foreach target, $(TARGETS), $($(target)_dependencies))

# Flash the program
flash: $(OUTPUT_DIRECTORY)/$(TARGETS).hex
	@echo Flashing: $<
	nrfjprog --program $< -f nrf51 --sectorerase
	nrfjprog --reset -f nrf51
# Flash softdevice
flash_softdevice:
	@echo Flashing: s130_nrf51_2.0.1_softdevice.hex
	nrfjprog --program $(SDK_ROOT)/components/softdevice/s130/hex/s130_nrf51_2.0.1_softdevice.hex -f nrf51 --chiperase 
	nrfjprog --reset -f nrf51
```

nRF51822/gcc/gcc_nrf51.ld
```c
/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x1b000, LENGTH = 0x25000
  RAM (rwx) :  ORIGIN = 0x20001FE8, LENGTH = 0x6018
}

SECTIONS
{
  .fs_data :
  {
    PROVIDE(__start_fs_data = .);
    KEEP(*(.fs_data))
    PROVIDE(__stop_fs_data = .);
  } > RAM
} INSERT AFTER .data;

INCLUDE "nrf5x_common.ld"
```
## gcc関連ファイル(nRF51821)

nRF51832/gcc/Makefile
```c
PROJECT_NAME     := BLETest
TARGETS          := $(PROJECT_NAME)
OUTPUT_DIRECTORY := _build

SDK_ROOT := ./../../../Test/sdk12
PROJ_DIR := ../..

$(OUTPUT_DIRECTORY)/$(TARGETS).out: \
  LINKER_SCRIPT  := gcc_nrf52.ld
# Source files common to all targets
SRC_FILES += \
  $(SDK_ROOT)/components/toolchain/gcc/gcc_startup_nrf52.S \
  $(SDK_ROOT)/components/toolchain/system_nrf52.c \
  $(PROJ_DIR)/src/main.c \
  $(PROJ_DIR)/src/beacon.c \
  $(SDK_ROOT)/components/libraries/timer/app_timer.c \
  $(SDK_ROOT)/components/libraries/util/app_error.c \
  $(SDK_ROOT)/components/libraries/util/app_error_weak.c \
  $(SDK_ROOT)/components/libraries/util/app_util_platform.c \
  $(SDK_ROOT)/components/softdevice/common/softdevice_handler/softdevice_handler.c \
  $(SDK_ROOT)/components/drivers_nrf/clock/nrf_drv_clock.c \
  $(SDK_ROOT)/components/drivers_nrf/common/nrf_drv_common.c \
  $(SDK_ROOT)/components/ble/common/ble_advdata.c \

# Include folders common to all targets
INC_FOLDERS += \
  $(PROJ_DIR)/config \
  $(PROJ_DIR)/src \
  $(SDK_ROOT)/components/device \
  $(SDK_ROOT)/components/toolchain \
  $(SDK_ROOT)/components/toolchain/cmsis/include \
  $(SDK_ROOT)/examples/bsp \
  $(SDK_ROOT)/components/drivers_nrf/hal \
  $(SDK_ROOT)/components/libraries/button \
  $(SDK_ROOT)/components/libraries/util \
  $(SDK_ROOT)/components/softdevice/s132/headers \
  $(SDK_ROOT)/components/libraries/timer \
  $(SDK_ROOT)/components/drivers_nrf/delay \
  $(SDK_ROOT)/components/softdevice/common/softdevice_handler \
  $(SDK_ROOT)/components/libraries/log \
  $(SDK_ROOT)/components/libraries/log/src \
  $(SDK_ROOT)/components/drivers_nrf/clock \
  $(SDK_ROOT)/components/drivers_nrf/common \
  $(SDK_ROOT)/components/ble/common \

# Libraries common to all targets
LIB_FILES += \

# C flags common to all targets
CFLAGS += -DNRF52
CFLAGS += -DBOARD_CUSTOM 
CFLAGS += -DNRF52832
CFLAGS += -DNRF52_PAN_64
CFLAGS += -DNRF52_PAN_12
CFLAGS += -DNRF52_PAN_15
CFLAGS += -DNRF52_PAN_58
CFLAGS += -DNRF52_PAN_55
CFLAGS += -DNRF52_PAN_54
CFLAGS += -DNRF52_PAN_31
CFLAGS += -DNRF52_PAN_30
CFLAGS += -DNRF52_PAN_51
CFLAGS += -DNRF52_PAN_36
CFLAGS += -DNRF52_PAN_53
CFLAGS += -DS132
CFLAGS += -DCONFIG_GPIO_AS_PINRESET
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -DNRF_SD_BLE_API_VERSION=3
CFLAGS += -DSWI_DISABLE0
CFLAGS += -DNRF52_PAN_20
CFLAGS += -DSOFTDEVICE_PRESENT
CFLAGS += -DNRF52_PAN_62
CFLAGS += -DNRF52_PAN_63
CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb -mabi=aapcs
CFLAGS +=  -Wall -Werror
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# keep every function in separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums 
# generate dependency output file
CFLAGS += -MP -MD

ifeq ($(DEBUG),yes)
CFLAGS += -O -g
else
CFLAGS += -O3
endif

# C++ flags common to all targets
CXXFLAGS += \

# Assembler flags common to all targets
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DNRF52
ASMFLAGS += -DBOARD_PCA10040
ASMFLAGS += -DNRF52832
ASMFLAGS += -DNRF52_PAN_64
ASMFLAGS += -DNRF52_PAN_12
ASMFLAGS += -DNRF52_PAN_15
ASMFLAGS += -DNRF52_PAN_58
ASMFLAGS += -DNRF52_PAN_55
ASMFLAGS += -DNRF52_PAN_54
ASMFLAGS += -DNRF52_PAN_31
ASMFLAGS += -DNRF52_PAN_30
ASMFLAGS += -DNRF52_PAN_51
ASMFLAGS += -DNRF52_PAN_36
ASMFLAGS += -DNRF52_PAN_53
ASMFLAGS += -DS132
ASMFLAGS += -DCONFIG_GPIO_AS_PINRESET
ASMFLAGS += -DBLE_STACK_SUPPORT_REQD
ASMFLAGS += -DNRF_SD_BLE_API_VERSION=3
ASMFLAGS += -DSWI_DISABLE0
ASMFLAGS += -DNRF52_PAN_20
ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DNRF52_PAN_62
ASMFLAGS += -DNRF52_PAN_63

# Linker flags
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m4
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys

.PHONY: $(TARGETS) default all clean help flash  flash_softdevice
# Default target - first one defined
default: $(TARGETS)

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo 	$(TARGETS)
	@echo 	flash_softdevice

TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc

include $(TEMPLATE_PATH)/Makefile.common
$(foreach target, $(TARGETS), $(call define_target, $(target)))
-include $(foreach target, $(TARGETS), $($(target)_dependencies))

# Flash the program
# Flash the program
flash: $(OUTPUT_DIRECTORY)/$(TARGETS).hex
	@echo Flashing: $<
	nrfjprog --program $< -f nrf52 --sectorerase
	nrfjprog --reset -f nrf52
# Flash softdevice
flash_softdevice:
	@echo Flashing: s132_nrf52_3.0.0_softdevice.hex
	nrfjprog --program $(SDK_ROOT)/components/softdevice/s132/hex/s132_nrf52_3.0.0_softdevice.hex -f nrf52 --chiperase 
	nrfjprog --reset -f nrf52

```

./nRF52832/gcc_nrf52.ld
```c
/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x1f000, LENGTH = 0x61000
  RAM (rwx) :  ORIGIN = 0x20002128, LENGTH = 0xDED8
}

SECTIONS
{
  .fs_data :
  {
    PROVIDE(__start_fs_data = .);
    KEEP(*(.fs_data))
    PROVIDE(__stop_fs_data = .);
  } > RAM
} INSERT AFTER .data;

INCLUDE "nrf5x_common.ld"
```

## Configフォルダ

![](/img/osx/osx010.png)

sdk_config.h を https://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v12.x.x/ よりダウンロードしたSDKより、configフォルダにコピーします。

config/custom_board.h
```c
// Akabeacon Dev Board

#ifndef CUSTOM_BOARD_H
#define CUSTOM_BOARD_H

#define LED_START      18
#define LED_0          18
#define LED_1          19
#define LED_STOP       19

#define BSP_LED_0      LED_0
#define BSP_LED_1      LED_1

#define BUTTON_START   16
#define BUTTON_0       16
#define BUTTON_1       17
#define BUTTON_STOP    17
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BSP_BUTTON_0   BUTTON_0
#define BSP_BUTTON_1   BUTTON_1

#define BUTTONS_NUMBER 2
#define LEDS_NUMBER    2
#define BUTTONS_MASK   0x00030000
#define LEDS_MASK      0x000C0000
#define LEDS_INV_MASK  0

#define BSP_BUTTON_0_MASK (1<<BSP_BUTTON_0)
#define BSP_BUTTON_1_MASK (1<<BSP_BUTTON_1)

#define BUTTONS_LIST { BUTTON_0, BUTTON_1 }
#define LEDS_LIST { LED_0, LED_1 }

#define BSP_LED_0_MASK    (1<<LED_0)
#define BSP_LED_1_MASK    (1<<LED_1)

//#define RX_PIN_NUMBER  11
//#define TX_PIN_NUMBER  9
#define RX_PIN_NUMBER  9
#define TX_PIN_NUMBER  11
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define HWFC           false

#define SPIS_MISO_PIN  20    // SPI MISO signal. 
#define SPIS_CSN_PIN   21    // SPI CSN signal. 
#define SPIS_MOSI_PIN  22    // SPI MOSI signal. 
#define SPIS_SCK_PIN   23    // SPI SCK signal. 

#define SPIM0_SCK_PIN       23u     /**< SPI clock GPIO pin number. */
#define SPIM0_MOSI_PIN      20u     /**< SPI Master Out Slave In GPIO pin number. */
#define SPIM0_MISO_PIN      22u     /**< SPI Master In Slave Out GPIO pin number. */
#define SPIM0_SS_PIN        21u     /**< SPI Slave Select GPIO pin number. */

#define SPIM1_SCK_PIN       29u     /**< SPI clock GPIO pin number. */
#define SPIM1_MOSI_PIN      24u     /**< SPI Master Out Slave In GPIO pin number. */
#define SPIM1_MISO_PIN      28u     /**< SPI Master In Slave Out GPIO pin number. */
#define SPIM1_SS_PIN        25u     /**< SPI Slave Select GPIO pin number. */

// serialization APPLICATION board

// UART
// this configuration works with the SPI wires setup
#define SER_APP_RX_PIN              20     // UART RX pin number.
#define SER_APP_TX_PIN              22     // UART TX pin number.
#define SER_APP_CTS_PIN             23     // UART Clear To Send pin number.
#define SER_APP_RTS_PIN             21     // UART Request To Send pin number.

// SPI
#if 0
#define SER_APP_SPIM0_SCK_PIN       20     // SPI clock GPIO pin number.
#define SER_APP_SPIM0_MOSI_PIN      17     // SPI Master Out Slave In GPIO pin number
#define SER_APP_SPIM0_MISO_PIN      16     // SPI Master In Slave Out GPIO pin number
#define SER_APP_SPIM0_SS_PIN        21     // SPI Slave Select GPIO pin number
#define SER_APP_SPIM0_RDY_PIN       19     // SPI READY GPIO pin number
#define SER_APP_SPIM0_REQ_PIN       18     // SPI REQUEST GPIO pin number
#else
#define SER_APP_SPIM0_SCK_PIN       23     // SPI clock GPIO pin number.
#define SER_APP_SPIM0_MOSI_PIN      20     // SPI Master Out Slave In GPIO pin number
#define SER_APP_SPIM0_MISO_PIN      22     // SPI Master In Slave Out GPIO pin number
#define SER_APP_SPIM0_SS_PIN        21     // SPI Slave Select GPIO pin number
#define SER_APP_SPIM0_RDY_PIN       25     // SPI READY GPIO pin number
#define SER_APP_SPIM0_REQ_PIN       24     // SPI REQUEST GPIO pin number
#endif

// serialization CONNECTIVITY board

// UART
#if 0
#define SER_CON_RX_PIN              22    // UART RX pin number.
#define SER_CON_TX_PIN              20    // UART TX pin number.
#define SER_CON_CTS_PIN             21    // UART Clear To Send pin number. Not used if HWFC is set to false.
#define SER_CON_RTS_PIN             23    // UART Request To Send pin number. Not used if HWFC is set to false.
#else
// this configuration works with the SPI wires setup
#define SER_CON_RX_PIN              20    // UART RX pin number.
#define SER_CON_TX_PIN              22    // UART TX pin number.
#define SER_CON_CTS_PIN             21    // UART Clear To Send pin number. Not used if HWFC is set to false.
#define SER_CON_RTS_PIN             23    // UART Request To Send pin number. Not used if HWFC is set to false.
#endif

//SPI
#if 0
#define SER_CON_SPIS_SCK_PIN        20    // SPI SCK signal.
#define SER_CON_SPIS_MISO_PIN       16    // SPI MISO signal.
#define SER_CON_SPIS_MOSI_PIN       17    // SPI MOSI signal.
#define SER_CON_SPIS_CSN_PIN        21    // SPI CSN signal.
#define SER_CON_SPIS_RDY_PIN        19     // SPI READY GPIO pin number.
#define SER_CON_SPIS_REQ_PIN        18     // SPI REQUEST GPIO pin number.
#else
#define SER_CON_SPIS_SCK_PIN        23    // SPI SCK signal.
#define SER_CON_SPIS_MOSI_PIN       22    // SPI MOSI signal.
#define SER_CON_SPIS_MISO_PIN       20    // SPI MISO signal.
#define SER_CON_SPIS_CSN_PIN        21    // SPI CSN signal.
#define SER_CON_SPIS_RDY_PIN        25     // SPI READY GPIO pin number.
#define SER_CON_SPIS_REQ_PIN        24     // SPI REQUEST GPIO pin number.
#endif

#define SER_CONN_ASSERT_LED_PIN     LED_0

#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}

#endif
```





