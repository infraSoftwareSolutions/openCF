/**
 * @file tlimites.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-03
 */

#include <stdint.h>

#ifndef OPENCF___CFROST___CGEN___TERNARY_TLIMITES_H
#define OPENCF___CFROST___CGEN___TERNARY_TLIMITES_H

#if defined(OPENCF_FOR_GNU)

    const uint8_t ocf_tnull = 0; // ternary null
    // for Balanced Ternary Logic
    const int8_t ocf_ttrue = 2; // ternary true
    const int8_t ocf_tunknown = 1; // ternary unknown
    const int8_t ocf_tfalse = -1; // ternary false
    // for Unbalanced Ternary Logic
    const uint8_t ocf_utrue = 3; // unbalanced ternary true
    const uint8_t ocf_uunknown = 2; // unbalanced ternary unknown
    const uint8_t ocf_ufalse = 1; // unbalanced ternary false

    #define OCF_MAX_TIRT 1
    #define OCF_MIN_TIRT -1
    #define OCF_MAX_UTIRT 2
    #define OCF_MIN_UTIRT 0
    #define OCF_MAX_TYRT 364
    #define OCF_MIN_TYRT -364
    #define OCF_MAX_UTYRT 728
    #define OCF_MIN_UTYRT 0
    #define OCF_MAX_UB27 26
    #define OCF_MIN_UB27 0
    #define OCF_MAX_B27 13
    #define OCF_MIN_B27 -13

#else
    const uint8_t tnull = 0; // ternary null
    // for Balanced Ternary Logic
    const int8_t ttrue = 2; // ternary true
    const int8_t tunknown = 1; // ternary unknown
    const int8_t tfalse = -1; // ternary false
    // for Unbalanced Ternary Logic
    const uint8_t utrue = 3; // unbalanced ternary true
    const uint8_t uunknown = 2; // unbalanced ternary unknown
    const uint8_t ufalse = 1; // unbalanced ternary false

    #define MAX_TIRT 1
    #define MIN_TIRT -1
    #define MAX_UTIRT 2
    #define MIN_UTIRT 0
    #define MAX_TYRT 364
    #define MIN_TYRT -364
    #define MAX_UTYRT 728
    #define MIN_UTYRT 0
    #define MAX_UB27 26
    #define MIN_UB27 0
    #define MAX_B27 13
    #define MIN_B27 -13
#endif

#endif // OPENCF___CFROST___CGEN___TERNARY_TLIMITES_H