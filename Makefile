ARMGNU_PREFIX=arm-none-eabi
CPP_ARGS=-Wall -Werror -O2 -I. -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -fdata-sections -nostartfiles -ffreestanding
CC_CMD=$(ARMGNU_PREFIX)-gcc $(CPP_ARGS)

all: boot.bin

kernel/main.o: kernel/main.c
	$(CC_CMD) kernel/main.c -c -o kernel/main.o

kernel/cpu.o: kernel/cpu.c
	$(CC_CMD) kernel/cpu.c -c -o kernel/cpu.o

kernel/interrupt.o: kernel/interrupt.c
	$(CC_CMD) kernel/interrupt.c -c -o kernel/interrupt.o

kernel/boot/init.o: kernel/boot/init.S
	$(CC_CMD) kernel/boot/init.S -c -o kernel/boot/init.o

kernel/boot/cp15.o: kernel/boot/cp15.S
	$(CC_CMD) kernel/boot/cp15.S -c -o kernel/boot/cp15.o

kernel/boot/isr.o: kernel/boot/isr.S
	$(CC_CMD) kernel/boot/isr.S -c -o kernel/boot/isr.o

kernel/boot/startup.o: kernel/boot/startup.c
	$(CC_CMD) kernel/boot/startup.c -c -o kernel/boot/startup.o

kernel/timers/dmtimer.o: kernel/timers/dmtimer.c
	$(CC_CMD) kernel/timers/dmtimer.c -c -o kernel/timers/dmtimer.o

boot.bin: kernel/main.o kernel/cpu.o kernel/interrupt.o kernel/boot/startup.o kernel/boot/init.o kernel/boot/cp15.o kernel/boot/isr.o kernel/boot/startup.o kernel/timers/dmtimer.o
	$(ARMGNU_PREFIX)-ld -nostartfiles -T kernel/boot/linker.ld kernel/main.o kernel/cpu.o kernel/interrupt.o kernel/boot/startup.o kernel/boot/init.o kernel/boot/cp15.o kernel/boot/isr.o kernel/timers/dmtimer.o -o boot.elf
	$(ARMGNU_PREFIX)-objcopy boot.elf -O srec boot.srec
	$(ARMGNU_PREFIX)-objcopy boot.elf -O binary boot.bin

clean:
	rm *.elf kernel/*.o kernel/boot/*.o
