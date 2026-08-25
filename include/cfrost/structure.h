#ifndef OPENCF___CFROST___STRUCTURE_H
#define OPENCF___CFROST___STRUCTURE_H

/**
 * @file include/cfrost/structure.h
 * @brief Lightweight structural helper macros for C and C++.
 *
 * This header provides shorthand macros for main function entrypoints,
 * loop iteration patterns, conditional jumps, and memory helpers for
 * both C and C++. The macros preserve the original logic and do
 * not alter the underlying behavior.
 */

#if defined(OPENCF_FOR_GNU)

/**
 * @def ocf_newl
 * @brief Newline character constant.
 */
#define ocf_newl '\n'

/**
 * @def ocf_tab
 * @brief Tab character constant.
 */
#define ocf_tab '\t'

/**
 * @def ocf_main_start_and_exit
 * @brief Define a minimal main function that immediately returns 0.
 */
#define ocf_main_start_and_exit \
    int main() { return 0; }

/**
 * @def ocf_main_command
 * @brief Define a main function with argc/argv parameters.
 */
#define ocf_main_command int main(int argc, char *argv[])

/**
 * @def ocf_main_empty
 * @brief Define a main function without parameters.
 */
#define ocf_main_empty int main()

#define ocf_main \
    int main

/**
 * @def ocf_exit
 * @brief Return a value from main and close the function body.
 * @param retval return value.
 */
#define ocf_exit(retval) return (int)retval;

/**
 * @def ocf_procedure
 * @brief defines function with void return type with out any parameter for the function.
 * @param name is the name of the function.
 */
#define ocf_procedure(name) void name()

/**
 * @def ocf_iter_less
 * @brief Loop macro for iterating from zero to a limit.
 * @param iterator loop variable name.
 * @param value exclusive upper bound.
 */
#define ocf_iter_less(iterator, value) \
    size_t iterator = 0;               \
    iterator < value;                  \
    iterator++

/**
 * @def ocf_iter_high
 * @brief Loop macro for iterating downward from a starting value.
 * @param iterator loop variable name.
 * @param value starting value.
 */
#define ocf_iter_high(iterator, value) \
    size_t iterator = value;           \
    iterator > 0;                      \
    iterator--

/**
 * @def ocf_iter_in_range
 * @brief Loop macro for iterating from a start to end using a custom step.
 * @param iterator loop variable name.
 * @param start initial value.
 * @param end exclusive upper bound.
 * @param step increment step.
 */
#define ocf_iter_in_range(iterator, start, end, step) \
    size_t iterator = start;                          \
    iterator < end;                                   \
    iterator += step

/**
 * @def in_range
 * @brief Compare a value against a min and max using inclusive or exclusive bounds.
 * @param value value to test.
 * @param max upper bound.
 * @param min lower bound.
 * @param symbol '=' for inclusive range, otherwise exclusive.
 */
#define in_range(value, max, min, symbol) \
    symbol == '=' ? (value) <= (max) && (value) >= (min) : (value)<(max) && (value)>(min)

/**
 * @def jump
 * @brief Jump to a label using goto.
 * @param label destination label.
 */
#define ocf_jump(label) goto label

/**
 * @def jump_if
 * @brief Conditionally jump to a label.
 * @param condition condition to evaluate.
 * @param label destination label.
 */
#define ocf_jump_if(condition, label) \
    if (condition)                    \
    goto label

/**
 * @def ocf_jump_elif
 * @brief Else-if branch used after jump_if.
 * @param condition condition to evaluate.
 * @param label destination label.
 */
#define ocf_jump_elif(condition, label) else if (condition) goto label

/**
 * @def ocf_jump_else
 * @brief Else branch used after jump_if.
 * @param label destination label.
 */
#define ocf_jump_else(label) else goto label

/**
 * @def ocf_jump_if_else
 * @brief Jump to one of two labels based on a condition.
 * @param condition condition to evaluate.
 * @param ifLabel label for true branch.
 * @param elseLabel label for false branch.
 */
#define ocf_jump_if_else(condition, ifLabel, elseLabel) \
    if (condition)                                      \
        goto ifLabel;                                   \
    else                                                \
        goto elseLabel

#if !defined(__cplusplus)

#include <stdlib.h>

/**
 * @def ocf_alloc
 * @brief Allocate an array of type in C.
 * @param type element type.
 * @param size number of elements.
 */
#define ocf_alloc(type, size) (type *)malloc(size * sizeof(type))

/**
 * @def ocf_realloc
 * @brief Reallocate an existing C array to a new size.
 * @param type element type.
 * @param memory pointer to existing array.
 * @param new_size number of elements in the resized array.
 */
#define ocf_realloc(type, memory, new_size) (type *)realloc(memory, new_size * sizeof(type))

/**
 * @def ocf_free
 * @brief Free memory allocated with ocf_alloc in C.
 * @param data pointer to allocated memory.
 */
#define ocf_free(data) free(data)

/**
 * @def ocf_object
 * @brief Alias for beginning a struct definition in C.
 */
#define ocf_object typedef struct

/**
 * @def ocf_enum
 * @brief Alias for beginning an enum definition in C.
 */
#define ocf_enum typedef enum

/**
 * @def ocf_string
 * @brief Declare a fixed-size character array in C.
 * @param name array identifier.
 * @param sizeValue array length.
 */
#define ocf_string(name, sizeValue) char name[sizeValue]

#else

/**
 * @def ocf_alloc
 * @brief Allocate an array of objects in C++.
 * @param type element type.
 * @param size number of elements.
 */
#define ocf_alloc(type, size) new type[size]

/**
 * @def ocf_realloc
 * @brief Reallocate an array in C++ by allocating a new block and deleting the old one.
 * @param type element type.
 * @param memory pointer to the existing array.
 * @param new_size number of new elements.
 */
#define ocf_realloc(type, memory, new_size)                                      \
    do                                                                           \
    {                                                                            \
        type *temp = new type[new_size];                                         \
        for (size_t i = 0; i < (old_size < new_size ? old_size : new_size); ++i) \
            temp[i] = memory[i];                                                 \
        delete[] memory;                                                         \
        memory = temp;                                                           \
    } while (false)

/**
 * @def ocf_free
 * @brief Free an array allocated with new[] in C++.
 * @param data pointer to allocated array.
 */
#define ocf_free(data) delete[] data

/**
 * @def ocf_lambda
 * @brief Create a C++ lambda with an explicit return type.
 * @param return_type lambda return type.
 * @param parameters lambda parameter list.
 */
#define ocf_lambda(return_type, parameters) parameters->return_type

/**
 * @def ocf_lambda_v
 * @brief Create a C++ lambda with void return.
 * @param parameters lambda parameter list.
 */
#define ocf_lambda_v(parameters) parameters->void

#include <string>
#include <functional>
#include <vector>
#include <queue>
#include <unordered_map>
#include <initializer_list>

#define ocf_enable_procedure_if(condition, name) \
    std::enable_if_t<condition, void> name(void)

namespace ocf
{

    // template <typename T1, typename T2>
    // using enable_arithmetic = std::enable_if<std::is_arithmetic<T1>::value, T2>::type;

    template <bool T1, typename T2>
    using enable_if = std::enable_if_t<T1, T2>;

    /**
     * @typedef str
     * @brief Alias for std::string.
     */
    using str = std::string;

    /**
     * @typedef func
     * @brief Alias for std::function<T>.
     */
    template <typename T>
    using func = std::function<T>;

    /**
     * @typedef vec
     * @brief Alias for std::vector<T>.
     */
    template <typename T>
    using vec = std::vector<T>;

    /**
     * @typedef que
     * @brief Alias for std::queue<T>.
     */
    template <typename T>
    using que = std::queue<T>;

    /**
     * @typedef hash_map
     * @brief Alias for std::unordered_map<T, U>.
     */
    template <typename T, typename U>
    using hash_map = std::unordered_map<T, U>;

    /**
     * @typedef initList
     * @brief Alias for std::initializer_list<T>.
     */
    template <typename T>
    using initList = std::initializer_list<T>;

}

#endif // __cplusplus

#else

/**
 * @def newl
 * @brief Newline character constant.
 */
#define newl '\n'

/**
 * @def tab
 * @brief Tab character constant.
 */
#define tab '\t'

/**
 * @def main_start_and_exit
 * @brief Define a minimal main function that immediately returns 0.
 */
#define main_start_and_exit \
    int main() { return 0; }

/**
 * @def command_main
 * @brief Define a main function with argc/argv parameters.
 */
#define main_command int main(int argc, char *argv[])

/**
 * @def main_func
 * @brief Define a main function without parameters.
 */
#define main_empty int main()

/**
 * @def procedure
 * @brief defines function with void return type with out any parameter for the function.
 * @param name is the name of the function.
 */
#define procedure(name) void name(void)

/**
 * @def less_iter
 * @brief Loop macro for iterating from zero to a limit.
 * @param iterator loop variable name.
 * @param value exclusive upper bound.
 */
#define iter_less(iterator, value) \
    size_t iterator = 0;           \
    iterator < value;              \
    iterator++

/**
 * @def high_iter
 * @brief Loop macro for iterating downward from a starting value.
 * @param iterator loop variable name.
 * @param value starting value.
 */
#define iter_high(iterator, value) \
    size_t iterator = value;       \
    iterator > 0;                  \
    iterator--

/**
 * @def inRangeIter
 * @brief Loop macro for iterating from a start to end using a custom step.
 * @param iterator loop variable name.
 * @param start initial value.
 * @param end exclusive upper bound.
 * @param step increment step.
 */
#define iter_in_range(iterator, start, end, step) \
    size_t iterator = start;                      \
    iterator < end;                               \
    iterator += step

/**
 * @def in_range
 * @brief Compare a value against a min and max using inclusive or exclusive bounds.
 * @param value value to test.
 * @param max upper bound.
 * @param min lower bound.
 * @param symbol '=' for inclusive range, otherwise exclusive.
 */
#define in_range(value, max, min, symbol) \
    symbol == '=' ? (value) <= (max) && (value) >= (min) : (value)<(max) && (value)>(min)

/**
 * @def jump
 * @brief Jump to a label using goto.
 * @param label destination label.
 */
#define jump(label) goto label

/**
 * @def jump_if
 * @brief Conditionally jump to a label.
 * @param condition condition to evaluate.
 * @param label destination label.
 */
#define jump_if(condition, label) \
    if (condition)                \
    goto label

/**
 * @def jump_elif
 * @brief Else-if branch used after jump_if.
 * @param condition condition to evaluate.
 * @param label destination label.
 */
#define jump_elif(condition, label) else if (condition) goto label

/**
 * @def jump_else
 * @brief Else branch used after jump_if.
 * @param label destination label.
 */
#define jump_else(label) else goto label

/**
 * @def jump_if_else
 * @brief Jump to one of two labels based on a condition.
 * @param condition condition to evaluate.
 * @param ifLabel label for true branch.
 * @param elseLabel label for false branch.
 */
#define jump_if_else(condition, ifLabel, elseLabel) \
    if (condition)                                  \
        goto ifLabel;                               \
    else                                            \
        goto elseLabel

#if !defined(__cplusplus)

#include <stdlib.h>

/**
 * @def allocate
 * @brief Allocate an array of type in C.
 * @param type element type.
 * @param size number of elements.
 */
#define dynamic_allocate(type, size) (type *)malloc(size * sizeof(type))

/**
 * @def reallocate
 * @brief Reallocate an existing C array to a new size.
 * @param type element type.
 * @param memory pointer to existing array.
 * @param new_size number of elements in the resized array.
 */
#define dynamic_reallocate(type, memory, new_size) (type *)realloc(memory, new_size * sizeof(type))

/**
 * @def front_free
 * @brief Free memory allocated with front_alloc in C.
 * @param data pointer to allocated memory.
 */
#define dynamic_free(data) free(data)

/**
 * @def object
 * @brief Alias for beginning a struct definition in C.
 */
#define object typedef struct

/**
 * @def cenum
 * @brief Alias for beginning an enum definition in C.
 */
#define cenum typedef enum

/**
 * @def cstring
 * @brief Declare a fixed-size character array in C.
 * @param name array identifier.
 * @param sizeValue array length.
 */
#define cstring(name, sizeValue) char name[sizeValue]

#else

/**
 * @def allocate
 * @brief Allocate an array of objects in C++.
 * @param type element type.
 * @param size number of elements.
 */
#define dynamic_allocate(type, size) new type[size]

/**
 * @def reallocate
 * @brief Reallocate an array in C++ by allocating a new block and deleting the old one.
 * @param type element type.
 * @param memory pointer to the existing array.
 * @param new_size number of new elements.
 */
#define dynamic_reallocate(type, memory, old_size, new_size)                     \
    do                                                                           \
    {                                                                            \
        type *temp = new type[new_size];                                         \
        for (size_t i = 0; i < (old_size < new_size ? old_size : new_size); ++i) \
            temp[i] = memory[i];                                                 \
        delete[] memory;                                                         \
        memory = temp;                                                           \
    } while (false)

/**
 * @def free_micro
 * @brief Free an array allocated with new[] in C++.
 * @param data pointer to allocated array.
 */
#define dynamic_free(data) delete[] data

/**
 * @def lambda_f
 * @brief Create a C++ lambda with an explicit return type.
 * @param return_type lambda return type.
 * @param parameters lambda parameter list.
 */
#define lambda_f(return_type, parameters) parameters->return_type

/**
 * @def lambda_v
 * @brief Create a C++ lambda with void return.
 * @param parameters lambda parameter list.
 */
#define lambda_v(parameters) parameters->void

#include <string>
#include <functional>
#include <vector>
#include <queue>
#include <unordered_map>
#include <initializer_list>

#define enable_procedure_if(condition, name) \
    std::enable_if_t<condition, void> name(void)

namespace ocf
{

    // template <typename T1, typename T2>
    // using enable_arithmetic = std::enable_if<std::is_arithmetic<T1>::value, T2>::type;

    template <bool T1, typename T2>
    using enable_if = std::enable_if_t<T1, T2>;

    /**
     * @typedef str
     * @brief Alias for std::string.
     */
    using str = std::string;

    /**
     * @typedef func
     * @brief Alias for std::function<T>.
     */
    template <typename T>
    using func = std::function<T>;

    /**
     * @typedef vec
     * @brief Alias for std::vector<T>.
     */
    template <typename T>
    using vec = std::vector<T>;

    /**
     * @typedef que
     * @brief Alias for std::queue<T>.
     */
    template <typename T>
    using que = std::queue<T>;

    /**
     * @typedef hash_map
     * @brief Alias for std::unordered_map<T, U>.
     */
    template <typename T, typename U>
    using hash_map = std::unordered_map<T, U>;

    /**
     * @typedef initList
     * @brief Alias for std::initializer_list<T>.
     */
    template <typename T>
    using initList = std::initializer_list<T>;

}

#endif // __cplusplus

#endif

#endif // OPENCF___CFROST___MICROS_STRUCTURE_H