#ifndef OPENCF___CFROST___CGEN___RANDOM_H
#define OPENCF___CFROST___CGEN___RANDOM_H

/**
 * @file random.h
 * @brief random struct and related functions for simple random number generation.
 * @details This module defines the random struct, which holds a core integer and a state double for
 * a simple linear congruential generator (LCG).  It provides functions to set the core value and
 * update the core and state according to the LCG algorithm.  Users can call set_core
 * to initialize the generator and update_core to advance the state.  The current state can be
 * accessed via the state field of the random struct.
 * @author Ali Lafi
 * @date 2024-06
 */

#if defined(OPENCF_FOR_GNU)

    typedef struct ocf_random
    {
        int core;
        double state;
    }
    ocf_random;

    void ocf_random_set_core(ocf_random *self, int core)
    {
        self->core = core;
        self->state = (double)(core / (core >> 2));
    }

    void ocf_random_update_core(ocf_random *self)
    {
        self->core = (self->core * 1103515245 + 12345) & 0x7fffffff;
        self->state = (double)self->core / 0x7fffffff;
    }

    // void update_state();

#else

    typedef struct crandom
    {
        int core;
        double state;
    }
    crandom;

    void crandom_set_core(crandom *self, int core)
    {
        self->core = core;
        self->state = (double)(core / (core >> 2));
    }

    void crandom_update_core(crandom *self)
    {
        self->core = (self->core * 1103515245 + 12345) & 0x7fffffff;
        self->state = (double)self->core / 0x7fffffff;
    }

    // void update_state();

#endif

#endif // OPENCF___CFROST___CGEN___RANDOM_H