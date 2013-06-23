#include "tests/test_help.h"
#include "app/buffer.h"

#include <string.h>
#include <assert.h>

void test_buffer_append(void) {
    Buffer b;
    char data[5];
    int i;
    BufferInit(&b, data, 5);
    assert(BufferAppend(&b, 'a') == 1);
    assert(!strncmp(b.data, "a", 1));

    for(i = 0;i < 4;++i)
        assert(BufferAppend(&b, 'b') == 1);

    assert(BufferAppend(&b, 'c') == 0);
}

void test_buffer_set(void) {
    Buffer b;
    char data[5];
    BufferInit(&b, data, 5);

    assert(BufferSet(&b, "aaaaa", 5) == 5);
    assert(!strncmp(b.data, "aaaaa", 5));

    assert(BufferSet(&b, "bbbb", 4) == 4);
    assert(!strncmp(b.data, "bbbb", 4));

    assert(BufferSet(&b, "cccccc", 6) == 0);
    assert(!strncmp(b.data, "bbbb", 4));
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Buffer append", test_buffer_append },
        { "Buffer set", test_buffer_set },
    };

    run_tests(tests);
    return 0;
}

