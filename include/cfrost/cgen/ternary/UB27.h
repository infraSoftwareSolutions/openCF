/**
 * @file UB27.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-03
 */

#include <stdio.h>
#include "tlimites.h"

#ifndef OPENCF___CFROST___CGEN___TERNARY_UB27_H
#define OPENCF___CFROST___CGEN___TERNARY_UB27_H

#if defined(OPENCF_FOR_GNU)

    /// @brief An array of characters representing the values of a UB27 variable.
    const char ocf_ub27_chars[27] = {
        '0', '1', '2', '3', '4', '5',
        '6', '7', '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q'
    };

    typedef uint8_t OCF_UB27;

    /// @brief Sets the value of a UB27 variable.
    /// @param value A reference to the UB27 variable to set.
    /// @param newValue The new value to assign.
    static inline void ocf_ub27_set(OCF_UB27 *value, uint8_t newValue) {
        if(newValue >= 27) {
            printf("Overflow error");
            return;
        }
        *value = newValue;
    }

    /// @brief Returns the character representation of the UB27 value.
    /// @param value The UB27 value to convert.
    /// @return The character representation of the value.
    static inline char ocf_ub27_get(OCF_UB27 value) {
        if(value >= 27) {
            printf("Overflow error");
            return ocf_ub27_chars[26];
        }
        return ocf_ub27_chars[value];
    }

#else

    /// @brief An array of characters representing the values of a UB27 variable.
    const char ub27_chars[27] = {
        '0', '1', '2', '3', '4', '5',
        '6', '7', '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q'
    };

    typedef uint8_t UB27;

    /// @brief Sets the value of a UB27 variable.
    /// @param value A reference to the UB27 variable to set.
    /// @param newValue The new value to assign.
    static inline void ub27_set(UB27 *value, uint8_t newValue) {
        if(newValue >= 27) {
            printf("Overflow error");
            return;
        }
        *value = newValue;
    }

    /// @brief Returns the character representation of the UB27 value.
    /// @param value The UB27 value to convert.
    /// @return The character representation of the value.
    static inline char ub27_get(UB27 value) {
        if(value >= 27) {
            printf("Overflow error");
            return ub27_chars[26];
        }
        return ub27_chars[value];
    }

#endif

#endif // OPENCF___CFROST___CGEN___TERNARY_UB27_H