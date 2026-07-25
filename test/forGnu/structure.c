#define OPENCF_FOR_GNU
#include "cfrost/structure.h"
#include "cfrost/test.h"
#include "cfrost/cgen/string.h"

/**
 * @file micros.c
 * @brief Comprehensive test suite for micros.h library
 * @details Tests cstring_micros functions and jump macros with various edge cases
 * @note References constant values from CObjectData.c (compiled separately)
 */

// External declarations for CObjectData constants (compiled in object file)
extern const _Bool value1;
extern const char value2;
extern const short value3;
extern const int value4;
extern const long value5;
extern const unsigned char value6;
extern const unsigned short value7;
extern const unsigned int value8;
extern const unsigned long value9;
extern const signed char value10;
extern const short value11;
extern const int value12;
extern const long value13;
extern const double value14;
extern const float value15;
extern const double value16;
extern const char value17[];
extern const int value18[];
extern const double value19[];
extern const int value20;

OCF_TEST_MAIN(cgen: micros);
    
    // ==================== JUMP MACROS TESTS ====================
    // Test basic jump loop
    short jv1 = 0, jv2 = 0, jv3 = 100, jv4 = 200, jv5 = 10;
    
    // Jump loop 1: increment until reaching 50
    tl1: jv1++;
    ocf_jump_if(jv1 < 50, tl1);
    OCF_TEST_EQU(jv1, 50);  // Should stop at 50
    
    // Jump loop 2: increment from 0 to 50 (inclusive)
    tl2: jv2++;
    ocf_jump_if(jv2 <= 50, tl2);
    OCF_TEST_EQU(jv2, 51);  // Should be 51 when loop breaks
    
    // Jump loop 3: decrement from 100 to 0
    tl3: jv3--;
    ocf_jump_if(jv3 > 0, tl3);
    OCF_TEST_EQU(jv3, 0);  // Should stop at 0
    
    // Jump loop 4: decrement from 200 to -1
    tl4: jv4--;
    ocf_jump_if(jv4 >= 0, tl4);
    OCF_TEST_EQU(jv4, -1);  // Should be -1 when loop breaks
    
    // Jump loop 5: decrement until not equal to 5
    tl5: jv5--;
    ocf_jump_if(jv5 != 5, tl5);
    OCF_TEST_EQU(jv5, 5);  // Should stop at 5
    
    // Advanced jump test: nested labels
    int counter = 0, result = 0;
    tl_outer: counter++;
    if (counter < 3) {
        result += 10;
        ocf_jump_if(counter < 3, tl_outer);
    }
    OCF_TEST_EQU(counter, 3);
    OCF_TEST_EQU(result, 20);
    
    // Edge case: jump with boundary conditions
    int boundary_test = 0;
    tl_boundary: boundary_test++;
    ocf_jump_if(boundary_test < 1, tl_boundary);
    OCF_TEST_EQU(boundary_test, 1);
    
    // ==================== CSTRING_MICROS TESTS ====================
    
    // Test 1: length() function
    ocf_string(s1,) = "09iie8";
    OCF_TEST_EQU(length(s1), 6);
    
    ocf_string(s_empty,) = "";
    OCF_TEST_EQU(length(s_empty), 0);
    
    ocf_string(s_single,) = "A";
    OCF_TEST_EQU(length(s_single), 1);
    
    ocf_string(s_long,) = "This is a longer test string";
    OCF_TEST_EQU(length(s_long), 28);
    
    // Test 2: equal() function
    ocf_string(s2,) = "88938";
    OCF_TEST_EQU(equal(s1, s2), false); // Different strings
    OCF_TEST_EQU(length(s2), 5);
    
    ocf_string(s3,) = "88938";
    OCF_TEST_EQU(equal(s2, s3), true); // Identical strings
    
    ocf_string(s_test1,) = "test";
    ocf_string(s_test2,) = "test";
    OCF_TEST_EQU(equal(s_test1, s_test2), true);
    
    ocf_string(s_test3,) = "Test";
    OCF_TEST_EQU(equal(s_test1, s_test3), false); // Case sensitive
    
    OCF_TEST_EQU(equal(NULL, s_test1), false); // NULL check
    OCF_TEST_EQU(equal(s_test1, NULL), false); // NULL check
    
    // Test 3: is_empty() function
    OCF_TEST_EQU(is_empty(s3), false);
    OCF_TEST_EQU(is_empty(s_empty), true);
    OCF_TEST_EQU(is_empty(NULL), true); // NULL is empty
    
    // Test 4: exist() function - check if character exists
    OCF_TEST_EQU(exist(s2, '8'), true); // '8' exists in "88938"
    OCF_TEST_EQU(exist(s2, '3'), true); // '3' exists
    OCF_TEST_EQU(exist(s2, 'i'), false); // 'i' doesn't exist
    OCF_TEST_EQU(exist(s2, '9'), true); // '9' exists
    
    ocf_string(s_alpha,) = "abcdefghijklmnopqrstuvwxyz";
    OCF_TEST_EQU(exist(s_alpha, 'a'), true);
    OCF_TEST_EQU(exist(s_alpha, 'z'), true);
    OCF_TEST_EQU(exist(s_alpha, 'm'), true);
    OCF_TEST_EQU(exist(s_alpha, 'A'), false); // Case sensitive
    
    // Test 5: concatenate() function
    ocf_string(s_concat1, 100) = "Hello";
    ocf_string(s_concat2,) = " World";
    ocf_string(s_result,) = concatenate(s_concat1, s_concat2);
    OCF_TEST_EQU(length(s_result), 11); // "Hello World" is 11 chars
    OCF_TEST_EQU(equal(s_result, "Hello World"), true);
    
    ocf_string(s_c1, 50) = "Test";
    ocf_string(s_c2,) = "123";
    concatenate(s_c1, s_c2);
    OCF_TEST_EQU(equal(s_c1, "Test123"), true);
    
    // Test concatenate with empty string
    ocf_string(s_c3, 50) = "Base";
    ocf_string(s_c4,) = "";
    concatenate(s_c3, s_c4);
    OCF_TEST_EQU(equal(s_c3, "Base"), true); // Should remain unchanged
    
    // Test 6: sub_exist() function - check if substring exists
    OCF_TEST_EQU(sub_exist(s2, "938"), true); // "938" exists in "88938"
    OCF_TEST_EQU(sub_exist(s2, "88"), true); // "88" exists at start
    OCF_TEST_EQU(sub_exist(s2, "8"), true); // "8" exists
    OCF_TEST_EQU(sub_exist(s2, "88k"), false); // "88k" doesn't exist
    OCF_TEST_EQU(sub_exist(s2, "xyz"), false); // "xyz" doesn't exist
    
    ocf_string(s_sub1,) = "MetaCoreSystem";
    OCF_TEST_EQU(sub_exist(s_sub1, "Meta"), true);
    OCF_TEST_EQU(sub_exist(s_sub1, "Core"), true);
    OCF_TEST_EQU(sub_exist(s_sub1, "System"), true);
    OCF_TEST_EQU(sub_exist(s_sub1, "CoreSys"), true); // Overlapping match
    OCF_TEST_EQU(sub_exist(s_sub1, "meta"), false); // Case sensitive
    OCF_TEST_EQU(sub_exist(s_sub1, "xyz"), false);
    
    // Test 7: count() function - count character occurrences
    OCF_TEST_EQU(count(s2, '8'), 3); // "88938" has three '8's (positions 0, 1, 4)
    OCF_TEST_EQU(count(s1, 'i'), 2); // "09iie8" has two 'i's
    OCF_TEST_EQU(count(s1, 'e'), 1); // "09iie8" has one 'e'
    OCF_TEST_EQU(count(s1, '0'), 1); // "09iie8" has one '0'
    
    ocf_string(s_count,) = "aaaaabbbccc";
    OCF_TEST_EQU(count(s_count, 'a'), 5);
    OCF_TEST_EQU(count(s_count, 'b'), 3);
    OCF_TEST_EQU(count(s_count, 'c'), 3);
    OCF_TEST_EQU(count(s_count, 'd'), 0); // Character doesn't exist
    
    ocf_string(s_special,) = "...***===***...";
    OCF_TEST_EQU(count(s_special, '.'), 6);
    OCF_TEST_EQU(count(s_special, '*'), 6);
    OCF_TEST_EQU(count(s_special, '='), 3);
    
    // Test 8: cstr_empty() function
    ocf_string(s_to_empty, 100) = "ToBeCleared";
    OCF_TEST_EQU(is_empty(s_to_empty), false);
    cstr_empty(s_to_empty);
    OCF_TEST_EQU(is_empty(s_to_empty), true); // Should be empty now
    
    // Test 9: cstr_free() function
    ocf_string(s_temp1,) = "test1";
    cstr_free(s_temp1);  // Should free without error
    
    ocf_string(s_temp2,) = "";
    cstr_free(s_temp2);  // Should free empty string
    
    // ==================== EDGE CASES AND SPECIAL CHARACTERS ====================
    
    // Test with special characters
    ocf_string(s_special_chars,) = "\n\t\r\\";
    OCF_TEST_EQU(length(s_special_chars), 4); // 4 escape sequences
    
    // Test with numeric strings
    ocf_string(s_numeric,) = "1234567890";
    OCF_TEST_EQU(length(s_numeric), 10);
    OCF_TEST_EQU(count(s_numeric, '1'), 1);
    OCF_TEST_EQU(exist(s_numeric, '5'), true);
    
    // Test with mixed case
    ocf_string(s_mixed,) = "AbCdEfGhIj";
    OCF_TEST_EQU(length(s_mixed), 10);
    OCF_TEST_EQU(count(s_mixed, 'A'), 1);
    OCF_TEST_EQU(count(s_mixed, 'a'), 0); // Case sensitive
    
    // ==================== TEST COBJECT_DATA CONSTANTS ====================
    // These values are defined in CObjectData.c
    
    // Verify const values are properly compiled
    OCF_TEST_EQU(value1, true); // cbool(value1, true)
    OCF_TEST_EQU(value2, '9'); // cchar(value2, '9')
    OCF_TEST_EQU(value3, 8880); // cshort(value3, 8880)
    OCF_TEST_EQU(value4, 199983); // cint(value4, 199983)
    OCF_TEST_EQU(value5, 10009389); // clong(value5, 10009389)
    
    OCF_TEST_EQU(value6, 199); // cuint8(value6, 199)
    OCF_TEST_EQU(value7, 8889); // cuint16(value7, 8889)
    OCF_TEST_EQU(value8, 98883); // cuint32(value8, 98883)
    OCF_TEST_EQU(value9, 998938); // cuint64(value9, 998938)
    
    OCF_TEST_EQU(value10, -10); // cint8(value10, -10)
    OCF_TEST_EQU(value11, -1183); // cint16(value11, -1183)
    OCF_TEST_EQU(value12, -77787); // cint32(value12, -77787)
    OCF_TEST_EQU(value13, -188388); // cint64(value13, -188388)
    
    // Float/Double comparison with tolerance
    float diff14 = value14 > 2.88 ? value14 - 2.88 : 2.88 - value14;
    OCF_TEST_EQU(diff14 < 0.01f, true); // value14 ≈ 2.89
    
    // Test cstring and arrays
    OCF_TEST_EQU(length(value17), 3); // ocf_string(value17, "ken")
    OCF_TEST_EQU(equal(value17, "ken"), true);
    
    // Array tests
    OCF_TEST_EQU(value18[0], 19);
    OCF_TEST_EQU(value18[1], 38);
    OCF_TEST_EQU(value18[2], 183);
    OCF_TEST_EQU(value18[3], 198);
    
    // Test cdynamic macro
    OCF_TEST_EQU(value20, 880); // cdynamic(value20, 880)
    
    // ==================== COMPREHENSIVE STRING OPERATIONS ====================
    
    // Multiple operations in sequence
    ocf_string(s_ops, 200) = "Start";
    OCF_TEST_EQU(length(s_ops), 5);
    concatenate(s_ops, "-Middle");
    OCF_TEST_EQU(length(s_ops), 12);
    concatenate(s_ops, "-End");
    OCF_TEST_EQU(length(s_ops), 16);
    OCF_TEST_EQU(equal(s_ops, "Start-Middle-End"), true);
    
    OCF_TEST_EQU(exist(s_ops, '-'), true);
    OCF_TEST_EQU(count(s_ops, '-'), 2); // Two dashes
    OCF_TEST_EQU(sub_exist(s_ops, "Middle"), true);
    OCF_TEST_EQU(sub_exist(s_ops, "Start-Middle"), true);

OCF_TEST_EXIT(true)