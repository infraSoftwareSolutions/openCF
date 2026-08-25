/**
 * @file queue.h
 * @brief Dynamic Data Queue (cqueue) implementation for cdynamic structs.
 * @details This module provides a dynamic queue structure (cqueue) for storing cdynamic
 * elements, along with functions for initialization, modification, querying, and cleanup.
 * The cqueue supports dynamic resizing, element enqueueing and dequeueing, and other common
 * queue operations.  Users must call cqueue_free() to release resources when finished with the
 * queue.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdlib.h>
#include "dynamic.h"

#ifndef OPENCF___CFROST___CGEN___DDT_QUEUE_H
#define OPENCF___CFROST___CGEN___DDT_QUEUE_H

#if defined(OPENCF_FOR_GNU)

    typedef struct ocf_queue
    {
        size_t size;
        size_t capacity;
        cdynamic *data;
    }
    ocf_queue;

    static inline void ocf_queue_init(ocf_queue *queue)
    {
        queue->size = 0;
        queue->capacity = 4;
        queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
    }

    static inline void ocf_queue_free(ocf_queue *queue)
    {
        free(queue->data);
        queue->data = NULL;
        queue->size = 0;
        queue->capacity = 0;
    }

    static inline void ocf_queue_set(ocf_queue *queue, ocf_queue *other)
    {
        queue->size = other->size;
        queue->capacity = other->capacity;
        queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
        for (size_t i = 0; i < queue->size; i++)
            queue->data[i] = other->data[i];
    }

    static inline void ocf_queue_enqueue(ocf_queue *queue, cdynamic value)
    {
        if (queue->size >= queue->capacity)
        {
            queue->capacity *= 2;
            queue->data = (cdynamic *)realloc(queue->data, queue->capacity * sizeof(cdynamic));
        }
        queue->data[queue->size++] = value;
    }

    static inline void ocf_queue_dequeue(ocf_queue *queue)
    {
        if (queue->size == 0)
            return; // Queue is empty, nothing to dequeue

        for (size_t i = 0; i < queue->size - 1; i++)
            queue->data[i] = queue->data[i + 1];

        queue->size--;
    }

    static inline size_t ocf_queue_size(ocf_queue *queue)
    {
        return queue->size;
    }

    static inline size_t ocf_queue_capacity(ocf_queue *queue)
    {
        return queue->capacity;
    }

#else

    typedef struct cqueue
    {
        size_t size;
        size_t capacity;
        cdynamic *data;
    }
    cqueue;

    static inline void cqueue_init(cqueue *queue)
    {
        queue->size = 0;
        queue->capacity = 4;
        queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
    }

    static inline void cqueue_free(cqueue *queue)
    {
        free(queue->data);
        queue->data = NULL;
        queue->size = 0;
        queue->capacity = 0;
    }

    static inline void cqueue_set(cqueue *queue, cqueue *other)
    {
        queue->size = other->size;
        queue->capacity = other->capacity;
        queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
        for (size_t i = 0; i < queue->size; i++)
            queue->data[i] = other->data[i];
    }

    static inline void cqueue_enqueue(cqueue *queue, cdynamic value)
    {
        if (queue->size >= queue->capacity)
        {
            queue->capacity *= 2;
            queue->data = (cdynamic *)realloc(queue->data, queue->capacity * sizeof(cdynamic));
        }
        queue->data[queue->size++] = value;
    }

    static inline void cqueue_dequeue(cqueue *queue)
    {
        if (queue->size == 0)
            return; // Queue is empty, nothing to dequeue

        for (size_t i = 0; i < queue->size - 1; i++)
            queue->data[i] = queue->data[i + 1];

        queue->size--;
    }

    static inline size_t cqueue_size(cqueue *queue)
    {
        return queue->size;
    }

    static inline size_t cqueue_capacity(cqueue *queue)
    {
        return queue->capacity;
    }
#endif

#endif // OPENCF___CFROST___CGEN___DDT_QUEUE_H