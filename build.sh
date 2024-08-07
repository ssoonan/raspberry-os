aarch64-linux-gnu-gcc -c boot.S -o boot.o
aarch64-linux-gnu-gcc -c lib.S -o liba.o
aarch64-linux-gnu-gcc -std=c99 -ffreestanding -mgeneral-regs-only  -c main.c
aarch64-linux-gnu-gcc -std=c99 -ffreestanding -mgeneral-regs-only  -c uart.c
aarch64-linux-gnu-ld -nostdlib -T link.lds -o kernel boot.o main.o liba.o uart.o
aarch64-linux-gnu-objcopy -O binary kernel kernel8.img