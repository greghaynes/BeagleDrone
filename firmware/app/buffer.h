#ifndef BUFFER_H
#define BUFFER_H

typedef struct Buffer {
    char *data;
    unsigned int size;
    unsigned int used;
} Buffer;

typedef struct RingBuffer {
    char *data;
    unsigned int used_end;
    unsigned int used_start;
    unsigned int size;
} RingBuffer;

void BufferInit(Buffer *b, char *data, unsigned int size);

/* Returns zero if src is too large, size otherwise */
int BufferSet(Buffer *b, const char *src, unsigned int size);

void BufferClear(Buffer *b);

/* Returns zero if full, 1 otherwise */
int BufferAppend(Buffer *b, char ch);

void RingBufferInit(RingBuffer *b, char *data, unsigned int size);

void RingBufferPush(RingBuffer *b, char ch);

/* Push onto opposite end of RingBufferPush */
void RingBufferPushBack(RingBuffer *b, char ch);

void RingBufferPushString(RingBuffer *b, char *data);

/* Pops one char, zero if buffer is empty, 1 otherwise */
int RingBufferPop(RingBuffer *b, char *dst);

/* Peeks at one char, zero if buffer is empty, 1 otherwise */
int RingBufferPeek(const RingBuffer *b, char *dst);

#endif

