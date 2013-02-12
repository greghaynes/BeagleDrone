import serial

AFPROTO_START_BYTE = 0x7d
AFPROTO_END_BYTE = 0x7d
AFPROTO_ESCAPE_BYTE = 0x7e

def main():
    s = serial('/dev/ttyUSB0')
    buff = ''
    while ch = s.read():
        if ch == AFPROTO_END_BYTE:
            decoded = afproto_decode(buff)
            if decoded != None:
                got_command(decoded)
                buff = ''
                continue
        buff += ch

