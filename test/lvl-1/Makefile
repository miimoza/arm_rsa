CC := arm-none-eabi-gcc
LD := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
CFLAGS := -Os -gdwarf-2 -mthumb -fno-builtin -mcpu=cortex-m4 -Wall -std=c99 -ffunction-sections -fdata-sections -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize -fverbose-asm
LDFLAGS := -mcpu=cortex-m4 -mthumb -nostartfiles  -Wl,-gc-sections -Tnf401re.ld -L. --specs=nano.specs
SRC := init.c main.c
OBJ := $(SRC:.c=.o)
BIN := lvl1.bin
ELF := $(BIN:.bin=.elf)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(ELF): $(OBJ)
	$(LD) $^ $(LDFLAGS) -o $@

%bin: %elf
	$(OBJCOPY) -O binary -S $< $@

all: $(BIN)

clean:
	rm -f $(OBJ) $(ELF) $(BIN)

.PHONY: all clean
.DEFAULT_GOAL = all
