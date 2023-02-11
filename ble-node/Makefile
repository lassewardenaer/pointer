# Toolchain and board information
TOOLCHAIN = GCC
BOARD = NINA_B3

# Path to the nRF5 SDK
SDK_ROOT = nRF5_SDK_17.1.0_ddde560

# Path to the SoftDevice binary
SOFTDEVICE = $(SDK_ROOT)/components/softdevice/s140/hex/s140_nrf52_6.1.0_softdevice.hex

# Path to the linker script
LINKER_SCRIPT = $(SDK_ROOT)/components/toolchain/gcc/nrf52.ld

# Source files
SRCS = src/$(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Compiler and linker flags
CFLAGS = -Wall -Werror -Os -g3 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -march=armv7-m -mtune=cortex-m4 -DNRF52 -DNRF52840_XXAA
CFLAGS += -DBOARD_$(BOARD) -DSOFTDEVICE_PRESENT -DNRF_SD_BLE_API_VERSION=6
CFLAGS += -I$(SDK_ROOT)/components/toolchain/gcc
CFLAGS += -I$(SDK_ROOT)/components/ble/ble_services/ble_ots_c
CFLAGS += -I$(SDK_ROOT)/components/softdevice/s140/headers/nrf52

LDFLAGS = -L$(SDK_ROOT)/components/toolchain/gcc -T$(LINKER_SCRIPT)
LDFLAGS += -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16

# Programmer settings
PROGRAMMER = JLINK
DEVICE = NRF52840_XXAA

# Target rule
all: app.hex

app.hex: app.out
	@echo "Generating HEX file"
	@$(SDK_ROOT)/components/toolchain/bin/arm-none-eabi-objcopy -O ihex app.out app.hex

app.out: $(OBJS) $(SOFTDEVICE)
	@echo "Linking objects"
	@$(SDK_ROOT)/components/toolchain/bin/arm-none-eabi-gcc $(LDFLAGS) -o app.out $(OBJS) $(SOFTDEVICE)

%.o: %.c
	@echo "Compiling $<"
	@$(SDK_ROOT)/components/toolchain/bin/arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

# Program the board
program: app.hex
	@echo "Programming the board"
	@$(SDK_ROOT)/components/toolchain/bin/JLinkExe -device $(DEVICE) -

