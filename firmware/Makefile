ARMGNU_PREFIX=arm-none-eabi
ARM_TOOLS_DIR=$(HOME)/Tools/toolchains/arm-cs-tools

CFLAGS=-mcpu=cortex-a8 -Dgcc -Wall -Werror -O2 -I. -fdata-sections -funsigned-char -ffunction-sections -g -Dam335x
CC=$(ARMGNU_PREFIX)-gcc
LDFLAGS=-static -e Entry -u Entry -u __aeabi_uidiv -u __aeabi_idiv -nostartfiles --gc-sections -g
LD_LIBS=-lgcc -lg -lc -lm

OBJS=kernel/boot/startup.o\
	kernel/boot/init.o\
	kernel/boot/isr.o\
	kernel/platform/beaglebone/dmtimer.o\
	kernel/platform/beaglebone/hsi2c.o\
	kernel/platform/beaglebone/pwmss.o\
	kernel/drivers/cp15.o\
	kernel/drivers/dmtimer.o\
	kernel/drivers/ehrpwm.o\
	kernel/drivers/hsi2c.o\
	kernel/drivers/uart.o\
	kernel/drivers/uart_irda_cir.o\
	kernel/cpu.o\
	kernel/interrupt.o\
	kernel/sysdelay.o\
	utils/delay.o\
	app/afproto.o\
	app/commands/nav.o\
	app/crc16.o\
	app/buffer.o\
	app/communication.o\
	app/command.o\
	app/control.o\
	app/log.o\
	app/motorcontrol.o\
	app/motorhelp.o\
	app/imusensors.o\
	app/state.o\
	app/quaternion.o\
	app/mathhelp.o\
	app/main.o

all: boot.bin

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.bin: $(OBJS)
	$(ARMGNU_PREFIX)-ld $(LDFLAGS) -T kernel/boot/linker.ld $(OBJS) -o boot.elf $(LD_LIBS)
	$(ARMGNU_PREFIX)-objcopy boot.elf -O srec boot.srec
	$(ARMGNU_PREFIX)-objcopy boot.elf -O binary boot.bin

clean:
	rm $(OBJS) boot.elf boot.srec boot.bin
