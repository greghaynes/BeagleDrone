#include "afproto_ringbuffer.h"

void afproto_ringbuffer_pop_frame(RingBuffer *input, Buffer *output) {
    char ch;
    int prev_escape = 0, pushed_cnt;

    // Pop until we find a start byte;
    while(RingBufferPop(input, &ch) &&
            ch != AFPROTO_START_BYTE);

    // We never saw a start byte
    if(ch != AFPROTO_START_BYTE)
        return;

    while(RingBufferPop(input, &ch)) {
        if(prev_escape) {
            ch ^= 0x20;
            prev_escape = 0;
        }

        if(ch == AFPROTO_ESC_BYTE) {
            prev_escape = 1;
        } else {
            if(!BufferPush(out, ch)) {
                // We ran out of space!

                // TODO return data to original buffer
                return;
            }

            if(ch == AFPROTO_END_BYTE)
                break;
        }
    }
}

