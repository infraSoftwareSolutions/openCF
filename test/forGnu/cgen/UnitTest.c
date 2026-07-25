#define OPENCF_FOR_GNU
#include "cfrost.h"
#include "cfrost/cgen/UnitTest.h"

/**
 * @file UnitTest.c
 * @brief Comprehensive test suite for UnitTest library functionality
 * @details Tests OCF_TEST object creation, result tracking, and various test functions
 *          for multiple data types including boolean, char, short, int, size_t, long,
 *          float, double, and string testing.
 */

OCF_TEST_MAIN(cgen: UnitTest);
    
    // ==================== OCF_TEST OBJECT CREATION AND MANAGEMENT ====================
    
    // Test creating OCF_TEST objects with boolean values
    OCF_TEST test_bool_1 = ocf_test_new(test_bool_1, "Boolean Test 1", "Testing true value", true);
    OCF_TEST_EQU(test_bool_1.name != NULL, true);
    OCF_TEST_EQU(test_bool_1.result, true);
    OCF_TEST_EQU(strlen(test_bool_1.name) > 0, true);
    
    OCF_TEST test_bool_2 = ocf_test_new(test_bool_2, "Boolean Test 2", "Testing false value", false);
    OCF_TEST_EQU(test_bool_2.result, false);
    OCF_TEST_EQU(get_result(test_bool_2), false);
    
    // Test creating OCF_TEST with NULL name and description
    OCF_TEST test_null = ocf_test_new(test_null, NULL, NULL, true);
    OCF_TEST_EQU(test_null.name != NULL, true);
    OCF_TEST_EQU(test_null.description != NULL, true);
    OCF_TEST_EQU(test_null.result, true);
    
    // Test OCF_TEST counter incrementation
    OCF_TEST test_counter_1 = ocf_test_new(test_counter_1, "Counter Test 1", "", true);
    OCF_TEST test_counter_2 = ocf_test_new(test_counter_2, "Counter Test 2", "", true);
    OCF_TEST_EQU(test_counter_2.num > test_counter_1.num, true);
    
    // ==================== BASIC TEST FUNCTIONS - BOOLEAN TYPE ====================
    
    // Test basic_test_bool without details
    bool bool_result_1 = basic_test_bool(true, true, false, 20, '-');
    OCF_TEST_EQU(bool_result_1, true);
    
    bool bool_result_2 = basic_test_bool(false, false, false, 20, '-');
    OCF_TEST_EQU(bool_result_2, true);
    
    bool bool_result_3 = basic_test_bool(true, false, false, 20, '-');
    OCF_TEST_EQU(bool_result_3, false);
    
    // ==================== BASIC TEST FUNCTIONS - CHAR TYPE ====================
    
    // Test basic_test_char
    bool char_result_1 = basic_test_char('A', 'A', false, 20, '-');
    OCF_TEST_EQU(char_result_1, true);
    
    bool char_result_2 = basic_test_char('B', 'A', false, 20, '-');
    OCF_TEST_EQU(char_result_2, false);
    
    bool char_result_3 = basic_test_char('\n', '\n', false, 20, '-');
    OCF_TEST_EQU(char_result_3, true);
    
    bool char_result_4 = basic_test_char('\t', '\t', false, 20, '-');
    OCF_TEST_EQU(char_result_4, true);
    
    // ==================== BASIC TEST FUNCTIONS - SHORT TYPE ====================
    
    // Test basic_test_short
    bool short_result_1 = basic_test_short(100, 100, false, 20, '-');
    OCF_TEST_EQU(short_result_1, true);
    
    bool short_result_2 = basic_test_short(-500, -500, false, 20, '-');
    OCF_TEST_EQU(short_result_2, true);
    
    bool short_result_3 = basic_test_short(32767, 32767, false, 20, '-');
    OCF_TEST_EQU(short_result_3, true);
    
    bool short_result_4 = basic_test_short(-32768, -32768, false, 20, '-');
    OCF_TEST_EQU(short_result_4, true);
    
    bool short_result_5 = basic_test_short(100, 200, false, 20, '-');
    OCF_TEST_EQU(short_result_5, false);
    
    // ==================== BASIC TEST FUNCTIONS - INT TYPE ====================
    
    // Test basic_test_int
    bool int_result_1 = basic_test_int(42, 42, false, 20, '-');
    OCF_TEST_EQU(int_result_1, true);
    
    bool int_result_2 = basic_test_int(-1000, -1000, false, 20, '-');
    OCF_TEST_EQU(int_result_2, true);
    
    bool int_result_3 = basic_test_int(0, 0, false, 20, '-');
    OCF_TEST_EQU(int_result_3, true);
    
    bool int_result_4 = basic_test_int(2147483647, 2147483647, false, 20, '-');
    OCF_TEST_EQU(int_result_4, true);

    bool int_result_5 = basic_test_int(100, 200, false, 20, '-');
    OCF_TEST_EQU(int_result_5, false);
    
    // ==================== BASIC TEST FUNCTIONS - SIZE_T TYPE ====================
    
    // Test basic_test_size
    bool size_result_1 = basic_test_size(0, 0, false, 20, '-');
    OCF_TEST_EQU(size_result_1, true);
    
    bool size_result_2 = basic_test_size(1024, 1024, false, 20, '-');
    OCF_TEST_EQU(size_result_2, true);
    
    bool size_result_3 = basic_test_size(999999, 999999, false, 20, '-');
    OCF_TEST_EQU(size_result_3, true);
    
    bool size_result_4 = basic_test_size(100, 200, false, 20, '-');
    OCF_TEST_EQU(size_result_4, false);
    
    // ==================== BASIC TEST FUNCTIONS - LONG TYPE ====================
    
    // Test basic_test_long
    bool long_result_1 = basic_test_long(100000L, 100000L, false, 20, '-');
    OCF_TEST_EQU(long_result_1, true);
    
    bool long_result_2 = basic_test_long(-999999L, -999999L, false, 20, '-');
    OCF_TEST_EQU(long_result_2, true);
    
    bool long_result_3 = basic_test_long(0L, 0L, false, 20, '-');
    OCF_TEST_EQU(long_result_3, true);
    
    bool long_result_4 = basic_test_long(100000L, 200000L, false, 20, '-');
    OCF_TEST_EQU(long_result_4, false);
    
    // ==================== BASIC TEST FUNCTIONS - FLOAT TYPE ====================
    
    // Test basic_test_float with exact values
    bool float_result_1 = basic_test_float(3.14f, 3.14f, false, 20, '-', 0.01f);
    OCF_TEST_EQU(float_result_1, true);
    
    bool float_result_2 = basic_test_float(2.5f, 2.5f, false, 20, '-', 0.01f);
    OCF_TEST_EQU(float_result_2, true);
    
    bool float_result_3 = basic_test_float(0.0f, 0.0f, false, 20, '-', 0.01f);
    OCF_TEST_EQU(float_result_3, true);
    
    // Test float with tolerance
    bool float_result_4 = basic_test_float(10.01f, 10.0f, false, 20, '-', 0.5f);
    OCF_TEST_EQU(float_result_4, true);
    
    bool float_result_5 = basic_test_float(10.1f, 10.0f, false, 20, '-', 0.5f);
    OCF_TEST_EQU(float_result_5, false);
    
    // Test float with high resolution warning
    bool float_result_6 = basic_test_float(1.0f, 1.0f, false, 20, '-', 10.0f);
    OCF_TEST_EQU(float_result_6, true);
    
    // ==================== BASIC TEST FUNCTIONS - DOUBLE TYPE ====================
    
    // Test basic_test_double with exact values
    bool double_result_1 = basic_test_double(3.14159, 3.14159, false, 20, '-', 0.01);
    OCF_TEST_EQU(double_result_1, true);
    
    bool double_result_2 = basic_test_double(2.71828, 2.71828, false, 20, '-', 0.01);
    OCF_TEST_EQU(double_result_2, true);
    
    bool double_result_3 = basic_test_double(0.0, 0.0, false, 20, '-', 0.01);
    OCF_TEST_EQU(double_result_3, true);
    
    // Test double with tolerance
    bool double_result_4 = basic_test_double(100.05, 100.0, false, 20, '-', 0.5);
    OCF_TEST_EQU(double_result_4, true);
    
    bool double_result_5 = basic_test_double(100.1, 100.0, false, 20, '-', 0.5);
    OCF_TEST_EQU(double_result_5, false);

    // Test double with high resolution warning
    bool double_result_6 = basic_test_double(1.0, 1.0, false, 20, '-', 10.0);
    OCF_TEST_EQU(double_result_6, true);
    
    // ==================== STRING TEST FUNCTION ====================
    
    // Test string_test with identical strings
    bool string_result_1 = string_test("Hello", "Hello", false, 20, '-');
    OCF_TEST_EQU(string_result_1, true);
    
    bool string_result_2 = string_test("", "", false, 20, '-');
    OCF_TEST_EQU(string_result_2, true);
    
    bool string_result_3 = string_test("Test123", "Test123", false, 20, '-');
    OCF_TEST_EQU(string_result_3, true);
    
    // Test string_test with different strings
    bool string_result_4 = string_test("Hello", "World", false, 20, '-');
    OCF_TEST_EQU(string_result_4, false);
    
    // Test string_test with different lengths
    bool string_result_5 = string_test("Hi", "Hello", false, 20, '-');
    OCF_TEST_EQU(string_result_5, false);
    
    bool string_result_6 = string_test("A", "B", false, 20, '-');
    OCF_TEST_EQU(string_result_6, false);
    
    // ==================== OCF_TEST CREATION FUNCTIONS - TYPED VARIANTS ====================
    
    // Test ctest_bool
    OCF_TEST ctest_bool_1 = ocf_test_b(true, true, "Bool Test Pass", "Comparing true values");
    OCF_TEST_EQU(ctest_bool_1.result, true);
    OCF_TEST_EQU(strlen(ctest_bool_1.name) > 0, true);
    
    OCF_TEST ctest_bool_2 = ocf_test_b(false, true, "Bool Test Fail", "Comparing different bool values");
    OCF_TEST_EQU(ctest_bool_2.result, false);
    
    // Test ctest_char
    OCF_TEST ctest_char_1 = ocf_test_c('X', 'X', "Char Test Pass", "Comparing identical chars");
    OCF_TEST_EQU(ctest_char_1.result, true);
    
    OCF_TEST ctest_char_2 = ocf_test_c('A', 'B', "Char Test Fail", "Comparing different chars");
    OCF_TEST_EQU(ctest_char_2.result, false);

    // Test ctest_short
    OCF_TEST ctest_short_1 = ocf_test_sh(1000, 1000, "Short Test Pass", "Comparing identical shorts");
    OCF_TEST_EQU(ctest_short_1.result, true);
    
    OCF_TEST ctest_short_2 = ocf_test_sh(500, 1000, "Short Test Fail", "Comparing different shorts");
    OCF_TEST_EQU(ctest_short_2.result, false);
    
    // Test ctest_int
    OCF_TEST ctest_int_1 = ocf_test_i(42, 42, "Int Test Pass", "Comparing identical integers");
    OCF_TEST_EQU(ctest_int_1.result, true);
    
    OCF_TEST ctest_int_2 = ocf_test_i(10, 20, "Int Test Fail", "Comparing different integers");
    OCF_TEST_EQU(ctest_int_2.result, false);
    
    // Test ctest_size
    OCF_TEST ctest_size_1 = ocf_test_sz(512, 512, "Size Test Pass", "Comparing identical size_t values");
    OCF_TEST_EQU(ctest_size_1.result, true);
    
    OCF_TEST ctest_size_2 = ocf_test_sz(100, 200, "Size Test Fail", "Comparing different size_t values");
    OCF_TEST_EQU(ctest_size_2.result, false);
    
    // Test ctest_long
    OCF_TEST ctest_long_1 = ocf_test_l(999999L, 999999L, "Long Test Pass", "Comparing identical long values");
    OCF_TEST_EQU(ctest_long_1.result, true);
    
    OCF_TEST ctest_long_2 = ocf_test_l(100L, 200L, "Long Test Fail", "Comparing different long values");
    OCF_TEST_EQU(ctest_long_2.result, false);
    
    // Test ctest_float
    OCF_TEST ctest_float_1 = ocf_test_f(3.14f, 3.14f, 0.01f, "Float Test Pass", "Comparing identical floats");
    OCF_TEST_EQU(ctest_float_1.result, true);
    
    OCF_TEST ctest_float_2 = ocf_test_f(1.5f, 1.6f, 0.5f, "Float Test Pass Tolerance", "Comparing floats within tolerance");
    OCF_TEST_EQU(ctest_float_2.result, true);
    
    OCF_TEST ctest_float_3 = ocf_test_f(1.0f, 2.0f, 0.01f, "Float Test Fail", "Comparing very different floats");
    OCF_TEST_EQU(ctest_float_3.result, false);
    
    // Test ctest_double
    OCF_TEST ctest_double_1 = ocf_test_d(3.14159, 3.14159, 0.01, "Double Test Pass", "Comparing identical doubles");
    OCF_TEST_EQU(ctest_double_1.result, true);
    
    OCF_TEST ctest_double_2 = ocf_test_d(2.0, 2.01, 0.5, "Double Test Pass Tolerance", "Comparing doubles within tolerance");
    OCF_TEST_EQU(ctest_double_2.result, true);
    
    OCF_TEST ctest_double_3 = ocf_test_d(1.0, 5.0, 0.01, "Double Test Fail", "Comparing very different doubles");
    OCF_TEST_EQU(ctest_double_3.result, false);
    
    // Test string_ctest
    OCF_TEST string_ctest_1 = ocf_test_str("MetaCore", "MetaCore", "String Test Pass", "Comparing identical strings");
    OCF_TEST_EQU(string_ctest_1.result, true);
    
    OCF_TEST string_cOCF_TEST_EQU = ocf_test_str("Hello", "World", "String Test Fail", "Comparing different strings");
    OCF_TEST_EQU(string_cOCF_TEST_EQU.result, false);
    
    OCF_TEST string_ctest_3 = ocf_test_str("Test", "Testing", "String Test Length Fail", "Comparing strings with different lengths");
    OCF_TEST_EQU(string_ctest_3.result, false);
    
    // ==================== TEST STREAM STRUCT TESTS ====================
    
    // Test test_stream initialization
    ocf_test_stream ts = {false, 20, '-', 0, 0, 0};
    OCF_TEST_EQU(ts.details, false);
    OCF_TEST_EQU(ts.seplen, 20);
    OCF_TEST_EQU(ts.sepch, '-');
    OCF_TEST_EQU(ts.success_tests, 0);
    OCF_TEST_EQU(ts.failed_tests, 0);
    OCF_TEST_EQU(ts.total_tests, 0);
    
    // Test test_stream with details enabled
    ocf_test_stream ts_detail = {true, 30, '=', 0, 0, 0};
    OCF_TEST_EQU(ts_detail.details, true);
    OCF_TEST_EQU(ts_detail.seplen, 30);
    OCF_TEST_EQU(ts_detail.sepch, '=');
    
    // ==================== GET_RESULT FUNCTION TESTS ====================
    
    OCF_TEST test_result_1 = ocf_test_new(test_result_1, "Result Test 1", "Testing get_result", true);
    OCF_TEST_EQU(get_result(test_result_1), true);
    
    OCF_TEST test_result_2 = ocf_test_new(test_result_2, "Result Test 2", "Testing get_result", false);
    OCF_TEST_EQU(get_result(test_result_2), false);
    
    // ==================== PRINT TEST FUNCTION (Functional Test) ====================
    
    // Note: printTest writes to console but we verify it doesn't crash
    OCF_TEST test_print = ocf_test_new(test_print, "Print Test", "Testing printTest function", true);
    printTest(test_print);  // Should print without crashing
    TEST_0(test_print.name != NULL);
    
    // ==================== EDGE CASES AND SPECIAL VALUES ====================
    
    // Test with special floating point values
    bool float_edge_1 = basic_test_float(-3.14f, -3.14f, false, 20, '-', 0.01f);
    OCF_TEST_EQU(float_edge_1, true);
    
    bool double_edge_1 = basic_test_double(-3.14159, -3.14159, false, 20, '-', 0.01);
    OCF_TEST_EQU(double_edge_1, true);
    
    // Test with boundary integer values
    bool int_edge_1 = basic_test_int(-2147483648, -2147483648, false, 20, '-');
    OCF_TEST_EQU(int_edge_1, true);
    
    // Test character edge cases
    bool char_edge_1 = basic_test_char(0, 0, false, 20, '-');
    OCF_TEST_EQU(char_edge_1, true);
    
    bool char_edge_2 = basic_test_char(255, 255, false, 20, '-');
    OCF_TEST_EQU(char_edge_2, true);
    
    // Test string with special characters
    bool string_edge_1 = string_test("\n\t", "\n\t", false, 20, '-');
    OCF_TEST_EQU(string_edge_1, true);
    
    // Test OCF_TEST with empty strings
    OCF_TEST test_empty = ocf_test_new(test_empty, "", "", true);
    OCF_TEST_EQU(test_empty.name != NULL, true);
    OCF_TEST_EQU(test_empty.description != NULL, true);

OCF_TEST_EXIT(true)