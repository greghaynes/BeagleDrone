#ifndef AFPOTO_H
#define AFPOTO_H

/*
 * Implements Afproto v3 protocol using RingBuffers
 */

#include "app/buffer.h"

/* 
 * Given a ringbuffer, produce decoded frame nearest the start, if possible.
 *
 * If a frame is found, all data preceding and including frame is removed
 * from buff
 */
void afproto_ringbuffer_pop_frame(RingBuffer *input, Buffer *output);

/*
 * Encapsulate input in afproto frame and push into output
 *
 * If an error occured (such as full buff), the size of buff will be
 * unmodified. Note that even an empty afproto frame has non zero size.
 */
void afproto_ringbuffer_push_frame(RingBuffer *output, RingBuffer *input);

#endif
