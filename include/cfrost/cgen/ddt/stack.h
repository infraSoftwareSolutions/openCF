/**
 * @file stack.h
 * @brief Dynamic Stack (CDS) implementation for cdynamic structs.
 * @details This module provides a dynamic stack structure (cstack) for storing cdynamic
 * elements, along with functions for initialization, modification, querying, and cleanup.
 * The cstack supports dynamic resizing, element pushing and popping, and other common stack
 *  operations.  Users must call cstack_free() to release resources when finished with the stack.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdlib.h>
#include "dynamic.h"

#ifndef OPENCF___CFROST___CGEN___DDT_STACK_H
#define OPENCF___CFROST___CGEN___DDT_STACK_H

#if defined(OPENCF_FOR_GNU)
    
    typedef struct ocf_stack
    {
        size_t size;
        size_t capacity;
        ocf_dynamic *data;
    }
    ocf_stack;

    static inline void ocf_stack_init(ocf_stack *stack)
    {
        stack->size = 0;
        stack->capacity = 4;
        stack->data = (ocf_dynamic *)malloc(stack->capacity * sizeof(ocf_dynamic));
    }

    static inline void ocf_stack_free(ocf_stack *stack)
    {
        free(stack->data);
        stack->data = NULL;
        stack->size = 0;
        stack->capacity = 0;
    }

    static inline void ocf_stack_push(ocf_stack *stack, ocf_dynamic value)
    {
        if (stack->size >= stack->capacity)
        {
            stack->capacity *= 2;
            stack->data = (ocf_dynamic *)realloc(stack->data, stack->capacity * sizeof(ocf_dynamic));
        }
        stack->data[stack->size++] = value;
    }

    static inline ocf_dynamic ocf_stack_pop(ocf_stack *stack)
    {
        if (stack->size == 0)
            return (ocf_dynamic){}; // Stack is empty, return default value

        return stack->data[--stack->size];
    }

    static inline ocf_dynamic ocf_stack_peek(ocf_stack *stack)
    {
        if (stack->size == 0)
            return (ocf_dynamic){}; // Stack is empty, return default value

        return stack->data[stack->size - 1];
    }

    static inline size_t ocf_stack_size(ocf_stack *stack)
    {
        return stack->size;
    }

    static inline size_t ocf_stack_capacity(ocf_stack *stack)
    {
        return stack->capacity;
    }
#else

    typedef struct cstack
    {
        size_t size;
        size_t capacity;
        cdynamic *data;
    }
    cstack;

    static inline void cstack_init(cstack *stack)
    {
        stack->size = 0;
        stack->capacity = 4;
        stack->data = (cdynamic *)malloc(stack->capacity * sizeof(cdynamic));
    }

    static inline void cstack_free(cstack *stack)
    {
        free(stack->data);
        stack->data = NULL;
        stack->size = 0;
        stack->capacity = 0;
    }

    static inline void cstack_push(cstack *stack, cdynamic value)
    {
        if (stack->size >= stack->capacity)
        {
            stack->capacity *= 2;
            stack->data = (cdynamic *)realloc(stack->data, stack->capacity * sizeof(cdynamic));
        }
        stack->data[stack->size++] = value;
    }

    static inline cdynamic cstack_pop(cstack *stack)
    {
        if (stack->size == 0)
            return (cdynamic){}; // Stack is empty, return default value

        return stack->data[--stack->size];
    }

    static inline cdynamic cstack_peek(cstack *stack)
    {
        if (stack->size == 0)
            return (cdynamic){}; // Stack is empty, return default value

        return stack->data[stack->size - 1];
    }

    static inline size_t cstack_size(cstack *stack)
    {
        return stack->size;
    }

    static inline size_t cstack_capacity(cstack *stack)
    {
        return stack->capacity;
    }

#endif

#endif // OPENCF___CFROST___CGEN___DDT_STACK_H