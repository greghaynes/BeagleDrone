ARMGNU_PREFIX=arm-none-eabi

boot.bin: kernel/boot/boot.s
	$(ARMGNU_PREFIX)-as kernel/boot/boot.s -o kernel/boot/boot.o
	$(ARMGNU_PREFIX)-g++ kernel/main.cpp -c -o kernel/main.o
	$(ARMGNU_PREFIX)-ld -T kernel/boot/linker.ld kernel/boot/boot.o kernel/main.o -o boot.elf
