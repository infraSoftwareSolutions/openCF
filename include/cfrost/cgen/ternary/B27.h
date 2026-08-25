/**
 * @file B27.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-03
 */

#include <stdio.h>
#include "tlimites.h"

#ifndef OPENCF___CFROST___CGEN___TERNARY_B27_H
#define OPENCF___CFROST___CGEN___TERNARY_B27_H

#if defined(OPENCF_FOR_GNU)

    /// @brief An array of characters representing the values of a B27 variable.
    const char* ocf_b27_chars[27] = {
        "(-D)", "(-C)", "(-B)", "(-A)",
        "(-9)", "(-8)", "(-7)", "(-6)",
        "(-5)", "(-4)", "(-3)", "(-2)",
        "(-1)", "(0)", "(1)", "(2)",
        "(3)", "(4)", "(5)", "(6)",
        "(7)", "(8)", "(9)", "(A)",
        "(B)", "(C)", "(D)"
    };

    typedef int8_t OCF_B27;

    /// @brief Sets the value of a B27 variable.
    /// @param value A reference to the B27 variable to set.
    /// @param newValue The new value to assign.
    static inline void ocf_b27_set(OCF_B27 *value, int8_t newValue) {
        if(newValue > 13 || newValue < -13) {
            printf("Overflow/Underflow error");
            return;
        }
        *value = newValue;
    }

    /// @brief Returns the character representation of the B27 value.
    /// @param value The B27 value to convert.
    /// @return The character representation of the value.
    static inline const char* ocf_b27_get(OCF_B27 value) {
        if(value > 13 || value < -13) {
            printf("Overflow/Underflow error");
            return ocf_b27_chars[13];
        }
        if(value < 0) return ocf_b27_chars[-1 * value];
        else return ocf_b27_chars[value + 13];
    }

#else

    /// @brief An array of characters representing the values of a B27 variable.
    const char* b27_chars[27] = {
        "(-D)", "(-C)", "(-B)", "(-A)",
        "(-9)", "(-8)", "(-7)", "(-6)",
        "(-5)", "(-4)", "(-3)", "(-2)",
        "(-1)", "(0)", "(1)", "(2)",
        "(3)", "(4)", "(5)", "(6)",
        "(7)", "(8)", "(9)", "(A)",
        "(B)", "(C)", "(D)"
    };

    typedef int8_t B27;

    /// @brief Sets the value of a B27 variable.
    /// @param value A reference to the B27 variable to set.
    /// @param newValue The new value to assign.
    static inline void b27_set(B27 *value, int8_t newValue) {
        if(newValue > 13 || newValue < -13) {
            printf("Overflow/Underflow error");
            return;
        }
        *value = newValue;
    }

    /// @brief Returns the character representation of the B27 value.
    /// @param value The B27 value to convert.
    /// @return The character representation of the value.
    static inline const char* b27_get(B27 value) {
        if(value > 13 || value < -13) {
            printf("Overflow/Underflow error");
            return b27_chars[13];
        }
        if(value < 0) return b27_chars[-1 * value];
        else return b27_chars[value + 13];
    }

#endif

#endif // OPENCF___CFROST___CGEN___TERNARY_B27_H