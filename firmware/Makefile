ARMGNU_PREFIX=arm-none-eabi
ARM_TOOLS_DIR=$(HOME)/Tools/toolchains/arm-cs-tools

CFLAGS=-mcpu=cortex-a8 -Dgcc -Wall -Werror -O2 -I. -fdata-sections -funsigned-char -ffunction-sections -g -Dam335x
CC=$(ARMGNU_PREFIX)-gcc
LDFLAGS=-static -e Entry -u Entry -u __aeabi_uidiv -u __aeabi_idiv -nostartfiles --gc-sections -g
LD_LIBS=-L$(ARM_TOOLS_DIR)/lib/gcc/arm-none-eabi/4.6.3 -lgcc -L$(ARM_TOOLS_DIR)/arm-none-eabi/lib -lg -lc -lm

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
	app/commands/nav.o\
	app/crc16.o\
	app/afproto.o\
	app/buffer.o\
	app/communication.o\
	app/command.o\
	app/log.o\
	app/motorcontrol.o\
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

test: test_buffer test_state test_quaternion test_communication test_command

test_buffer:
	gcc -Wall -g -lm -I. app/buffer.c tests/test_help.c tests/test_buffer.c -o tests/test_buffer
	./tests/test_buffer

test_state:
	gcc -Wall -g -I. app/mathhelp.c app/quaternion.c app/state.c tests/test_help.c tests/test_state.c -o tests/test_state -lm
	./tests/test_state

test_quaternion:
	gcc -g -I. app/mathhelp.c app/quaternion.c tests/test_help.c tests/test_quaternion.c -o tests/test_quaternion -lm
	./tests/test_quaternion

test_communication:
	gcc -g -lm -I. app/afproto.c app/buffer.c app/crc16.c app/communication.c tests/test_help.c tests/test_communication.c -o tests/test_communication
	./tests/test_communication

test_command:
	gcc -g -I. app/command.c tests/test_command.c tests/test_help.c -o tests/test_command
	./tests/test_command

clean:
	rm $(OBJS) boot.elf boot.srec boot.bin
