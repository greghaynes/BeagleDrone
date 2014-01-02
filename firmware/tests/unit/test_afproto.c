#include "tests/test_help.h"
#include "app/afproto.h"
#include "app/buffer.h"
#include "app/crc16.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int escaped_bytes_in(const char *str) {
    int ret = 0;
    while(*str) {
        if(*str == AFPROTO_START_BYTE || *str == AFPROTO_ESC_BYTE ||
           *str == AFPROTO_END_BYTE)
            ++ret;
        ++str;
    }

    return ret;
}

void test_pop_no_end_byte(void) {
    char in_data[512];
    char out_data[256];

    RingBuffer rb_in;
    Buffer output;

    RingBufferInit(&rb_in, in_data, 512);
    BufferInit(&output, out_data, 256);

    RingBufferPushString(&rb_in, "\x7d\x48\x65\x6c\x6c\x6f\xd6\xcb");
    assert(!afproto_ringbuffer_pop_frame(&rb_in, &output));
    assert(output.used == 0);
}

void test_pop_frame(void) {
    char in_data[512];
    char out_data[256];

    RingBuffer rb_in;
    Buffer output;

    RingBufferInit(&rb_in, in_data, 512);
    BufferInit(&output, out_data, 256);

    RingBufferPushString(&rb_in, "\x7d\x48\x65\x6c\x6c\x6f\xd6\xcb\x7f");

    assert(!afproto_ringbuffer_pop_frame(&rb_in, &output));
    assert(output.used == strlen("Hello"));
    assert(!strcmp(out_data, "Hello"));
}

void test_push_frame(void) {
    char in_data[256];
    char out_data[512];
    const char *test_str = "Hello";
    RingBuffer rb_in, rb_out;

    RingBufferInit(&rb_in, in_data, 256);
    RingBufferInit(&rb_out, out_data, 512);

    RingBufferPushString(&rb_in, test_str);
    afproto_ringbuffer_push_frame(&rb_out, &rb_in);

    int framed_len = strlen(test_str) + escaped_bytes_in(test_str) + 4;

    assert(RingBufferSize(&rb_out) == framed_len);
    assert(out_data[0] == AFPROTO_START_BYTE);
    assert(out_data[framed_len - 1] == AFPROTO_END_BYTE);
    unsigned short framed_crc = *(
            (unsigned short*)(out_data + framed_len - 3));
    assert(framed_crc == crc16_buff(test_str, strlen(test_str)));
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Push frame", test_push_frame },
        { "Pop frame", test_pop_frame },
        { "Pop no end byte", test_pop_no_end_byte },
        { 0, 0 }
    };

    run_tests(tests);
    return 0;
}

