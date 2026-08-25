#ifndef OPENCF___CFROST___TEST_H
#define OPENCF___CFROST___TEST_H

    /**
     * @file include/cfrost/test.h
     * @brief Lightweight C and C++ test utilities implemented as macros.
     *
     * This header defines small, header-only testing helpers for both C and C++.
     * It provides test initialization, assertion helpers, summary printing, and
     * basic benchmark main wrappers without altering existing test logic.
     */
    
    #if defined(OPENCF_FOR_GNU)
        #if defined(__cplusplus)

            #include <string>
            #include <iostream>
            #include <queue>
            #include <chrono>

            /**
             * @def OCF_TEST_SUMMARY
             * @brief Print a C++ test summary using std::cout.
             */
            #define OCF_TEST_SUMMARY                                 \
                std::cout                                            \
                << "\n-------------------------------"               \
                << "\n<<<<<<<<< test summary >>>>>>>>"               \
                << "\n-------------------------------"               \
                << "\nTEST NAME: " << testName                       \
                << "\npassed tests: " << tests_passed                \
                << "\nfailed tests: " << tests_failed                \
                << "\ntotal tests: " << total_tests;                 \
                if (total_tests > 0)                                 \
                {                                                    \
                    std::cout                                        \
                    << "\npassed tests ratio: "                      \
                    << (double)(100 * (tests_passed / total_tests))  \
                    << "\nfailed tests ratio: "                      \
                    << (double)(100 * (tests_failed / total_tests)); \
                }                                                    \
                else                                                 \
                {                                                    \
                    std::cout                                        \
                    << "\npassed tests ratio: 0.0"                   \
                    << "\nfailed tests ratio: 0.0";                  \
                }                                                    \
                std::cout << "\n-------------------------------\n"

            /**
             * @def OCF_TEST_INIT
             * @brief Initialize C++ test counters, flags, and test name.
             * @param name test suite name.
             */
            #define OCF_TEST_INIT(name)   \
                bool warningFlag = false; \
                bool errorFlag = false;   \
                size_t tests_passed = 0;  \
                size_t tests_failed = 0;  \
                size_t total_tests = 0;   \
                std::string testName = #name

            /**
             * @def OCF_TEST_MAIN
             * @brief Start a C++ test program main function and initialize test state.
             * @param name test suite name.
             */
            #define OCF_TEST_MAIN(name) \
                int main() {            \
                    OCF_TEST_INIT(name) \

            /**
             * @def OCF_TEST_EXIT
             * @brief Finish the C++ test main function, optionally print summary, and return status.
             * @param PS print summary flag.
             */
            #define OCF_TEST_EXIT(PS)                          \
                    if(print_summary) OCF_TEST_SUMMARY;        \
                    return (int)(tests_failed || warningFlag); \
                }
            
            /**
             * @def OCF_TEST_ASSERT
             * @brief Evaluate a condition in C++ tests and record failure diagnostics.
             * @param cond condition to assert.
             */
            #define OCF_TEST_ASSERT(cond)              \
                do {                                   \
                    if (cond) { tests_passed++; }      \
                    else                               \
                    {                                  \
                        tests_failed++;                \
                        std::cout                      \
                        << "FAIL:\n"                   \
                        << "\tNUMBER: " << total_tests \
                        << "\tLINE: " << __LINE__      \
                        << "\tFILE: " << __FILE__;     \
                    }                                  \
                    total_tests++;                     \
                } while(false)

            /**
             * @def OCF_TEST_COND
             * @brief Evaluate a boolean condition and update C++ test counters.
             * @param cond condition to evaluate.
             */
            #define OCF_TEST_COND(cond)       \
                do {                          \
                    if (cond) tests_passed++; \
                    else tests_failed++;      \
                    total_tests++;            \
                } while(false)

            /**
             * @def OCF_TEST_RANGE
             * @brief Assert a value lies within an inclusive range in C++ tests.
             * @param value tested value.
             * @param high upper bound.
             * @param low lower bound.
             */
            #define OCF_TEST_RANGE(value, high, low)   \
                do {                                   \
                    if (value <= high && value >= low) \
                    {                                  \
                        tests_passed++;                \
                    }                                  \
                    else                               \
                    {                                  \
                        tests_failed++;                \
                        std::cout                      \
                        << "FAIL:\n"                   \
                        << "\tNUMBER: " << total_tests \
                        << "\tLINE: " << __LINE__      \
                        << "\tFILE: " << __FILE__;     \
                    }                                  \
                    total_tests++;                     \
                } while(false)

            /**
             * @def OCF_TEST_MSG
             * @brief Evaluate a condition and print a failure message in C++ tests.
             * @param cond condition to assert.
             * @param msg failure message.
             */
            #define OCF_TEST_MSG(cond, msg)            \
                do{                                    \
                    if (cond) { tests_passed++; }      \
                    else                               \
                    {                                  \
                        tests_failed++;                \
                        std::cout                      \
                        << "FAIL: " << msg             \
                        << "\tNUMBER: " << total_tests \
                        << "\tLINE: " << __LINE__      \
                        << "\tFILE: " << __FILE__;     \
                    }                                  \
                    total_tests++;                     \
                } while(false)

            /**
             * @def TEST_EQU
             * @brief Assert equality in C++ tests and record diagnostics on failure.
             * @param real actual value.
             * @param expected expected value.
             */
            #define OCF_TEST_EQU(real, expected)              \
                do {                                          \
                    if (real == expected) { tests_passed++; } \
                    else                                      \
                    {                                         \
                        tests_failed++;                       \
                        std::cout                             \
                        << "FAIL:\n"                          \
                        << "\tNUMBER: " << total_tests        \
                        << "\tLINE: " << __LINE__             \
                        << "\tFILE: " << __FILE__;            \
                    }                                         \
                    total_tests++;                            \
                } while(false)

            /**
             * @def TEST_EQU_MSG
             * @brief Assert equality with a failure message in C++ tests.
             * @param real actual value.
             * @param expected expected value.
             * @param msg failure message.
             */
            #define OCF_TEST_EQU_MSG(real, expected, msg)     \
                do {                                          \
                    if (real == expected) { tests_passed++; } \
                    else                                      \
                    {                                         \
                        tests_failed++;                       \
                        std::cout                             \
                        << "FAIL: " << msg                    \
                        << "\tNUMBER: " << total_tests        \
                        << "\tLINE: " << __LINE__             \
                        << "\tFILE: " << __FILE__;            \
                    }                                         \
                    total_tests++;                            \
                } while(false)


            /**
             * @def OCF_BENCHMARK_MAIN
             * @brief Start a benchmark main function with a lightweight benchmark timer.
             */
            #define OCF_BENCHMARK_MAIN \
                int main() {           \
                    auto BMS_start = std::chrono::high_resolution_clock::now();
            
            /**
             * @def OCF_BENCHMARK_EXIT
             * @brief Finish benchmark main and optionally print a benchmark summary.
             * @param PS print summary flag.
             */
            #define OCF_BENCHMARK_EXIT(PS)                                         \
                    if(PS)                                                         \
                    {                                                              \
                        auto BMS_end = std::chrono::high_resolution_clock::now();  \
                        auto BMS_elapsed =                                         \
                            std::chrono::duration_cast<std::chrono::microseconds>( \
                                BMS_end - BMS_start                                \
                            ).count();                                             \
                        std::cout << "\nBenchmark elapsed: "                       \
                                << BMS_elapsed                                     \
                                << " microseconds\n";                              \
                    }                                                              \
                    return 0;                                                      \
                }
        #else
            #include <stdio.h>

            /**
             * @def CTEST_INIT
             * @brief Initialize C test counters and set the test suite name.
             * @param name test suite name.
             */
            #define OCF_TEST_INIT(name)  \
                size_t tests_passed = 0; \
                size_t tests_failed = 0; \
                size_t total_tests = 0;  \
                char testName[] = #name

            /**
             * @def OCF_TEST_SUMMARY
             * @brief Print a formatted C test summary to stdout.
             */
            #define OCF_TEST_SUMMARY                           \
                printf("\n-------------------------------");   \
                printf("\n<<<<<<<<< test summary >>>>>>>>");   \
                printf("\n-------------------------------");   \
                printf("\nTEST NAME: %s", testName);           \
                printf("\npassed tests: %i", tests_passed);    \
                printf("\nfailed tests: %i", tests_failed);    \
                printf("\ntotal tests: %i", total_tests);      \
                if (total_tests > 0)                           \
                {                                              \
                    printf(                                    \
                        "\npassed tests ratio: %f",            \
                        (double)                               \
                        (100 * (tests_passed / total_tests))); \
                    printf(                                    \
                        "\nfailed tests ratio: %f",            \
                        (double)                               \
                        (100 * (tests_failed / total_tests))); \
                }                                              \
                else                                           \
                {                                              \
                    printf("\npassed tests ratio: 0.0");       \
                    printf("\nfailed tests ratio: 0.0");       \
                }                                              \
                printf("\n-------------------------------\n")

            /**
             * @def OCF_TEST_MAIN
             * @brief Start a C test program main function and initialize counters.
             * @param name test suite name.
             */
            #define OCF_TEST_MAIN(name)      \
                int main()                   \
                {                            \
                    size_t tests_passed = 0; \
                    size_t tests_failed = 0; \
                    size_t total_tests = 0;  \
                    char testName[] = #name

            /**
             * @def OCF_TEST_EXIT
             * @brief Finish the C test main function, optionally print summary, and return failures.
             * @param PS print summary flag.
             */
            #define OCF_TEST_EXIT(PS)         \
                    if (PS) OCF_TEST_SUMMARY; \
                    return (int)tests_failed; \
                }

            /**
             * @def OCF_TEST_ASSERT
             * @brief Evaluate a condition and record a failure with diagnostics if false.
             * @param cond condition to assert.
             */
            #define OCF_TEST_ASSERT(cond)                    \
                do {                                         \
                    if (cond) { tests_passed++; }            \
                    else                                     \
                    {                                        \
                        tests_failed++;                      \
                        printf("FAIL:\n");                   \
                        printf("\tNUMBER: %d", total_tests); \
                        printf("\tLINE: %d", __LINE__);      \
                        printf("\tFILE: %s", __FILE__);      \
                    }                                        \
                    total_tests++;                           \
                } while(false)

            /**
             * @def CTEST_COND
             * @brief Evaluate a boolean condition and update pass/fail counters.
             * @param cond condition to evaluate.
             */
            #define OCF_TEST_COND(cond)       \
                do {                          \
                    if (cond) tests_passed++; \
                    else tests_failed++;      \
                    total_tests++;            \
                } while(false)

            /**
             * @def CTEST_MSG
             * @brief Evaluate a condition and print a message on failure.
             * @param cond condition to assert.
             * @param msg failure message.
             */
            #define OCF_TEST_MSG(cond, msg)                  \
                do{                                          \
                    if (cond) { tests_passed++; }            \
                    else                                     \
                    {                                        \
                        tests_failed++;                      \
                        printf("FAIL: %s\n", msg);           \
                        printf("\tNUMBER: %d", total_tests); \
                        printf("\tLINE: %d", __LINE__);      \
                        printf("\tFILE: %s", __FILE__);      \
                    }                                        \
                    total_tests++;                           \
                } while(false)

            /**
             * @def OCF_TEST_RANGE
             * @brief Assert that a value lies within an inclusive range.
             * @param value tested value.
             * @param high upper bound.
             * @param low lower bound.
             */
            #define OCF_TEST_RANGE(value, high, low)         \
                do {                                         \
                    if (value <= high && value >= low)       \
                    {                                        \
                        tests_passed++;                      \
                    }                                        \
                    else                                     \
                    {                                        \
                        tests_failed++;                      \
                        printf("FAIL:\n");                   \
                        printf("\tNUMBER: %d", total_tests); \
                        printf("\tLINE: %d", __LINE__);      \
                        printf("\tFILE: %s", __FILE__);      \
                    }                                        \
                    total_tests++;                           \
                } while(false)


            /**
             * @def OCF_TEST_EQU
             * @brief Assert that two values are equal and record a failure if not.
             * @param real actual value.
             * @param expected expected value.
             */
            #define OCF_TEST_EQU(real, expected)              \
                do {                                          \
                    if (real == expected) { tests_passed++; } \
                    else                                      \
                    {                                         \
                        tests_failed++;                       \
                        printf("FAIL:\n");                    \
                        printf("\tNUMBER: %d", total_tests);  \
                        printf("\tLINE: %d", __LINE__);       \
                        printf("\tFILE: %s", __FILE__);       \
                    }                                         \
                    total_tests++;                            \
                } while(false)

            /**
             * @def OCF_TEST_EQU_MSG
             * @brief Assert equality and include a failure message.
             * @param real actual value.
             * @param expected expected value.
             * @param msg failure message.
             */
            #define OCF_TEST_EQU_MSG(real, expected, msg)     \
                do {                                          \
                    if (real == expected) { tests_passed++; } \
                    else                                      \
                    {                                         \
                        tests_failed++;                       \
                        printf("FAIL: %s\n", msg);            \
                        printf("\tNUMBER: %d", total_tests);  \
                        printf("\tLINE: %d", __LINE__);       \
                        printf("\tFILE: %s", __FILE__);       \
                    }                                         \
                    total_tests++;                            \
                } while(false)
            
        #endif // __cplusplus
    #else
        #if defined(__cplusplus)

            #include <string>
            #include <iostream>
            #include <queue>
            #include <chrono>

            /**
             * @def TEST_SUMMARY
             * @brief Print a C++ test summary using std::cout.
             */
            #define TEST_SUMMARY                                    \
                std::cout                                           \
                << "\n-------------------------------"              \
                << "\n<<<<<<<<< test summary >>>>>>>>"              \
                << "\n-------------------------------"              \
                << "\nTEST NAME: " << testName                      \
                << "\npassed tests: " << tests_passed               \
                << "\nfailed tests: " << tests_failed               \
                << "\ntotal tests: " << total_tests;                \
                if (total_tests > 0)                                \
                {                                                   \
                    std::cout                                       \
                    << "\npassed tests ratio: "                     \
                    << (double)(100 * (tests_passed / total_tests)) \
                    << "\nfailed tests ratio: "                     \
                    << (double)(100 * (tests_failed / total_tests));\
                }                                                   \
                else                                                \
                {                                                   \
                    std::cout                                       \
                    << "\npassed tests ratio: 0.0"                  \
                    << "\nfailed tests ratio: 0.0";                 \
                }                                                   \
                std::cout << "\n-------------------------------\n"

            /**
             * @def TEST_INIT
             * @brief Initialize C++ test counters, flags, and test name.
             * @param name test suite name.
             */
            #define TEST_INIT(name)       \
                bool warningFlag = false; \
                bool errorFlag = false;   \
                size_t tests_passed = 0;  \
                size_t tests_failed = 0;  \
                size_t total_tests = 0;   \
                std::string testName = #name

            /**
             * @def TEST_MAIN
             * @brief Start a C++ test program main function and initialize test state.
             * @param name test suite name.
             */
            #define TEST_MAIN(name) \
                int main() {        \
                    TEST_INIT(name) \

            /**
             * @def TEST_EXIT
             * @brief Finish the C++ test main function, optionally print summary, and return status.
             * @param PS print summary flag.
             */
            #define TEST_EXIT(PS)                              \
                    if(PS) TEST_SUMMARY;            \
                    return (int)(tests_failed || warningFlag); \
                }
            
            /**
             * @def TEST_ASSERT
             * @brief Evaluate a condition in C++ tests and record failure diagnostics.
             * @param cond condition to assert.
             */
            #define TEST_ASSERT(cond)                  \
                do {                                   \
                    if (cond) { tests_passed++; }      \
                    else                               \
                    {                                  \
                        tests_failed++;                \
                        std::cout                      \
                        << "FAIL:\n"                   \
                        << "\tNUMBER: " << total_tests \
                        << "\tLINE: " << __LINE__      \
                        << "\tFILE: " << __FILE__;     \
                    }                                  \
                    total_tests++;                     \
                } while(false)

            /**
             * @def TEST_COND
             * @brief Evaluate a boolean condition and update C++ test counters.
             * @param cond condition to evaluate.
             */
            #define TEST_COND(cond)           \
                do {                          \
                    if (cond) tests_passed++; \
                    else tests_failed++;      \
                    total_tests++;            \
                } while(false)

            /**
             * @def TEST_RANGE
             * @brief Assert a value lies within an inclusive range in C++ tests.
             * @param value tested value.
             * @param high upper bound.
             * @param low lower bound.
             */
            #define TEST_RANGE(value, high, low)       \
                do {                                   \
                    if (value <= high && value >= low) \
                    {                                  \
                        tests_passed++;                \
                    }                                  \
                    else                               \
                    {                                  \
                        tests_failed++;                \
                        std::cout                      \
                        << "FAIL:\n"                   \
                        << "\tNUMBER: " << total_tests \
                        << "\tLINE: " << __LINE__      \
                        << "\tFILE: " << __FILE__;     \
                    }                                  \
                    total_tests++;                     \
                } while(false)

            /**
             * @def TEST_MSG
             * @brief Evaluate a condition and print a failure message in C++ tests.
             * @param cond condition to assert.
             * @param msg failure message.
             */
            #define TEST_MSG(cond, msg)                \
                do{                                    \
                    if (cond) { tests_passed++; }      \
                    else                               \
                    {                                  \
                        tests_failed++;                \
                        std::cout                      \
                        << "FAIL: " << msg             \
                        << "\tNUMBER: " << total_tests \
                        << "\tLINE: " << __LINE__      \
                        << "\tFILE: " << __FILE__;     \
                    }                                  \
                    total_tests++;                     \
                } while(false)

            /**
             * @def TEST_EQU
             * @brief Assert equality in C++ tests and record diagnostics on failure.
             * @param real actual value.
             * @param expected expected value.
             */
            #define TEST_EQU(real, expected)                  \
                do {                                          \
                    if (real == expected) { tests_passed++; } \
                    else                                      \
                    {                                         \
                        tests_failed++;                       \
                        std::cout                             \
                        << "FAIL:\n"                          \
                        << "\tNUMBER: " << total_tests        \
                        << "\tLINE: " << __LINE__             \
                        << "\tFILE: " << __FILE__;            \
                    }                                         \
                    total_tests++;                            \
                } while(false)

            /**
             * @def TEST_EQU_MSG
             * @brief Assert equality with a failure message in C++ tests.
             * @param real actual value.
             * @param expected expected value.
             * @param msg failure message.
             */
            #define TEST_EQU_MSG(real, expected, msg)         \
                do {                                          \
                    if (real == expected) { tests_passed++; } \
                    else                                      \
                    {                                         \
                        tests_failed++;                       \
                        std::cout                             \
                        << "FAIL: " << msg                    \
                        << "\tNUMBER: " << total_tests        \
                        << "\tLINE: " << __LINE__             \
                        << "\tFILE: " << __FILE__;            \
                    }                                         \
                    total_tests++;                            \
                } while(false)


            /**
             * @def BENCHMARK_MAIN
             * @brief Start a benchmark main function with a lightweight benchmark timer.
             */
            #define BENCHMARK_MAIN \
                int main() {       \
                    auto BMS_start = std::chrono::high_resolution_clock::now();
            
            /**
             * @def BENCHMARK_EXIT
             * @brief Finish benchmark main and optionally print a benchmark summary.
             * @param PS print summary flag.
             */
            #define BENCHMARK_EXIT(PS)                                             \
                    if(PS)                                                         \
                    {                                                              \
                        auto BMS_end = std::chrono::high_resolution_clock::now();  \
                        auto BMS_elapsed =                                         \
                            std::chrono::duration_cast<std::chrono::microseconds>( \
                                BMS_end - BMS_start                                \
                            ).count();                                             \
                        std::cout << "\nBenchmark elapsed: "                       \
                                << BMS_elapsed                                   \
                                << " microseconds\n";                            \
                    }                                                              \
                    return 0;                                                      \
                }
        #else
            #include <stdio.h>

            /**
             * @def TEST_INIT
             * @brief Initialize C test counters and set the test suite name.
             * @param name test suite name.
             */
            #define TEST_INIT(name)      \
                size_t tests_passed = 0; \
                size_t tests_failed = 0; \
                size_t total_tests = 0;  \
                char testName[] = #name

            /**
             * @def TEST_SUMMARY
             * @brief Print a formatted C test summary to stdout.
             */
            #define TEST_SUMMARY                               \
                printf("\n-------------------------------");   \
                printf("\n<<<<<<<<< test summary >>>>>>>>");   \
                printf("\n-------------------------------");   \
                printf("\nTEST NAME: %s", testName);           \
                printf("\npassed tests: %i", tests_passed);    \
                printf("\nfailed tests: %i", tests_failed);    \
                printf("\ntotal tests: %i", total_tests);      \
                if (total_tests > 0)                           \
                {                                              \
                    printf(                                    \
                        "\npassed tests ratio: %f",            \
                        (double)                               \
                        (100 * (tests_passed / total_tests))); \
                    printf(                                    \
                        "\nfailed tests ratio: %f",            \
                        (double)                               \
                        (100 * (tests_failed / total_tests))); \
                }                                              \
                else                                           \
                {                                              \
                    printf("\npassed tests ratio: 0.0");       \
                    printf("\nfailed tests ratio: 0.0");       \
                }                                              \
                printf("\n-------------------------------\n")

            /**
             * @def TEST_MAIN
             * @brief Start a C test program main function and initialize counters.
             * @param name test suite name.
             */
            #define TEST_MAIN(name)          \
                int main()                   \
                {                            \
                    size_t tests_passed = 0; \
                    size_t tests_failed = 0; \
                    size_t total_tests = 0;  \
                    char testName[] = #name

            /**
             * @def TEST_EXIT
             * @brief Finish the C test main function, optionally print summary, and return failures.
             * @param PS print summary flag.
             */
            #define TEST_EXIT(PS)             \
                    if (PS) TEST_SUMMARY;     \
                    return (int)tests_failed; \
                }

            /**
             * @def TEST_ASSERT
             * @brief Evaluate a condition and record a failure with diagnostics if false.
             * @param cond condition to assert.
             */
            #define TEST_ASSERT(cond)                        \
                do {                                         \
                    if (cond) { tests_passed++; }            \
                    else                                     \
                    {                                        \
                        tests_failed++;                      \
                        printf("FAIL:\n");                   \
                        printf("\tNUMBER: %d", total_tests); \
                        printf("\tLINE: %d", __LINE__);      \
                        printf("\tFILE: %s", __FILE__);      \
                    }                                        \
                    total_tests++;                           \
                } while(false)

            /**
             * @def TEST_COND
             * @brief Evaluate a boolean condition and update pass/fail counters.
             * @param cond condition to evaluate.
             */
            #define TEST_COND(cond)           \
                do {                          \
                    if (cond) tests_passed++; \
                    else tests_failed++;      \
                    total_tests++;            \
                } while(false)

            /**
             * @def CTEST_MSG
             * @brief Evaluate a condition and print a message on failure.
             * @param cond condition to assert.
             * @param msg failure message.
             */
            #define TEST_MSG(cond, msg)                      \
                do{                                          \
                    if (cond) { tests_passed++; }            \
                    else                                     \
                    {                                        \
                        tests_failed++;                      \
                        printf("FAIL: %s\n", msg);           \
                        printf("\tNUMBER: %d", total_tests); \
                        printf("\tLINE: %d", __LINE__);      \
                        printf("\tFILE: %s", __FILE__);      \
                    }                                        \
                    total_tests++;                           \
                } while(false)

            /**
             * @def CTEST_RANGE
             * @brief Assert that a value lies within an inclusive range.
             * @param value tested value.
             * @param high upper bound.
             * @param low lower bound.
             */
            #define TEST_RANGE(value, high, low)             \
                do {                                         \
                    if (value <= high && value >= low)       \
                    {                                        \
                        tests_passed++;                      \
                    }                                        \
                    else                                     \
                    {                                        \
                        tests_failed++;                      \
                        printf("FAIL:\n");                   \
                        printf("\tNUMBER: %d", total_tests); \
                        printf("\tLINE: %d", __LINE__);      \
                        printf("\tFILE: %s", __FILE__);      \
                    }                                        \
                    total_tests++;                           \
                } while(false)


            /**
             * @def TEST_EQU
             * @brief Assert that two values are equal and record a failure if not.
             * @param real actual value.
             * @param expected expected value.
             */
            #define TEST_EQU(real, expected)                  \
                do {                                          \
                    if (real == expected) { tests_passed++; } \
                    else                                      \
                    {                                         \
                        tests_failed++;                       \
                        printf("FAIL:\n");                    \
                        printf("\tNUMBER: %d", total_tests);  \
                        printf("\tLINE: %d", __LINE__);       \
                        printf("\tFILE: %s", __FILE__);       \
                    }                                         \
                    total_tests++;                            \
                } while(false)

            /**
             * @def TEST_EQU_MSG
             * @brief Assert equality and include a failure message.
             * @param real actual value.
             * @param expected expected value.
             * @param msg failure message.
             */
            #define TEST_EQU_MSG(real, expected, msg)         \
                do {                                          \
                    if (real == expected) { tests_passed++; } \
                    else                                      \
                    {                                         \
                        tests_failed++;                       \
                        printf("FAIL: %s\n", msg);            \
                        printf("\tNUMBER: %d", total_tests);  \
                        printf("\tLINE: %d", __LINE__);       \
                        printf("\tFILE: %s", __FILE__);       \
                    }                                         \
                    total_tests++;                            \
                } while(false)
            
        #endif // __cplusplus
    #endif
#endif // OPENCF___CFROST___TEST_H