CC=gcc
CFLAGS=-Wall -g -lm -I../
UNIT_CFLAGS=$(CFLAGS) -Iunit/

test: test_buffer test_state test_quaternion test_communication test_command test_motorhelp

# UNIT
test_buffer:
	$(CC) $(UNIT_CFLAGS) ../app/buffer.c test_help.c unit/test_buffer.c -o unit/test_buffer
	./unit/test_buffer

test_state:
	$(CC) $(UNIT_CFLAGS) ../app/mathhelp.c ../app/quaternion.c ../app/state.c test_help.c unit/test_state.c -o unit/test_state -lm
	./unit/test_state

test_quaternion:
	$(CC) $(UNIT_CFLAGS) ../app/mathhelp.c ../app/quaternion.c test_help.c unit/test_quaternion.c -o unit/test_quaternion -lm
	./unit/test_quaternion

test_communication:
	$(CC) $(UNIT_CFLAGS) ../app/afproto.c ../app/buffer.c ../app/crc16.c ../app/communication.c test_help.c unit/test_communication.c -o unit/test_communication
	./unit/test_communication

test_command:
	$(CC) $(UNIT_CFLAGS) ../app/command.c unit/test_command.c test_help.c -o unit/test_command
	./unit/test_command

test_motorhelp:
	$(CC) $(UNIT_CFLAGS) ../app/motorhelp.c unit/test_motorhelp.c test_help.c -o unit/test_motorhelp
	./unit/test_motorhelp

