# ---------------------------------------------------------
#  @rebwar_ai
# ---------------------------------------------------------
MCU = atmega2560            # Target microcontroller (Arduino Mega 2560)
F_CPU = 16000000UL          # CPU frequency (16 MHz)
BAUD = 115200               # Baud rate for uploading via bootloader
PORT = COM5                 # Serial port on Windows (e.g., COM5)
SRC = blink.c               # Source file
TARGET = blink              # Output file name (without extension)

# ---------------------------------------------------------
# ⚙️ Toolchain Configuration
# ---------------------------------------------------------
CC = avr-gcc                # AVR C compiler
OBJCOPY = avr-objcopy       # Converts ELF → HEX
AVRDUDE = avrdude           # Upload tool

# ---------------------------------------------------------
# 🏗️ Compiler Flags
# ---------------------------------------------------------
# -mmcu  : specify microcontroller
# -DF_CPU: define CPU frequency
# -Os    : optimize for size
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

# ---------------------------------------------------------
# 🎯 Default Target
# ---------------------------------------------------------
all: $(TARGET).hex

# ---------------------------------------------------------
# 🧩 Step 1: Compile and link → ELF file
# ---------------------------------------------------------
$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

# ---------------------------------------------------------
# 🧩 Step 2: Convert ELF → HEX
# ---------------------------------------------------------
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# ---------------------------------------------------------
# 🚀 Upload to Arduino Mega 2560
# ---------------------------------------------------------
# -D            : skip chip erase
# -p $(MCU)     : target MCU
# -c wiring     : use Arduino bootloader protocol
# -P $(PORT)    : serial port
# -b $(BAUD)    : baud rate
# -U flash:w:$< : write HEX to flash memory
upload: $(TARGET).hex
	$(AVRDUDE) -D -p $(MCU) -c wiring -P $(PORT) -b $(BAUD) -U flash:w:$<

# ---------------------------------------------------------
# 🧹 Clean build files (Windows uses "del")
# ---------------------------------------------------------
clean:
	del $(TARGET).elf $(TARGET).hex
