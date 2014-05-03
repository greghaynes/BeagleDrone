CC=gcc
CFLAGS=-Wall -Werror -fdata-sections -funsigned-char -ffunction-sections -g -I../
LDFLAGS=-lm
UNIT_CFLAGS=$(CFLAGS) -Iunit/
FUNC_CFLAGS=$(CFLAGS) -Ifunctional/

test: test_unit test_functional

test_unit:\
	test_afproto\
	test_buffer\
	test_ahrs\
	test_quaternion\
	test_communication\
	test_command\
	test_motorhelp

test_functional: test_boot test_commands

test_afproto:
	$(CC) $(UNIT_CFLAGS) ../app/afproto.c ../app/buffer.c ../app/crc16.c \
	    test_help.c unit/test_afproto.c -o unit/test_afproto $(LDFLAGS) && \
	./unit/test_afproto

test_buffer:
	$(CC) $(UNIT_CFLAGS) ../app/buffer.c test_help.c unit/test_buffer.c \
	    -o unit/test_buffer $(LDFLAGS) && \
	./unit/test_buffer

test_ahrs:
	$(CC) $(UNIT_CFLAGS) ../app/mathhelp.c ../app/quaternion.c ../app/ahrs.c \
		test_help.c unit/test_ahrs.c -o unit/test_state $(LDFLAGS) && \
	./unit/test_state

test_quaternion:
	$(CC) $(UNIT_CFLAGS) ../app/mathhelp.c ../app/quaternion.c test_help.c \
		unit/test_quaternion.c -o unit/test_quaternion $(LDFLAGS) && \
	./unit/test_quaternion

test_communication:
	$(CC) $(UNIT_CFLAGS) ../app/afproto.c ../app/buffer.c ../app/crc16.c \
		../app/communication.c test_help.c unit/test_communication.c \
	    -o unit/test_communication $(LDFLAGS) && \
	./unit/test_communication

test_command:
	$(CC) $(UNIT_CFLAGS) ../app/command.c unit/test_command.c test_help.c \
		-o unit/test_command $(LDFLAGS) && \
	./unit/test_command

test_motorhelp:
	$(CC) $(UNIT_CFLAGS) ../app/motorhelp.c unit/test_motorhelp.c test_help.c \
		-o unit/test_motorhelp $(LDFLAGS) && \
	./unit/test_motorhelp

test_boot:
	$(CC) $(FUNC_CFLAGS) ../app/afproto.c ../app/buffer.c ../app/command.c \
		../app/commands/nav.c ../app/communication.c ../app/crc16.c \
		../app/log.c ../app/mathhelp.c ../app/quaternion.c ../app/ahrs.c \
		mock/uart_driver.c test_help.c functional/test_boot.c \
	    ../glue/communication.c -o functional/test_boot $(LDFLAGS) && \
	./functional/test_boot

test_commands:
	$(CC) $(FUNC_CFLAGS) ../app/afproto.c ../app/buffer.c ../app/command.c \
		../app/commands/nav.c ../app/communication.c ../app/crc16.c \
		../app/log.c ../app/mathhelp.c ../app/quaternion.c ../app/ahrs.c \
		../glue/communication.c mock/uart_driver.c test_help.c \
	    functional/test_commands.c -o functional/test_commands $(LDFLAGS) && \
	./functional/test_commands
