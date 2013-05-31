TARGET = test
MMCU = atmega16
F_CPU = 8000000UL

CC = avr-gcc
CFLAGS = -O2 -g -Wall
SRC = $(shell ls *.c) 
INC = $(shell find .  -name '*.[h]')

TARGET_P = m16
HFUSE = 0x99
# external clock, no divide by 8
LFUSE = 0xcf
# internal 8MHz
#LFUSE = 0xe1
MMCU_N = 2

CDEFINES = -DMMCU=$(MMCU_N) -DF_CPU=$(F_CPU)

# Reglas
########

# Reglas para compilar y generar el binario para subir al target
all: hex

elf: $(SRC) $(INC)
	$(CC) $(CDEFINES) -mmcu=$(MMCU) $(CFLAGS) -o $(TARGET).elf $(SRC)
	avr-objdump -h -S $(TARGET).elf > $(TARGET).lst
	avr-size -d $(TARGET).elf
	avr-size -d --format=avr --mcu=$(MMCU) $(TARGET).elf

hex: elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex


# Reglas para programar el target
program: hex
	avrdude -c usbtiny -p $(TARGET_P) -U f:w:$(TARGET).hex

program_dw: elf
	avarice -w -j usb --erase --program --file $(TARGET).elf

fuse:
	avrdude -c usbtiny -p $(TARGET_P) -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m

clean:
	rm -rf $(TARGET).hex $(TARGET).elf $(TARGET).lst
