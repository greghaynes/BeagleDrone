#include "afproto.h"
#include "buffer.h"
#include "crc16.h"

int afproto_byte_needs_escaping(char ch) {
    return ch == AFPROTO_START_BYTE ||
           ch == AFPROTO_ESC_BYTE ||
           ch == AFPROTO_END_BYTE;
}

int afproto_ringbuffer_pop_frame(RingBuffer *input, Buffer *output) {
    char ch, prev_chars[2];
    int prev_escape = 0, in_iter_cnt = 0;

    // Pop until we find a start byte;
    while(RingBufferPop(input, &ch) &&
            ch != AFPROTO_START_BYTE);

    // We never saw a start byte
    if(ch != AFPROTO_START_BYTE)
        return 0;

    while(RingBufferPop(input, &ch)) {
        if (ch == AFPROTO_END_BYTE)
            break;

        if(prev_escape) {
            ch ^= 0x20;
            prev_escape = 0;
        }

        if(ch == AFPROTO_ESC_BYTE)
            prev_escape = 1;
        else {
            if(in_iter_cnt >= 2 && !BufferAppend(output, prev_chars[0])) {
                // We ran out of space!

                // TODO return data to original buffer
                return 1;
            }

            prev_chars[0] = prev_chars[1];
            prev_chars[1] = ch;
            ++in_iter_cnt;
        }
    }

    if(ch != AFPROTO_END_BYTE)
        BufferClear(output);
    else {
        unsigned short crc = crc16_buff(output->data, in_iter_cnt - 2);
        if(crc != *(unsigned short*)prev_chars)
            BufferClear(output);
    }
    return !RingBufferIsEmpty(input);
}

void afproto_ringbuffer_push_frame(RingBuffer *output,
                                   const char *data,
                                   unsigned int size) {
    // TODO check avail space in output
    const char *input_iter = data;
    const char *input_end = data + size;
    char ch;
    short crc = 0;

    RingBufferPush(output, AFPROTO_START_BYTE);

    while(input_iter != input_end && (ch = *(input_iter++))) {
        if (afproto_byte_needs_escaping(ch)) {
            RingBufferPush(output, AFPROTO_ESC_BYTE);
            crc = crc16_floating(ch, crc);
            RingBufferPush(output, ch ^ 0x20);
        } else {
            crc = crc16_floating(ch, crc);
            RingBufferPush(output, ch);
        }
    }

    // Write the CRC
    char *crc_str = (char*)&crc;
    int i;
    for(i=0;i < 2;++i) {
        if(afproto_byte_needs_escaping(crc_str[i])) {
            RingBufferPush(output, AFPROTO_ESC_BYTE);
            RingBufferPush(output, crc_str[i] ^ 0x20);
        } else
            RingBufferPush(output, crc_str[i]);
    }

    RingBufferPush(output, AFPROTO_END_BYTE);
}

