/**
 * This library provides a way to represent and manipulate ternary logic values using a single byte (uint8_t).
 * The values are represented as follows:
 * - Null: 00 (0 in decimal)
 * - False: 01 (1 in decimal)
 * - Unknown: 10 (2 in decimal)
 * - True: 11 (3 in decimal)
 * @file utirt.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-02
 */

#include "tlimites.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef OPENCF___CFROST___CGEN___TERNARY_UTIRT_H
#define OPENCF___CFROST___CGEN___TERNARY_UTIRT_H

#if defined(OPENCF_FOR_GNU)

    typedef uint8_t ocf_utirt;

    /// @brief Sets the high bit of a ternary logic value
    /// @param value The ternary logic value to modify
    static inline void ocf_utirt_set_high(ocf_utirt *value) { *value |= 2; }

    /// @brief Sets the low bit of a ternary logic value
    /// @param value The ternary logic value to modify
    static inline void ocf_utirt_set_low(ocf_utirt *value) { *value |= 1; }

    /// @brief Resets the high bit of a ternary logic value
    /// @param value The ternary logic value to modify
    static inline void ocf_utirt_reset_high(ocf_utirt *value) { *value &= 1; }

    /// @brief Resets the low bit of a ternary logic value
    /// @param value The ternary logic value to modify
    static inline void ocf_utirt_reset_low(ocf_utirt *value) { *value &= 2; }

    /// @brief Sets the high bit of a ternary logic value based on a boolean condition
    /// @param value The ternary logic value to modify
    /// @param newValue The boolean value to set
    static inline void ocf_utirt_set_high(ocf_utirt *value, bool newValue) {
        if(newValue) ocf_utirt_set_high(value);
        else ocf_utirt_reset_high(value);
    }

    /// @brief Sets the low bit of a ternary logic value based on a boolean condition
    /// @param value The ternary logic value to modify
    /// @param newValue The boolean value to set
    static inline void ocf_utirt_set_low(ocf_utirt *value, bool newValue) {
        if(newValue) ocf_utirt_set_low(value);
        else ocf_utirt_reset_low(value);
    }

    /// @brief Sets a bit of a ternary logic value based on a boolean condition
    /// @param value The ternary logic value to modify
    /// @param islow A boolean indicating whether to modify the low bit
    /// @param newValue The boolean value to set
    static inline void ocf_utirt_set(ocf_utirt *value, bool islow, bool newValue) {
        if(islow) {
            if(newValue) ocf_utirt_set_low(value);
            else ocf_utirt_reset_low(value);
        }
        else {
            if(newValue) ocf_utirt_set_high(value);
            else ocf_utirt_reset_high(value);
        }
    }

    /// @brief to set a ternary logic value to true
    /// @param value The ternary logic value to modify
    static inline void ocf_utirt_true(ocf_utirt *value) { *value = 3; }

    /// @brief to set a ternary logic value to unknown
    /// @param value The ternary logic value to modify
    static inline void ocf_utirt_unknown(ocf_utirt *value) { *value = 2; }

    /// @brief to set a ternary logic value to false
    /// @param value The ternary logic value to modify
    static inline void ocf_utirt_false(ocf_utirt *value) { *value = 1; }

    /// @brief to set a ternary logic value to null
    /// @param value The ternary logic value to modify
    static inline void ocf_utirt_null(ocf_utirt *value) { *value = 0; }

    /// @brief Displays the value of a ternary logic value
    /// @param value The ternary logic value to display
    static inline void ocf_utirt_show_value(ocf_utirt *value) {
        if(*value == 3) printf("true");
        else if(*value == 2) printf("unknown");
        else if(*value == 1) printf("false");
        else if(*value == 0) printf("null");
    }

    /// @brief Performs the NOT operation on a ternary logic value
    /// @param value The ternary logic value to negate
    /// @return The negation of the input ternary logic value
    static inline ocf_utirt ocf_utirt_not(ocf_utirt value) {
        ocf_utirt temp;
        if(value == 3) temp = 1;
        else if(value == 2) temp = 2;
        else if(value == 1) temp = 3;
        else temp = 0;
        return temp;
    }

    /// @brief Performs the AND operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the AND operation on the two input ternary logic values
    static inline ocf_utirt ocf_utirt_and(ocf_utirt first, ocf_utirt second) {
        if(first > second) return second;
        else return first;
    }


    /// @brief Performs the OR operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the OR operation on the two input ternary logic values
    static inline ocf_utirt ocf_utirt_or(ocf_utirt first, ocf_utirt second) {
        if(first > second) return first;
        else return second;
    }

    /// @brief Performs the XOR operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the XOR operation on the two input ternary logic values
    static inline ocf_utirt ocf_utirt_xor(ocf_utirt first, ocf_utirt second) {
        return ocf_utirt_or(ocf_utirt_and(first, ocf_utirt_not(second)), 
            ocf_utirt_and(ocf_utirt_not(first), second));
    }

    /// @brief Performs the NOR operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the NOR operation on the two input ternary logic values
    static inline ocf_utirt ocf_utirt_nor(ocf_utirt first, ocf_utirt second) {
        return ocf_utirt_not(ocf_utirt_or(first, second));
    }

    /// @brief Performs the NAND operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the NAND operation on the two input ternary logic values
    static inline ocf_utirt ocf_utirt_nand(ocf_utirt first, ocf_utirt second) {
        return ocf_utirt_not(ocf_utirt_and(first, second));
    }

    /// @brief Performs the XNOR operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the XNOR operation on the two input ternary logic values
    static inline ocf_utirt ocf_utirt_xnor(ocf_utirt first, ocf_utirt second) {
        return ocf_utirt_not(ocf_utirt_xor(first, second));
    }

#else

    typedef uint8_t utirt;

    /// @brief Sets the high bit of a ternary logic value
    /// @param value The ternary logic value to modify
    static inline void utirt_set_high(utirt *value) { *value |= 2; }

    /// @brief Sets the low bit of a ternary logic value
    /// @param value The ternary logic value to modify
    static inline void utirt_set_low(utirt *value) { *value |= 1; }

    /// @brief Resets the high bit of a ternary logic value
    /// @param value The ternary logic value to modify
    static inline void utirt_reset_high(utirt *value) { *value &= 1; }

    /// @brief Resets the low bit of a ternary logic value
    /// @param value The ternary logic value to modify
    static inline void utirt_reset_low(utirt *value) { *value &= 2; }

    /// @brief Sets the high bit of a ternary logic value based on a boolean condition
    /// @param value The ternary logic value to modify
    /// @param newValue The boolean value to set
    static inline void utirt_set_high(utirt *value, bool newValue) {
        if(newValue) utirt_set_high(value);
        else utirt_reset_high(value);
    }

    /// @brief Sets the low bit of a ternary logic value based on a boolean condition
    /// @param value The ternary logic value to modify
    /// @param newValue The boolean value to set
    static inline void utirt_set_low(utirt *value, bool newValue) {
        if(newValue) utirt_set_low(value);
        else utirt_reset_low(value);
    }

    /// @brief Sets a bit of a ternary logic value based on a boolean condition
    /// @param value The ternary logic value to modify
    /// @param islow A boolean indicating whether to modify the low bit
    /// @param newValue The boolean value to set
    static inline void utirt_set(utirt *value, bool islow, bool newValue) {
        if(islow) {
            if(newValue) utirt_set_low(value);
            else utirt_reset_low(value);
        }
        else {
            if(newValue) utirt_set_high(value);
            else utirt_reset_high(value);
        }
    }

    /// @brief to set a ternary logic value to true
    /// @param value The ternary logic value to modify
    static inline void utirt_true(utirt *value) { *value = utrue; }

    /// @brief to set a ternary logic value to unknown
    /// @param value The ternary logic value to modify
    static inline void utirt_unknown(utirt *value) { *value = uunknown; }

    /// @brief to set a ternary logic value to false
    /// @param value The ternary logic value to modify
    static inline void utirt_false(utirt *value) { *value = ufalse; }

    /// @brief to set a ternary logic value to null
    /// @param value The ternary logic value to modify
    static inline void utirt_null(utirt *value) { *value = tnull; }

    /// @brief Displays the value of a ternary logic value
    /// @param value The ternary logic value to display
    static inline void utirt_show_value(utirt *value) {
        if(*value == 3) printf("true");
        else if(*value == 2) printf("unknown");
        else if(*value == 1) printf("false");
        else if(*value == 0) printf("null");
    }

    /// @brief Performs the NOT operation on a ternary logic value
    /// @param value The ternary logic value to negate
    /// @return The negation of the input ternary logic value
    static inline utirt utirt_not(utirt value) {
        utirt temp;
        if(value == 3) temp = 1;
        else if(value == 2) temp = 2;
        else if(value == 1) temp = 3;
        else temp = 0;
        return temp;
    }

    /// @brief Performs the AND operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the AND operation on the two input ternary logic values
    static inline utirt utirt_and(utirt first, utirt second) {
        if(first > second) return second;
        else return first;
    }


    /// @brief Performs the OR operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the OR operation on the two input ternary logic values
    static inline utirt utirt_or(utirt first, utirt second) {
        if(first > second) return first;
        else return second;
    }

    /// @brief Performs the XOR operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the XOR operation on the two input ternary logic values
    static inline utirt utirt_xor(utirt first, utirt second) {
        return utirt_or(utirt_and(first, utirt_not(second)), 
            utirt_and(utirt_not(first), second));
    }

    /// @brief Performs the NOR operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the NOR operation on the two input ternary logic values
    static inline utirt utirt_nor(utirt first, utirt second) {
        return utirt_not(utirt_or(first, second));
    }

    /// @brief Performs the NAND operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the NAND operation on the two input ternary logic values
    static inline utirt utirt_nand(utirt first, utirt second) {
        return utirt_not(utirt_and(first, second));
    }

    /// @brief Performs the XNOR operation on two ternary logic values
    /// @param first The first ternary logic value
    /// @param second The second ternary logic value
    /// @return The result of the XNOR operation on the two input ternary logic values
    static inline utirt utirt_xnor(utirt first, utirt second) {
        return utirt_not(utirt_xor(first, second));
    }

#endif

#endif // OPENCF___CFROST___CGEN___TERNARY_UTIRT_H