ARMGNU_PREFIX=arm-none-eabi
CPP_ARGS=-Wall -Werror -O2 -I. -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -ffunction-sections -fdata-sections -nostartfiles -ffreestanding
AS_ARGS=-Wall -Werror -O0 -I. -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -ffunction-sections -fdata-sections -nostartfiles -ffreestanding
CPP_CMD=$(ARMGNU_PREFIX)-g++ $(CPP_ARGS)
AS_CMD=$(ARMGNU_PREFIX)-gcc $(AS_ARGS)

all: boot.bin

kernel/start.o: kernel/start.cpp
	$(CPP_CMD) kernel/start.cpp -c -o kernel/start.o

kernel/interrupt.o: kernel/interrupt.cpp
	$(CPP_CMD) kernel/interrupt.cpp -c -o kernel/interrupt.o

kernel/boot/irq.o: kernel/boot/irq.cpp
	$(CPP_CMD) kernel/boot/irq.cpp -c -o kernel/boot/irq.o

kernel/boot/isr.o: kernel/boot/isr.S
	$(AS_CMD) kernel/boot/isr.S -c -o kernel/boot/isr.o

kernel/boot/startup.o: kernel/boot/startup.cpp
	$(CPP_CMD) kernel/boot/startup.cpp -c -o kernel/boot/startup.o

boot.bin: kernel/start.o kernel/interrupt.o kernel/boot/irq.o kernel/boot/isr.o kernel/boot/startup.o
	$(ARMGNU_PREFIX)-ld -nostartfiles -T kernel/boot/linker.ld kernel/interrupt.o kernel/boot/irq.o kernel/boot/isr.o kernel/boot/startup.o kernel/start.o -o boot.elf
	$(ARMGNU_PREFIX)-objcopy boot.elf -O srec boot.srec
	$(ARMGNU_PREFIX)-objcopy boot.elf -O binary boot.bin

clean:
	rm *.elf kernel/*.o kernel/boot/*.o
