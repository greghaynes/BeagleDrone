#include "buffer.h"

#include <string.h>

void BufferInit(Buffer *b, char *data, unsigned int size) {
    b->data = data;
    b->size = size;
    b->used = 0;
}

int BufferSet(Buffer *b, const char *src, unsigned int size) {
    if(size > b->size) return 0;

    memcpy(b->data, src, size);
    b->used = size;

    return size;
}

int BufferAppend(Buffer *b, char ch) {
    if(b->used >= b->size) return 0;

    b->data[b->used++] = ch;
    return 1;
}

void RingBufferInit(RingBuffer *b, char *data, unsigned int size) {
    b->data = data;
    b->used_end = 0;
    b->used_start = 0;
    b->size = size;
}

void RingBufferPush(RingBuffer *b, char ch) {
    b->data[b->used_end] = ch;
    ++b->used_end;
    if(b->used_end >= b->size)
        b->used_end = 0;

    if(b->used_end == b->used_start)
        ++b->used_start;
}

int RingBufferPop(RingBuffer *b, char *dst) {
    if(b->used_end == b->size) return 0;

    if(dst) *dst = b->used_start;
    ++b->used_start;

    if(b->used_start >= b->size)
        b->used_start = 0;

    return 1;
}

int RingBufferPeek(RingBuffer *b, char *dst) {
    if(b->used_end == b->size) return 0;

    if(dst) *dst = b->used_start;

    return 1;
}

