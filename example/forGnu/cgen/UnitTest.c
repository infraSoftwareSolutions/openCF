#define OPENCF_FOR_GNU

#include "cfrost/cgen/UnitTest.h"
#include "cfrost/structure.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

ocf_main_empty {
    printf("|========================================================|\n");
    printf("|         UnitTest Framework - Practical Examples        |\n");
    printf("|========================================================|\n\n");

    // ============================================================
    // Example 1: OCF_TEST Structure - Create and Display Tests
    // ============================================================
    printf("EXAMPLE 1: OCF_TEST Structure Basics\n");
    printf("-------------------------------------\n");
    
    OCF_TEST test1;
    test1 = ocf_test_new(test1, "Boolean Test", "Testing true == true", true);
    printTest(test1);
    
    OCF_TEST test2;
    test2 = ocf_test_new(test2, "Arithmetic Test", "Testing 5 + 3 == 8", 5 + 3 == 8);
    printTest(test2);

    // ============================================================
    // Example 2: Basic Test Functions - Boolean
    // ============================================================
    printf("EXAMPLE 2: Testing Boolean Values\n");
    printf("------------------------------------\n");
    
    bool actual_bool = true;
    bool expected_bool = true;
    
    bool result = ocf_test_basic_b(actual_bool, expected_bool, true, 40, '=');
    printf("Result: %s\n\n", result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 3: Basic Test Functions - Character
    // ============================================================
    printf("EXAMPLE 3: Testing Character Values\n");
    printf("--------------------------------------\n");
    
    char ch_actual = 'A';
    char ch_expected = 'A';
    
    bool ch_result = ocf_test_basic_c(ch_actual, ch_expected, true, 40, '-');
    printf("Result: %s\n\n", ch_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 4: Basic Test Functions - Integer
    // ============================================================
    printf("EXAMPLE 4: Testing Integer Values\n");
    printf("------------------------------------\n");
    
    int actual_int = 100;
    int expected_int = 100;
    
    bool int_result = ocf_test_basic_i(actual_int, expected_int, true, 40, '*');
    printf("Result: %s\n\n", int_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 5: Basic Test Functions - Float with Tolerance
    // ============================================================
    printf("EXAMPLE 5: Testing Float Values (with tolerance)\n");
    printf("----------------------------------------------------\n");
    
    float actual_float = 3.14f;
    float expected_float = 3.14f;
    
    bool float_result = ocf_test_basic_f(actual_float, expected_float, true, 40, '=', 0.1f);
    printf("Result: %s\n\n", float_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 6: Basic Test Functions - Double
    // ============================================================
    printf("EXAMPLE 6: Testing Double Values\n");
    printf("-----------------------------------\n");
    
    double actual_double = 2.71828;
    double expected_double = 2.71828;
    
    bool double_result = ocf_test_basic_d(actual_double, expected_double, true, 40, '-', 0.01);
    printf("Result: %s\n\n", double_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 7: String Testing
    // ============================================================
    printf("EXAMPLE 7: Testing C-Style Strings\n");
    printf("--------------------------------------\n");
    
    const char *str1 = "Hello";
    const char *str2 = "Hello";
    
    bool string_result = ocf_test_basic_str(str1, str2, true, 40, '=');
    printf("Result: %s\n\n", string_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 8: OCF_TEST Variants - ocf_test_i
    // ============================================================
    printf("EXAMPLE 8: Using ocf_test_i Function\n");
    printf("--------------------------------------\n");
    
    OCF_TEST math_test = ocf_test_i(2 + 3, 5, "Addition", "Testing 2 + 3 == 5");
    printTest(math_test);
    printf("Result: %s\n\n", get_result(math_test) ? "PASSED" : "FAILED");

    // ============================================================
    // Example 9: OCF_TEST Variants - ocf_test_b
    // ============================================================
    printf("EXAMPLE 9: Using ocf_test_b Function\n");
    printf("--------------------------------------\n");
    
    OCF_TEST logic_test = ocf_test_b(true && true, true, "Logic AND", "Testing true AND true == true");
    printTest(logic_test);

    // ============================================================
    // Example 10: OCF_TEST Variants - ocf_test_f
    // ============================================================
    printf("EXAMPLE 10: Using ocf_test_f Function\n");
    printf("----------------------------------------\n");
    
    OCF_TEST precision_test = ocf_test_f(3.14159f, 3.14159f, 0.1f, "Pi Value", "Testing PI precision");
    printTest(precision_test);

    // ============================================================
    // Example 11: OCF_TEST Variants - ocf_test_str
    // ============================================================
    printf("EXAMPLE 11: Using ocf_test_str Function\n");
    printf("-----------------------------------------\n");
    
    OCF_TEST str_OCF_TEST = ocf_test_str("MetaCore", "MetaCore", "String Equality", "Testing library name");
    printTest(str_OCF_TEST);

    // ============================================================
    // Example 12: ocf_test_stream Structure - Basic Usage
    // ============================================================
    printf("EXAMPLE 12: ocf_test_stream Structure\n");
    printf("--------------------------------------\n");
    
    ocf_test_stream ts;
    ts.details = true;
    ts.seplen = 40;
    ts.sepch = '*';
    ts.success_tests = 0;
    ts.failed_tests = 0;
    ts.total_tests = 0;
    
    printf("Created ocf_test_stream with settings:\n");
    printf("  Details: %s\n", ts.details ? "true" : "false");
    printf("  Separator: '%c' with length %u\n\n", ts.sepch, ts.seplen);

    // ============================================================
    // Example 13: Adding Multiple Tests to Stream
    // ============================================================
    printf("EXAMPLE 13: Batch Testing with ocf_test_stream\n");
    printf("----------------------------------------------\n\n");
    
    // Create a fresh test stream
    ocf_test_stream batch_tests;
    batch_tests.details = false;  // Disable detailed output for batch
    batch_tests.seplen = 35;
    batch_tests.sepch = '-';
    batch_tests.success_tests = 0;
    batch_tests.failed_tests = 0;
    batch_tests.total_tests = 0;
    
    // Add boolean tests
    batch_tests = ocf_add_test_bool(batch_tests, true, true, false);
    batch_tests = ocf_add_test_bool(batch_tests, false, false, false);
    batch_tests = ocf_add_test_bool(batch_tests, true, false, false);
    
    // Add integer tests
    batch_tests = ocf_add_test_int(batch_tests, 5, 5, false);
    batch_tests = ocf_add_test_int(batch_tests, 10, 20, false);
    batch_tests = ocf_add_test_int(batch_tests, 42, 42, false);
    
    // Add float tests
    batch_tests = ocf_add_test_float(batch_tests, 3.14f, 3.14f, false);
    batch_tests = ocf_add_test_float(batch_tests, 2.71f, 2.72f, false);
    
    // Add double tests
    batch_tests = ocf_add_test_double(batch_tests, 1.414, 1.414, false);
    batch_tests = ocf_add_test_double(batch_tests, 1.732, 1.733, false);
    
    // Print summary
    print(batch_tests);
    NewLines(1);

    // ============================================================
    // Example 14: ASR and AFR Calculation
    // ============================================================
    printf("EXAMPLE 14: Success and Failure Rate Calculation\n");
    printf("--------------------------------------------------\n");
    
    ocf_test_stream rate_tests;
    rate_tests.success_tests = 7;
    rate_tests.failed_tests = 3;
    rate_tests.total_tests = 10;
    
    float success_rate = OCF_ASR(rate_tests);
    float failure_rate = OCF_AFR(rate_tests);
    
    printf("Test Statistics:\n");
    printf("  Passed: %zu\n", rate_tests.success_tests);
    printf("  Failed: %zu\n", rate_tests.failed_tests);
    printf("  Total: %zu\n", rate_tests.total_tests);
    printf("  Average Success Rate (ASR): %.2f%%\n", success_rate);
    printf("  Average Failure Rate (AFR): %.2f%%\n\n", failure_rate);

    // ============================================================
    // Example 15: Practical Use Case - Calculator Module Tests
    // ============================================================
    printf("EXAMPLE 15: Practical Use - Calculator Module\n");
    printf("----------------------------------------------\n\n");
    
    ocf_test_stream calc_tests;
    calc_tests.details = false;
    calc_tests.seplen = 40;
    calc_tests.sepch = '=';
    calc_tests.success_tests = 0;
    calc_tests.failed_tests = 0;
    calc_tests.total_tests = 0;
    
    printf("Running Calculator Tests:\n");
    
    // Test addition
    calc_tests = ocf_add_test_int(calc_tests, 5 + 3, 8, false);
    printf("✓ Addition: 5 + 3 = 8\n");
    
    // Test subtraction
    calc_tests = ocf_add_test_int(calc_tests, 10 - 4, 6, false);
    printf("✓ Subtraction: 10 - 4 = 6\n");
    
    // Test multiplication
    calc_tests = ocf_add_test_int(calc_tests, 7 * 6, 42, false);
    printf("✓ Multiplication: 7 * 6 = 42\n");
    
    // Test division
    calc_tests = ocf_add_test_float(calc_tests, 15.0f / 3.0f, 5.0f, false);
    printf("✓ Division: 15.0 / 3.0 = 5.0\n");
    
    // Test power
    calc_tests = ocf_add_test_float(calc_tests, powf(2.0f, 8.0f), 256.0f, false);
    printf("✓ Power: 2^8 = 256\n\n");
    
    print(calc_tests);
    NewLines(1);

    // ============================================================
    // Example 16: Practical Use Case - String Processing Tests
    // ============================================================
    printf("EXAMPLE 16: Practical Use - String Processing\n");
    printf("-----------------------------------------------\n\n");
    
    ocf_test_stream string_tests;
    string_tests.details = false;
    string_tests.seplen = 40;
    string_tests.sepch = '-';
    string_tests.success_tests = 0;
    string_tests.failed_tests = 0;
    string_tests.total_tests = 0;
    
    // Test string length
    const char *test_str = "Hello";
    string_tests = ocf_add_test_size(string_tests, strlen(test_str), 5, false);
    printf("✓ String Length: strlen('Hello') = 5\n");
    
    // Test string comparison
    bool strcmp_result = string_test("MetaCore", "MetaCore", false, 40, '-');
    string_tests = ocf_add_test_bool(string_tests, strcmp_result, true, false);
    printf("✓ String Comparison: 'MetaCore' == 'MetaCore'\n");
    
    // Test character matching
    string_tests = ocf_add_test_char(string_tests, 'A', 'A', false);
    printf("✓ Character Match: 'A' == 'A'\n\n");
    
    print(string_tests);
    NewLines(1);

    // ============================================================
    // Example 17: Practical Use Case - Data Validation Tests
    // ============================================================
    printf("EXAMPLE 17: Practical Use - Data Validation\n");
    printf("----------------------------------------------\n\n");
    
    ocf_test_stream validation_tests;
    validation_tests.details = false;
    validation_tests.seplen = 40;
    validation_tests.sepch = '*';
    validation_tests.success_tests = 0;
    validation_tests.failed_tests = 0;
    validation_tests.total_tests = 0;
    
    // Validate user ID
    int user_id = 12345;
    validation_tests = ocf_add_test_int(validation_tests, user_id > 0 ? 1 : 0, 1, false);
    printf("✓ User ID validation: %d > 0\n", user_id);
    
    // Validate email format check (simplified)
    bool has_email = true;
    validation_tests = ocf_add_test_bool(validation_tests, has_email, true, false);
    printf("✓ Email field present: %s\n", has_email ? "true" : "false");
    
    // Validate age
    int age = 25;
    validation_tests = ocf_add_test_bool(validation_tests, age >= 18 && age <= 120, true, false);
    printf("✓ Age validation: 18 <= %d <= 120\n\n", age);
    
    print(validation_tests);
    NewLines(1);

    // ============================================================
    // Example 18: Test Statistics Summary
    // ============================================================
    printf("EXAMPLE 18: Complete Test Report\n");
    printf("----------------------------------\n\n");
    
    ocf_test_stream final_report;
    final_report.details = false;
    final_report.seplen = 45;
    final_report.sepch = '=';
    final_report.success_tests = 0;
    final_report.failed_tests = 0;
    final_report.total_tests = 0;
    
    printf("Consolidating all test results...\n\n");
    
    // Aggregate results
    final_report.success_tests = batch_tests.success_tests + calc_tests.success_tests + 
                                  string_tests.success_tests + validation_tests.success_tests;
    final_report.failed_tests = batch_tests.failed_tests + calc_tests.failed_tests + 
                                 string_tests.failed_tests + validation_tests.failed_tests;
    final_report.total_tests = batch_tests.total_tests + calc_tests.total_tests + 
                                string_tests.total_tests + validation_tests.total_tests;
    
    print(final_report);
    NewLines(1);

    // ============================================================
    // Summary
    // ============================================================
    printf("|========================================================|\n");
    printf("|  UnitTest Framework provides comprehensive testing:    |\n");
    printf("|                                                        |\n");
    printf("|  • OCF_TEST - Test object structure                       |\n");
    printf("|  • basic_test_*() - Simple type testing                |\n");
    printf("|  • OCF_TEST_*() - Named test creation                     |\n");
    printf("|  • string_test() - String comparison                   |\n");
    printf("|  • ocf_test_stream - Batch test management                 |\n");
    printf("|  • addTest*() - Add tests to stream                    |\n");
    printf("|  • ASR/AFR - Success/failure rate calculation          |\n");
    printf("|  • print() - Summary report generation                 |\n");
    printf("|                                                        |\n");
    printf("|  Supports: bool, char, short, int, long, size_t,       |\n");
    printf("|            float, double, C-strings                    |\n");
    printf("|========================================================|\n");

    ocf_exit(false);
}