/**
 * @file cfrost.h
 * @brief Micro Definitions and Utility Macros
 * @author ali lafi
 * @date May 25, 2026
 *
 * @details
 * This file provides comprehensive macro definitions for constant declarations, object definitions,
 * and testing utilities. It has two main modes controlled by COBJECT_DATA:
 *
 * COBJECT_DATA Mode: Constant declaration macros
 * - Macros for declaring typed constants (cbool, cchar, cint, cfloat, cdouble, etc.)
 * - Array definition macros (carray_i32, carray_f64)
 * - Section attribute for memory placement (DATA_SEC)
 * - Type inference macros in non-strict mode (cauto, cdynamic)
 * - Optional logic restriction macros when ALLOW_LOGIC_MODE is disabled
 *
 * Standard Mode: Testing utilities and string operations
 * - Test framework macros (INIT_TEST, MAIN_TEST, EXIT_TEST, TEST_0 through TEST_3)
 * - Assertion macro (ASSERT)
 * - Object/struct definition macro (cobject)
 * - Character constants (nl, ctab)
 * - String type alias (cstrptr)
 *
 * @functions (Standard Mode)
 * - length()           : Get string length
 * - equal()            : Compare two strings for equality
 * - concatenate()      : Concatenate two strings
 * - is_empty()         : Check if string is empty or NULL
 * - empty()            : Clear string content
 * - free()             : Free string memory
 * - exist()            : Check if character exists in string
 * - sub_exist()        : Check if substring exists in string
 * - count()            : Count occurrences of character in string
 */

#ifndef OPENCF___CFROST_H
#define OPENCF___CFROST_H

#if defined(cobject_data_micros) && !defined(ALLOW_LOGIC_MODE)
    #include "cfrost/object_data.h"
#elif defined(cobject_data_micros) && defined(ALLOW_LOGIC_MODE)
    #include "cfrost/object_data.h"
    #include "cfrost/structure.h"
    #include "cfrost/test.h"
    #include "cfrost/types.h"
    #if defined(__cplusplus)
        #include "cfrost/data_structure.hpp"
    #endif
#else
    #include "cfrost/structure.h"
    #include "cfrost/test.h"
    #include "cfrost/types.h"
    #if defined(__cplusplus)
        #include "cfrost/data_structure.hpp"
    #endif
#endif // cobject_data_micros

#endif // OPENCF___CFROST_H