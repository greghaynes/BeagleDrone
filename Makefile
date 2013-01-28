ARMGNU_PREFIX=arm-none-eabi
CFLAGS=-Wall -Werror -O2 -I. -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -fdata-sections -nostartfiles -ffreestanding
CC=$(ARMGNU_PREFIX)-gcc
LDFLAGS=-e Entry -u Entry -u __aeabi_uidiv -u __aeabi_idiv -nostartfiles --gc-sections

OBJS=kernel/boot/startup.o\
	kernel/boot/init.o\
	kernel/boot/isr.o\
	kernel/drivers/cp15.o\
    kernel/drivers/uart_irda_cir.o\
	kernel/drivers/dmtimer.o\
	kernel/cpu.o\
	kernel/interrupt.o\
    utils/uartStdio.o\
    app/main.o

all: boot.bin

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.bin: $(OBJS)
	$(ARMGNU_PREFIX)-ld $(LDFLAGS) -T kernel/boot/linker.ld $(OBJS) -o boot.elf
	$(ARMGNU_PREFIX)-objcopy boot.elf -O srec boot.srec
	$(ARMGNU_PREFIX)-objcopy boot.elf -O binary boot.bin

clean:
	rm $(OBJS) boot.elf boot.srec boot.bin
