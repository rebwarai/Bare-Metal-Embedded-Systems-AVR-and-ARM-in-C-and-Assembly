MCU = atmega2560
PORT = COM4
BAUD = 115200
SRC = blink.asm
TARGET = blink

AS = avr-as
LD = avr-ld
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

ASFLAGS = -mmcu=$(MCU)
LDFLAGS = -m avr6 -Ttext=0x0000
OBJFLAGS = -O ihex

all: $(TARGET).hex

$(TARGET).o: $(SRC)
	$(AS) $(ASFLAGS) -o $@ $<

$(TARGET).elf: $(TARGET).o
	$(LD) $(LDFLAGS) -o $@ $<

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) $(OBJFLAGS) $< $@

upload: $(TARGET).hex
	$(AVRDUDE) -D -p $(MCU) -c wiring -P $(PORT) -b $(BAUD) -U flash:w:$<

clean:
	del $(TARGET).o $(TARGET).elf $(TARGET).hex

.PHONY: all clean upload