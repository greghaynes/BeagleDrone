#include "tests/test_help.h"
#include "app/afproto.h"
#include "app/buffer.h"

#include <stdio.h>
#include <assert.h>

void test_push_frame(void) {
    char in_data[256];
    char out_data[512];
    RingBuffer rb_in, rb_out;
    BufferInit(&rb_in, in_data, 256);
    RingBufferInit(&rb_out, out_data, 512);

    afproto_ringbuffer_push_frame(&rb_out, &rb_in);
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Push frame", test_push_frame },
        { 0, 0 }
    };

    run_tests(tests);
    return 0;
}

