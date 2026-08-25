/**
 * @file cbool_8.h
 * @brief A compact cbool_8 container for managing multiple cbool_8 values in a single byte
 * @details Provides a cbool_8 structure and operations to efficiently store and manipulate
 *          up to 8 independent cbool_8 values using bit-level operations. Each bit position
 *          (0-7) represents one cbool_8 value, making this ideal for applications requiring
 *          efficient storage of multiple cbool_8 flags.
 *
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * 
 * @note Position 0 represents the least significant bit (LSB) and position 7 the most significant bit (MSB).
 * @note All functions preserve the original value and return new structures (immutable design).
 * 
 * Functions provided:
 * - set(): Set or reset a cbool_8 value at a specified bit position
 * - get(): Retrieve the cbool_8 value at a specified bit position
 * - empty(): Create an empty cbool_8 structure (all bits 0)
 * - isEmpty(): Check if a cbool_8 structure is empty
 * 
 * Usage example:
 * @code
 * cbool_8 flags = empty();              // Create empty structure
 * flags = set(flags, true, 0);          // Set bit 0 to true
 * flags = set(flags, true, 1);          // Set bit 1 to true
 * bool bit0 = get(flags, 0);            // Read bit 0 (returns true)
 * bool isEmpty_check = isEmpty(flags);  // Returns false
 * @endcode
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "get_bit.h"
#include "reset_bit.h"
#include "set_bit.h"

#ifndef OPENCF___CFROST___CGEN___BITUTILITYS_CBOOL_8_H
#define OPENCF___CFROST___CGEN___BITUTILITYS_CBOOL_8_H

    #if defined(OPENCF_FOR_GNU)

        /// @brief A structure representing an 8-bit ocf_bool value that can store multiple allocate states
        /// @details This structure encapsulates an 8-bit unsigned integer (uint8_t) to store multiple
        ///          ocf_bool values, one for each bit position (0-7). This allows efficient storage
        ///          and manipulation of up to 8 independent ocf_bool values in a single byte.
        /// @members value The underlying 8-bit unsigned integer storing the ocf_bool flags
        typedef struct { uint8_t value; } ocf_bool;

        /// @brief Set or reset the ocf_bool value at position 0
        /// @param current The current ocf_bool structure
        /// @param value The ocf_bool value to set
        /// @return A new ocf_bool structure with the specified bit modified
        static inline ocf_bool ocf_bool_set(ocf_bool current, bool value) {
            return value ? (ocf_bool){ocf_set_u8bit(current.value, 0)} : (ocf_bool){reset_u8bit(current.value, 0)};
        }

        /// @brief Retrieve the ocf_bool value at position 0
        /// @param current The current ocf_bool structure
        /// @return The ocf_bool value at position 0 (true for 1, false for 0)
        static inline bool ocf_bool_get(ocf_bool current) {
            return ocf_get_u8bit(current.value, 0);
        }

        /// @brief Set or reset a ocf_bool bit at a specified position
        /// @details Creates a new ocf_bool structure with the bit at the specified position set to the
        ///          provided ocf_bool value. If value is true, the bit is set to 1; if false, it's reset to 0.
        /// @param current The current ocf_bool structure
        /// @param value The ocf_bool value to set (true sets bit, false resets bit)
        /// @param position The bit position to modify (0-7, where 0 is LSB)
        /// @return A new ocf_bool structure with the specified bit modified
        /// @note Position 0 represents the least significant bit (LSB)
        static inline ocf_bool ocf_bool_set_in(ocf_bool current, bool value, uint8_t position) {
            return value ? (ocf_bool){ocf_set_u8bit(current.value, position)} 
                        : (ocf_bool){ocf_reset_u8bit(current.value, position)};
        }

        /// @brief Retrieve the ocf_bool value at a specified bit position
        /// @details Extracts and returns the ocf_bool value stored at the specified bit position
        ///          in the ocf_bool structure. Returns true if the bit is 1, false if the bit is 0.
        /// @param current The ocf_bool structure to read from
        /// @param position The bit position to read (0-7, where 0 is LSB)
        /// @return The ocf_bool value at the specified position (true for 1, false for 0)
        /// @note Position 0 represents the least significant bit (LSB)
        static inline bool ocf_bool_get_in(ocf_bool current, uint8_t position) {
            return ocf_get_u8bit(current.value, position);
        }

        /// @brief Create an empty ocf_bool structure (all bits set to 0)
        /// @details Initializes and returns a new ocf_bool structure with all bits set to 0,
        ///          representing an empty or unset state.
        /// @return A new ocf_bool structure with value 0 (all bits cleared)
        /// @note This function is commonly used to initialize a fresh ocf_bool container
        static inline ocf_bool ocf_bool_empty() {
            return (ocf_bool){0};
        }

        /// @brief Check if a ocf_bool structure is empty (all bits are 0)
        /// @details Compares the provided ocf_bool structure to an empty ocf_bool structure
        ///          and returns true if they are equal (i.e., all bits are 0).
        /// @param current The ocf_bool structure to check
        /// @return true if the structure is empty (all bits are 0), false otherwise
        static inline bool ocf_bool_isEmpty(ocf_bool current) {
            return (current.value == (uint8_t)0) ? true : false;
        }

    #else

        /// @brief A structure representing an 8-bit cbool_8 value that can store multiple cbool_8 states
        /// @details This structure encapsulates an 8-bit unsigned integer (uint8_t) to store multiple
        ///          cbool_8 values, one for each bit position (0-7). This allows efficient storage
        ///          and manipulation of up to 8 independent cbool_8 values in a single byte.
        /// @members value The underlying 8-bit unsigned integer storing the cbool_8 flags
        typedef struct { uint8_t value; } cbool_8;

        /// @brief Set or reset the cbool_8 value at position 0
        /// @param current The current cbool_8 structure
        /// @param value The cbool_8 value to set
        /// @return A new cbool_8 structure with the specified bit modified
        static inline cbool_8 cbool_8_set(cbool_8 current, bool value) {
            return value ? (cbool_8){set_u8bit(current.value, 0)} : (cbool_8){reset_u8bit(current.value, 0)};
        }

        /// @brief Retrieve the cbool_8 value at position 0
        /// @param current The current cbool_8 structure
        /// @return The cbool_8 value at position 0 (true for 1, false for 0)
        static inline bool cbool_8_get(cbool_8 current) {
            return get_u8bit(current.value, 0);
        }

        /// @brief Set or reset a cbool_8 bit at a specified position
        /// @details Creates a new cbool_8 structure with the bit at the specified position set to the
        ///          provided cbool_8 value. If value is true, the bit is set to 1; if false, it's reset to 0.
        /// @param current The current cbool_8 structure
        /// @param value The cbool_8 value to set (true sets bit, false resets bit)
        /// @param position The bit position to modify (0-7, where 0 is LSB)
        /// @return A new cbool_8 structure with the specified bit modified
        /// @note Position 0 represents the least significant bit (LSB)
        static inline cbool_8 cbool_8_set_in(cbool_8 current, bool value, uint8_t position) {
            return value ? (cbool_8){set_u8bit(current.value, position)} 
                        : (cbool_8){reset_u8bit(current.value, position)};
        }

        /// @brief Retrieve the cbool_8 value at a specified bit position
        /// @details Extracts and returns the cbool_8 value stored at the specified bit position
        ///          in the cbool_8 structure. Returns true if the bit is 1, false if the bit is 0.
        /// @param current The cbool_8 structure to read from
        /// @param position The bit position to read (0-7, where 0 is LSB)
        /// @return The cbool_8 value at the specified position (true for 1, false for 0)
        /// @note Position 0 represents the least significant bit (LSB)
        static inline bool cbool_8_get_in(cbool_8 current, uint8_t position) {
            return get_u8bit(current.value, position);
        }

        /// @brief Create an empty cbool_8 structure (all bits set to 0)
        /// @details Initializes and returns a new cbool_8 structure with all bits set to 0,
        ///          representing an empty or unset state.
        /// @return A new cbool_8 structure with value 0 (all bits cleared)
        /// @note This function is commonly used to initialize a fresh cbool_8 container
        static inline cbool_8 cbool_8_empty() {
            return (cbool_8){0};
        }

        /// @brief Check if a cbool_8 structure is empty (all bits are 0)
        /// @details Compares the provided cbool_8 structure to an empty cbool_8 structure
        ///          and returns true if they are equal (i.e., all bits are 0).
        /// @param current The cbool_8 structure to check
        /// @return true if the structure is empty (all bits are 0), false otherwise
        static inline bool cbool_8_isEmpty(cbool_8 current) {
            return (current.value == (uint8_t)0) ? true : false;
        }

    #endif

#endif // OPENCF___CFROST___CGEN___BITUTILITYS_CBOOL_8_H