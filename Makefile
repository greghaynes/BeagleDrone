ARMGNU_PREFIX=arm-none-eabi

all: boot.bin

kernel/main.o: kernel/main.cpp
	$(ARMGNU_PREFIX)-g++ kernel/main.cpp -c -o kernel/main.o

kernel/boot/boot.o: kernel/boot/boot.s
	$(ARMGNU_PREFIX)-as kernel/boot/boot.s -o kernel/boot/boot.o

boot.bin: kernel/boot/boot.o kernel/main.o
	$(ARMGNU_PREFIX)-ld -T kernel/boot/linker.ld kernel/boot/boot.o kernel/main.o -o boot.elf
	$(ARMGNU_PREFIX)-objcopy boot.elf -O srec boot.srec
	$(ARMGNU_PREFIX)-objcopy boot.elf -O binary boot.bin

clean:
	rm *.elf kernel/*.o kernel/boot/*.o
