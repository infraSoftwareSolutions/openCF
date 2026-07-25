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

TEST_MAIN(meta_cgen: micros);
    
    // ==================== JUMP MACROS TESTS ====================
    // Test basic jump loop
    short jv1 = 0, jv2 = 0, jv3 = 100, jv4 = 200, jv5 = 10;
    
    // Jump loop 1: increment until reaching 50
    tl1: jv1++;
    jump_if(jv1 < 50, tl1);
    TEST_EQU(jv1, 50);  // Should stop at 50
    
    // Jump loop 2: increment from 0 to 50 (inclusive)
    tl2: jv2++;
    jump_if(jv2 <= 50, tl2);
    TEST_EQU(jv2, 51);  // Should be 51 when loop breaks
    
    // Jump loop 3: decrement from 100 to 0
    tl3: jv3--;
    jump_if(jv3 > 0, tl3);
    TEST_EQU(jv3, 0);  // Should stop at 0
    
    // Jump loop 4: decrement from 200 to -1
    tl4: jv4--;
    jump_if(jv4 >= 0, tl4);
    TEST_EQU(jv4, -1);  // Should be -1 when loop breaks
    
    // Jump loop 5: decrement until not equal to 5
    tl5: jv5--;
    jump_if(jv5 != 5, tl5);
    TEST_EQU(jv5, 5);  // Should stop at 5
    
    // Advanced jump test: nested labels
    int counter = 0, result = 0;
    tl_outer: counter++;
    if (counter < 3) {
        result += 10;
        jump_if(counter < 3, tl_outer);
    }
    TEST_EQU(counter, 3);
    TEST_EQU(result, 20);
    
    // Edge case: jump with boundary conditions
    int boundary_test = 0;
    tl_boundary: boundary_test++;
    jump_if(boundary_test < 1, tl_boundary);
    TEST_EQU(boundary_test, 1);
    
    // ==================== CSTRING_MICROS TESTS ====================
    
    // Test 1: length() function
    cstring(s1,) = "09iie8";
    TEST_EQU(length(s1), 6);
    
    cstring(s_empty,) = "";
    TEST_EQU(length(s_empty), 0);
    
    cstring(s_single,) = "A";
    TEST_EQU(length(s_single), 1);
    
    cstring(s_long,) = "This is a longer test string";
    TEST_EQU(length(s_long), 28);
    
    // Test 2: equal() function
    cstring(s2,) = "88938";
    TEST_EQU(equal(s1, s2), false); // Different strings
    TEST_EQU(length(s2), 5);
    
    cstring(s3,) = "88938";
    TEST_EQU(equal(s2, s3), true); // Identical strings
    
    cstring(s_test1,) = "test";
    cstring(s_test2,) = "test";
    TEST_EQU(equal(s_test1, s_test2), true);
    
    cstring(s_test3,) = "Test";
    TEST_EQU(equal(s_test1, s_test3), false); // Case sensitive
    
    TEST_EQU(equal(NULL, s_test1), false); // NULL check
    TEST_EQU(equal(s_test1, NULL), false); // NULL check
    
    // Test 3: is_empty() function
    TEST_EQU(is_empty(s3), false);
    TEST_EQU(is_empty(s_empty), true);
    TEST_EQU(is_empty(NULL), true); // NULL is empty
    
    // Test 4: exist() function - check if character exists
    TEST_EQU(exist(s2, '8'), true); // '8' exists in "88938"
    TEST_EQU(exist(s2, '3'), true); // '3' exists
    TEST_EQU(exist(s2, 'i'), false); // 'i' doesn't exist
    TEST_EQU(exist(s2, '9'), true); // '9' exists
    
    cstring(s_alpha,) = "abcdefghijklmnopqrstuvwxyz";
    TEST_EQU(exist(s_alpha, 'a'), true);
    TEST_EQU(exist(s_alpha, 'z'), true);
    TEST_EQU(exist(s_alpha, 'm'), true);
    TEST_EQU(exist(s_alpha, 'A'), false); // Case sensitive
    
    // Test 5: concatenate() function
    cstring(s_concat1, 100) = "Hello";
    cstring(s_concat2,) = " World";
    cstring(s_result,) = concatenate(s_concat1, s_concat2);
    TEST_EQU(length(s_result), 11); // "Hello World" is 11 chars
    TEST_EQU(equal(s_result, "Hello World"), true);
    
    cstring(s_c1, 50) = "Test";
    cstring(s_c2,) = "123";
    concatenate(s_c1, s_c2);
    TEST_EQU(equal(s_c1, "Test123"), true);
    
    // Test concatenate with empty string
    cstring(s_c3, 50) = "Base";
    cstring(s_c4,) = "";
    concatenate(s_c3, s_c4);
    TEST_EQU(equal(s_c3, "Base"), true); // Should remain unchanged
    
    // Test 6: sub_exist() function - check if substring exists
    TEST_EQU(sub_exist(s2, "938"), true); // "938" exists in "88938"
    TEST_EQU(sub_exist(s2, "88"), true); // "88" exists at start
    TEST_EQU(sub_exist(s2, "8"), true); // "8" exists
    TEST_EQU(sub_exist(s2, "88k"), false); // "88k" doesn't exist
    TEST_EQU(sub_exist(s2, "xyz"), false); // "xyz" doesn't exist
    
    cstring(s_sub1,) = "MetaCoreSystem";
    TEST_EQU(sub_exist(s_sub1, "Meta"), true);
    TEST_EQU(sub_exist(s_sub1, "Core"), true);
    TEST_EQU(sub_exist(s_sub1, "System"), true);
    TEST_EQU(sub_exist(s_sub1, "CoreSys"), true); // Overlapping match
    TEST_EQU(sub_exist(s_sub1, "meta"), false); // Case sensitive
    TEST_EQU(sub_exist(s_sub1, "xyz"), false);
    
    // Test 7: count() function - count character occurrences
    TEST_EQU(count(s2, '8'), 3); // "88938" has three '8's (positions 0, 1, 4)
    TEST_EQU(count(s1, 'i'), 2); // "09iie8" has two 'i's
    TEST_EQU(count(s1, 'e'), 1); // "09iie8" has one 'e'
    TEST_EQU(count(s1, '0'), 1); // "09iie8" has one '0'
    
    cstring(s_count,) = "aaaaabbbccc";
    TEST_EQU(count(s_count, 'a'), 5);
    TEST_EQU(count(s_count, 'b'), 3);
    TEST_EQU(count(s_count, 'c'), 3);
    TEST_EQU(count(s_count, 'd'), 0); // Character doesn't exist
    
    cstring(s_special,) = "...***===***...";
    TEST_EQU(count(s_special, '.'), 6);
    TEST_EQU(count(s_special, '*'), 6);
    TEST_EQU(count(s_special, '='), 3);
    
    // Test 8: cstr_empty() function
    cstring(s_to_empty, 100) = "ToBeCleared";
    TEST_EQU(is_empty(s_to_empty), false);
    cstr_empty(s_to_empty);
    TEST_EQU(is_empty(s_to_empty), true); // Should be empty now
    
    // Test 9: cstr_free() function
    cstring(s_temp1,) = "test1";
    cstr_free(s_temp1);  // Should free without error
    
    cstring(s_temp2,) = "";
    cstr_free(s_temp2);  // Should free empty string
    
    // ==================== EDGE CASES AND SPECIAL CHARACTERS ====================
    
    // Test with special characters
    cstring(s_special_chars,) = "\n\t\r\\";
    TEST_EQU(length(s_special_chars), 4); // 4 escape sequences
    
    // Test with numeric strings
    cstring(s_numeric,) = "1234567890";
    TEST_EQU(length(s_numeric), 10);
    TEST_EQU(count(s_numeric, '1'), 1);
    TEST_EQU(exist(s_numeric, '5'), true);
    
    // Test with mixed case
    cstring(s_mixed,) = "AbCdEfGhIj";
    TEST_EQU(length(s_mixed), 10);
    TEST_EQU(count(s_mixed, 'A'), 1);
    TEST_EQU(count(s_mixed, 'a'), 0); // Case sensitive
    
    // ==================== TEST COBJECT_DATA CONSTANTS ====================
    // These values are defined in CObjectData.c
    
    // Verify const values are properly compiled
    TEST_EQU(value1, true); // cbool(value1, true)
    TEST_EQU(value2, '9'); // cchar(value2, '9')
    TEST_EQU(value3, 8880); // cshort(value3, 8880)
    TEST_EQU(value4, 199983); // cint(value4, 199983)
    TEST_EQU(value5, 10009389); // clong(value5, 10009389)
    
    TEST_EQU(value6, 199); // cuint8(value6, 199)
    TEST_EQU(value7, 8889); // cuint16(value7, 8889)
    TEST_EQU(value8, 98883); // cuint32(value8, 98883)
    TEST_EQU(value9, 998938); // cuint64(value9, 998938)
    
    TEST_EQU(value10, -10); // cint8(value10, -10)
    TEST_EQU(value11, -1183); // cint16(value11, -1183)
    TEST_EQU(value12, -77787); // cint32(value12, -77787)
    TEST_EQU(value13, -188388); // cint64(value13, -188388)
    
    // Float/Double comparison with tolerance
    float diff14 = value14 > 2.88 ? value14 - 2.88 : 2.88 - value14;
    TEST_EQU(diff14 < 0.01f, true); // value14 ≈ 2.89
    
    // Test cstring and arrays
    TEST_EQU(length(value17), 3); // cstring(value17, "ken")
    TEST_EQU(equal(value17, "ken"), true);
    
    // Array tests
    TEST_EQU(value18[0], 19);
    TEST_EQU(value18[1], 38);
    TEST_EQU(value18[2], 183);
    TEST_EQU(value18[3], 198);
    
    // Test cdynamic macro
    TEST_EQU(value20, 880); // cdynamic(value20, 880)
    
    // ==================== COMPREHENSIVE STRING OPERATIONS ====================
    
    // Multiple operations in sequence
    cstring(s_ops, 200) = "Start";
    TEST_EQU(length(s_ops), 5);
    concatenate(s_ops, "-Middle");
    TEST_EQU(length(s_ops), 12);
    concatenate(s_ops, "-End");
    TEST_EQU(length(s_ops), 16);
    TEST_EQU(equal(s_ops, "Start-Middle-End"), true);
    
    TEST_EQU(exist(s_ops, '-'), true);
    TEST_EQU(count(s_ops, '-'), 2); // Two dashes
    TEST_EQU(sub_exist(s_ops, "Middle"), true);
    TEST_EQU(sub_exist(s_ops, "Start-Middle"), true);

TEST_EXIT(true)