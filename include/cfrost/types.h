#pragma once
#ifndef OPENCF___CFROST___TYPES_H
#define OPENCF___CFROST___TYPES_H

    #if defined(__cplusplus)
        #include <string>
        #include <functional>
        #include <vector>
        #include <queue>
        #include <unordered_map>
        #include <initializer_list>
        #include <cstdint>
        #include <cstddef>
        #include <cstdbool>
        namespace ocf {
            using byte = std::int8_t;
            using ubyte = std::uint8_t;
            using i8 = std::int8_t;
            using u8 = std::uint8_t;
            using i16 = std::int16_t;
            using u16 = std::uint16_t;
            using i32 = std::int32_t;
            using u32 = std::uint32_t;
            using i64 = std::int64_t;
            using u64 = std::uint64_t;
            using f32 = float;
            using f64 = double;
            using b = bool;
            using c = char;

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
    #else
        #include <stdint.h>
        #include <stddef.h>
        #include <stdbool.h>
        typedef int8_t byte;
        typedef uint8_t ubyte;
        typedef int8_t i8;
        typedef uint8_t u8;
        typedef int16_t i16;
        typedef uint16_t u16;
        typedef int32_t i32;
        typedef uint32_t u32;
        typedef int64_t i64;
        typedef uint64_t u64;
        typedef float f32;
        typedef double f64;
        typedef bool b;
        typedef char c;
    #endif

#endif // OPENCF___CFROST___TYPES_H