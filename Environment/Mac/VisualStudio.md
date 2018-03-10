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

## tasks.json

.vscode/tasks.json
```json
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the ocumentation about the tasks.json format
    "version": "0.1.0",
    "command": "sh",
    "isShellCommand": true,
    "args": ["-c"],
    "showOutput": "always",
    "suppressTaskName": true,
    "tasks": [
    {
        "isBuildCommand": true,
        "taskName": "Build 51",
        "args": ["make -C ./nRF51822/gcc/ DEBUG=yes"]
    },
    {
        "taskName": "Clean 51",
        "args": ["make -C ./nRF51822/gcc/ clean"]
    },
    {
        "taskName": "Flash 51",
        "args": ["make -C ./nRF51822/gcc/ flash"]
    },
    {
        "taskName": "Flash SoftDevice 51",
        "args": ["make -C ./nRF51822/gcc/ flash_softdevice"]
    },
    {
        "taskName": "Run GDB-Server 51",
        "args": ["JLinkGDBServer -select USB -device nrf51822 -if SWD -speed 1000 -noir"]
    },
    {
        "taskName": "Build 52",
        "args": ["make -C ./nRF52832/gcc/ DEBUG=yes"]
    },
    {
        "taskName": "Clean 52",
        "args": ["make -C ./nRF52832/gcc/ clean"]
    },
    {
        "taskName": "Flash 52",
        "args": ["make -C ./nRF52832/gcc/ flash"]
    },
    {
        "taskName": "Flash SoftDevice 52",
        "args": ["make -C ./nRF52832/gcc/ flash_softdevice"]
    },
    {
        "taskName": "Run GDB-Server 52",
        "args": ["JLinkGDBServer -select USB -device nrf52 -if SWD -speed 1000 -noir"]
    }
  ]
}
```

## gcc関連ファイル(nRF51821)

nRF51822/gcc/Makefile
```c
PROJECT_NAME     := ibeacon9sec
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
PROJECT_NAME     := ibeacon9sec
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



