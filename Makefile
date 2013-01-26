ARMGNU_PREFIX=arm-none-eabi
CFLAGS=-Wall -Werror -O2 -I. -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -fdata-sections -nostartfiles -ffreestanding
CC=$(ARMGNU_PREFIX)-gcc

OBJS=kernel/main.o\
	kernel/boot/startup.o\
	kernel/boot/init.o\
	kernel/boot/isr.o\
	kernel/timers/dmtimer.o\
	kernel/cp15.o\
	kernel/cpu.o\
	kernel/interrupt.o

all: boot.bin

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.bin: $(OBJS)
	$(ARMGNU_PREFIX)-ld -nostartfiles -T kernel/boot/linker.ld $(OBJS) -o boot.elf
	$(ARMGNU_PREFIX)-objcopy boot.elf -O srec boot.srec
	$(ARMGNU_PREFIX)-objcopy boot.elf -O binary boot.bin

clean:
	rm *.elf kernel/*.o kernel/boot/*.o
