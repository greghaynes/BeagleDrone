CC=gcc
CFLAGS=-Wall -g -I../
LDFLAGS=-lm
UNIT_CFLAGS=$(CFLAGS) -Iunit/
FUNC_CFLAGS=$(CFLAGS) -Ifunctional/

test: test_unit test_functional

test_unit: test_buffer test_state test_quaternion test_communication test_command test_motorhelp

test_functional: test_commands

test_buffer:
	$(CC) $(UNIT_CFLAGS) ../app/buffer.c test_help.c unit/test_buffer.c -o unit/test_buffer $(LDFLAGS) && \
	./unit/test_buffer

test_state:
	$(CC) $(UNIT_CFLAGS) ../app/mathhelp.c ../app/quaternion.c ../app/state.c test_help.c unit/test_state.c -o unit/test_state $(LDFLAGS) && \
	./unit/test_state

test_quaternion:
	$(CC) $(UNIT_CFLAGS) ../app/mathhelp.c ../app/quaternion.c test_help.c unit/test_quaternion.c -o unit/test_quaternion $(LDFLAGS) && \
	./unit/test_quaternion

test_communication:
	$(CC) $(UNIT_CFLAGS) ../app/afproto.c ../app/buffer.c ../app/crc16.c ../app/communication.c test_help.c unit/test_communication.c -o unit/test_communication $(LDFLAGS) && \
	./unit/test_communication

test_command:
	$(CC) $(UNIT_CFLAGS) ../app/command.c unit/test_command.c test_help.c -o unit/test_command $(LDFLAGS) && \
	./unit/test_command

test_motorhelp:
	$(CC) $(UNIT_CFLAGS) ../app/motorhelp.c unit/test_motorhelp.c test_help.c -o unit/test_motorhelp $(LDFLAGS) && \
	./unit/test_motorhelp

test_commands:
	$(CC) $(FUNC_CFLAGS) ../app/mathhelp.c ../app/quaternion.c ../app/state.c test_help.c functional/test_commands.c -o functional/test_commands $(LDFLAGS) && \
	./functional/test_commands
