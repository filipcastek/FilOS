C_SOURCES=$(wildcard *.c)
OBJ=$(C_SOURCES:.c=.o)

CC=i686-elf-gcc
LD=i686-elf-ld
CFLAGS=-ffreestanding -m32

all: kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.bin: $(OBJ)
	$(LD) -T linker.ld -o $@ $(OBJ)

clean:
	rm -f *.o kernel.bin
