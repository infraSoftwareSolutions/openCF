/** @file dynamic.h
 *  @brief cdynamic struct and related functions for dynamic typing.
 * @details This module defines the cdynamic struct, which can hold a value of various types
 * along with a type tag.  It provides initialization functions for different types, as well as
 * casting and conversion utilities.  Users must call cdynamic_init() before using a cdynamic
 * instance to ensure it is in a valid state.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdexcpt.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

#ifndef OPENCF___CFROST___CGEN___DDT_DYNAMIC_H
#define OPENCF___CFROST___CGEN___DDT_DYNAMIC_H

    #if defined(OPENCF_FOR_GNU)
            const uint8_t 
            dyn_enum_null = 0,
            dyn_enum_bool = 1,
            dyn_enum_char = 2,
            dyn_enum_short = 3,
            dyn_enum_int = 4,
            dyn_enum_float = 5,
            dyn_enum_long = 6,
            dyn_enum_double = 7;

        typedef struct ocf_dynamic
        {
            uint8_t id;
            double value;
        }
        ocf_dynamic;

        static inline ocf_dynamic ocf_dynamic_new()
        {
            ocf_dynamic obj;
            obj.id = dyn_enum_null;
            obj.value = 0.0;
            return obj;
        }

        /**
         * @brief Initialize a dynamic object to null state.
         * Sets the type tag to `dyn_enum_null` and zeroes the value.  This function must
         * be called before using the object.
         * @param self Pointer to ocf_dynamic instance.
         */
        static inline void ocf_dynamic_self(ocf_dynamic *self)
        {
            self->id = dyn_enum_null;
            self->value = 0.0;
        }

        /**
         * @brief Initialize ocf_dynamic from a boolean.
         * Stores the value as 1.0 or 0.0 and sets the type tag accordingly.
         * @param value Boolean value to assign.
         */
        static inline ocf_dynamic ocf_dynamic_bool(bool value)
        {
            ocf_dynamic obj;
            obj.id = dyn_enum_bool;
            obj.value = (value ? 1.0 : 0.0);
            return obj;
        }

        /**
         * @brief Initialize ocf_dynamic from a char value.
         * The character is converted to double and the type tag is set to CHAR.
         * @param value Character to store.
         */
        static inline ocf_dynamic ocf_dynamic_char(char value)
        {
            ocf_dynamic obj;
            obj.id = dyn_enum_char;
            obj.value = (double)value;
            return obj;
        }

        /**
         * @brief Initialize ocf_dynamic from a short integer.
         * Converts to double internally.
         * @param value Short integer to store.
         */
        static inline ocf_dynamic ocf_dynamic_short(short value)
        {
            ocf_dynamic obj;
            obj.id = dyn_enum_short;
            obj.value = (double)value;
            return obj;
        }

        /**
         * @brief Initialize ocf_dynamic from an int.
         * Stored as double.
         * @param value Integer value.
         */
        static inline ocf_dynamic ocf_dynamic_int(int value)
        {
            ocf_dynamic obj;
            obj.id = dyn_enum_int;
            obj.value = (double)value;
            return obj;
        }

        /**
         * @brief Initialize ocf_dynamic from a float.
         * The float is promoted to double.
         * @param value Float value to store.
         */
        static inline ocf_dynamic ocf_dynamic_float(float value)
        {
            ocf_dynamic obj;
            obj.id = dyn_enum_float;
            obj.value = (double)value;
            return obj;
        }

        /**
         * @brief Initialize ocf_dynamic from a double.
         * @param value Double value to store.
         */
        static inline ocf_dynamic ocf_dynamic_double(double value)
        {
            ocf_dynamic obj;
            obj.id = dyn_enum_double;
            obj.value = value;
            return obj;
        }

        /**
         * @brief Copy initialize from another ocf_dynamic.
         * Performs a shallow copy of the tag and value.
         * @param other Source ocf_dynamic to copy.
         */
        static inline ocf_dynamic ocf_dynamic_copy(ocf_dynamic other)
        {
            ocf_dynamic obj;
            obj.id = other.id;
            obj.value = other.value;
            return obj;
        }

        /**
         * @brief Retrieve the textual name of the stored type.
         *
         * @param self Pointer to ocf_dynamic instance.
         * @return String literal representing the current type tag.
         */
        static inline const char* ocf_dynamic_type_name(ocf_dynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_null:
                return "NULL";
            case dyn_enum_bool:
                return "BOOL";
            case dyn_enum_char:
                return "CHAR";
            case dyn_enum_short:
                return "SHORT";
            case dyn_enum_int:
                return "INT";
            case dyn_enum_float:
                return "FLOAT";
            case dyn_enum_long:
                return "LONG";
            case dyn_enum_double:
                return "DOUBLE";
            default:
                return "UNKNOWN";
            }
        }

        static inline bool ocf_dynamic_get_bool(ocf_dynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                return self.value != 0.0;
            default:
                printf("run time error: Invalid dynamic type for cast_bool");
            }
            return false;
        }

        static inline char ocf_dynamic_get_char(ocf_dynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return (char)(self.value != 0.0 ? 1 : 0);
            case dyn_enum_char:
                return self.value;
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                if (self.value > (double)'~' || self.value < (double)'\0')
                {
                    printf("out of range error: the value is out of the range of ascii table.\n");
                    return '~';
                }
                return (char)self.value;
            default:
                printf("run time error: Invalid dynamic type for cast_char\n");
            }
            return '\0';
        }

        static inline short ocf_dynamic_get_short(ocf_dynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return (short)(self.value != 0.0 ? 1 : 0);
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                if (self.value > SHRT_MAX || self.value < SHRT_MIN)
                {
                    printf("out of range error: the value is out of range of the type short.\n");
                    return (short)0;
                }
                return (short)self.value;
            default:
                printf("run time error: Invalid dynamic type for cast_short");
            }
            return (short)0;
        }

        static inline int ocf_dynamic_get_int(ocf_dynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return (int)(self.value != 0.0 ? 1 : 0);
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                if (self.value > INT_MAX || self.value < INT_MIN)
                {
                    printf("out of range error: the value is out of range of the type int.\n");
                    return (int)0;
                }
                return (int)self.value;
            default:
                printf("run time error: Invalid dynamic type for cast_int");
            }
        }

        static inline float ocf_dynamic_get_float(ocf_dynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return (self.value != 0.0 ? 1.0f : 0.0f);
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                return (float)(self.value);
            default:
                printf("run time error: Invalid dynamic type for cast_float\n");
            }
            return 0.0f;
        }

        static inline double ocf_dynamic_get_double(ocf_dynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return self.value != 0.0 ? 1.0 : 0.0;
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                return self.value;
            default:
                printf("run time error: Invalid dynamic type for cast_double");
            }
        }

        static inline ocf_dynamic ocf_dynamic_cast2bool(ocf_dynamic self)
        {
            if (self.id == dyn_enum_bool)
            {
                return self;
            }
            return ocf_dynamic_bool(self.value != 0.0);
        }

        static inline ocf_dynamic ocf_dynamic_cast2char(ocf_dynamic self)
        {
            if (self.id == dyn_enum_char)
            {
                return self;
            }
            if (self.value > '~' || self.value < '\0')
            {
                printf("out of range error: the value is out of range of the type char.\n");
                return ocf_dynamic_new();
            }
            return ocf_dynamic_char(self.value);
        }

        static inline ocf_dynamic ocf_dynamic_cast2short(ocf_dynamic self)
        {
            if (self.id == dyn_enum_short)
            {
                return self;
            }
            if (self.value > SHRT_MAX || self.value < SHRT_MIN)
            {
                printf("out of range error: the value is out of range of the type short.\n");
                return ocf_dynamic_new();
            }
            return ocf_dynamic_short(self.value);
        }

        static inline ocf_dynamic ocf_dynamic_cast2int(ocf_dynamic self)
        {
            if (self.id == dyn_enum_int)
            {
                return self;
            }
            if (self.value > INT_MAX || self.value < INT_MIN)
            {
                printf("out of range error: the value is out of range of the type int.\n");
                return ocf_dynamic_new();
            }
            return ocf_dynamic_int(self.value);
        }

        static inline ocf_dynamic ocf_dynamic_cast2float(ocf_dynamic self)
        {
            if (self.id == dyn_enum_float)
            {
                return self;
            }
            return ocf_dynamic_float(self.value);
        }

        static inline ocf_dynamic ocf_dynamic_cast2double(ocf_dynamic self)
        {
            if (self.id == dyn_enum_double)
            {
                return self;
            }
            return ocf_dynamic_double(self.value);
        }

        /**
         * @brief Convert the object to a specified target type.
         *
         * Performs the appropriate cast based on @p target_type and returns a new
         * ocf_dynamic with that type and value.  Throws if the target type is
         * unsupported.
         *
         * @param self        Source object to convert.
         * @param target_type Desired dynamic_index value.
         * @return New ocf_dynamic holding the converted value.
         */
        static inline ocf_dynamic ocf_dynamic_convert_to(ocf_dynamic self, uint8_t target_type)
        {
            switch (target_type)
            {
            case dyn_enum_null:
                return ocf_dynamic_new();
            case dyn_enum_bool:
                return ocf_dynamic_cast2bool(self);
            case dyn_enum_char:
                return ocf_dynamic_cast2char(self);
            case dyn_enum_short:
                return ocf_dynamic_cast2short(self);
            case dyn_enum_int:
                return ocf_dynamic_cast2int(self);
            case dyn_enum_float:
                return ocf_dynamic_cast2float(self);
            case dyn_enum_double:
                return ocf_dynamic_cast2double(self);
            default:
                printf("run time error: Invalid target type for convert_to");
                return ocf_dynamic_new();
            }
        }

        /**
         * @brief Retrieve the stored numeric value.
         *
         * @param self Pointer to ocf_dynamic instance.
         * @return Underlying double value.
         */
        static inline double ocf_dynamic_get_value(ocf_dynamic self) { return self.value; }

        /**
         * @brief Get the type tag of the dynamic object.
         *
         * @param self Pointer to ocf_dynamic instance.
         * @return The current uint8_t id.
         */
        static inline uint8_t ocf_dynamic_get_id(ocf_dynamic self) { return self.id; }

        static inline bool ocf_dynamic_is_null(ocf_dynamic self) { return self.id == dyn_enum_null; }

        static inline bool ocf_dynamic_is_bool(ocf_dynamic self) { return self.id == dyn_enum_bool; }

        static inline bool ocf_dynamic_is_char(ocf_dynamic self) { return self.id == dyn_enum_char; }

        static inline bool ocf_dynamic_is_short(ocf_dynamic self) { return self.id == dyn_enum_short; }

        static inline bool ocf_dynamic_is_int(ocf_dynamic self) { return self.id == dyn_enum_int; }

        static inline bool ocf_dynamic_is_long(ocf_dynamic self) { return self.id == dyn_enum_long; }

        static inline bool ocf_dynamic_is_float(ocf_dynamic self) { return self.id == dyn_enum_float; }

        static inline bool ocf_dynamic_is_double(ocf_dynamic self) { return self.id == dyn_enum_double; }
    #else
        const uint8_t 
            dyn_enum_null = 0,
            dyn_enum_bool = 1,
            dyn_enum_char = 2,
            dyn_enum_short = 3,
            dyn_enum_int = 4,
            dyn_enum_float = 5,
            dyn_enum_long = 6,
            dyn_enum_double = 7;

        typedef struct cdynamic
        {
            uint8_t id;
            double value;
        }
        cdynamic;

        static inline cdynamic cdynamic_new()
        {
            cdynamic obj;
            obj.id = dyn_enum_null;
            obj.value = 0.0;
            return obj;
        }

        /**
         * @brief Initialize a dynamic object to null state.
         * Sets the type tag to `dyn_enum_null` and zeroes the value.  This function must
         * be called before using the object.
         * @param self Pointer to cdynamic instance.
         */
        static inline void cdynamic_self(cdynamic *self)
        {
            self->id = dyn_enum_null;
            self->value = 0.0;
        }

        /**
         * @brief Initialize cdynamic from a boolean.
         * Stores the value as 1.0 or 0.0 and sets the type tag accordingly.
         * @param value Boolean value to assign.
         */
        static inline cdynamic cdynamic_bool(bool value)
        {
            cdynamic obj;
            obj.id = dyn_enum_bool;
            obj.value = (value ? 1.0 : 0.0);
            return obj;
        }

        /**
         * @brief Initialize cdynamic from a char value.
         * The character is converted to double and the type tag is set to CHAR.
         * @param value Character to store.
         */
        static inline cdynamic cdynamic_char(char value)
        {
            cdynamic obj;
            obj.id = dyn_enum_char;
            obj.value = (double)value;
            return obj;
        }

        /**
         * @brief Initialize cdynamic from a short integer.
         * Converts to double internally.
         * @param value Short integer to store.
         */
        static inline cdynamic cdynamic_short(short value)
        {
            cdynamic obj;
            obj.id = dyn_enum_short;
            obj.value = (double)value;
            return obj;
        }

        /**
         * @brief Initialize cdynamic from an int.
         * Stored as double.
         * @param value Integer value.
         */
        static inline cdynamic cdynamic_int(int value)
        {
            cdynamic obj;
            obj.id = dyn_enum_int;
            obj.value = (double)value;
            return obj;
        }

        /**
         * @brief Initialize cdynamic from a float.
         * The float is promoted to double.
         * @param value Float value to store.
         */
        static inline cdynamic cdynamic_float(float value)
        {
            cdynamic obj;
            obj.id = dyn_enum_float;
            obj.value = (double)value;
            return obj;
        }

        /**
         * @brief Initialize cdynamic from a double.
         * @param value Double value to store.
         */
        static inline cdynamic cdynamic_double(double value)
        {
            cdynamic obj;
            obj.id = dyn_enum_double;
            obj.value = value;
            return obj;
        }

        /**
         * @brief Copy initialize from another cdynamic.
         * Performs a shallow copy of the tag and value.
         * @param other Source cdynamic to copy.
         */
        static inline cdynamic cdynamic_copy(cdynamic other)
        {
            cdynamic obj;
            obj.id = other.id;
            obj.value = other.value;
            return obj;
        }

        /**
         * @brief Retrieve the textual name of the stored type.
         *
         * @param self Pointer to cdynamic instance.
         * @return String literal representing the current type tag.
         */
        static inline const char* cdynamic_type_name(cdynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_null:
                return "NULL";
            case dyn_enum_bool:
                return "BOOL";
            case dyn_enum_char:
                return "CHAR";
            case dyn_enum_short:
                return "SHORT";
            case dyn_enum_int:
                return "INT";
            case dyn_enum_float:
                return "FLOAT";
            case dyn_enum_long:
                return "LONG";
            case dyn_enum_double:
                return "DOUBLE";
            default:
                return "UNKNOWN";
            }
        }

        static inline bool cdynamic_get_bool(cdynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                return self.value != 0.0;
            default:
                printf("run time error: Invalid dynamic type for cast_bool");
            }
            return false;
        }

        static inline char cdynamic_get_char(cdynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return (char)(self.value != 0.0 ? 1 : 0);
            case dyn_enum_char:
                return self.value;
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                if (self.value > (double)'~' || self.value < (double)'\0')
                {
                    printf("out of range error: the value is out of the range of ascii table.\n");
                    return '~';
                }
                return (char)self.value;
            default:
                printf("run time error: Invalid dynamic type for cast_char\n");
            }
            return '\0';
        }

        static inline short cdynamic_get_short(cdynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return (short)(self.value != 0.0 ? 1 : 0);
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                if (self.value > SHRT_MAX || self.value < SHRT_MIN)
                {
                    printf("out of range error: the value is out of range of the type short.\n");
                    return (short)0;
                }
                return (short)self.value;
            default:
                printf("run time error: Invalid dynamic type for cast_short");
            }
            return (short)0;
        }

        static inline int cdynamic_get_int(cdynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return (int)(self.value != 0.0 ? 1 : 0);
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                if (self.value > INT_MAX || self.value < INT_MIN)
                {
                    printf("out of range error: the value is out of range of the type int.\n");
                    return (int)0;
                }
                return (int)self.value;
            default:
                printf("run time error: Invalid dynamic type for cast_int");
            }
        }

        static inline float cdynamic_get_float(cdynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return (self.value != 0.0 ? 1.0f : 0.0f);
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                return (float)(self.value);
            default:
                printf("run time error: Invalid dynamic type for cast_float\n");
            }
            return 0.0f;
        }

        static inline double cdynamic_get_double(cdynamic self)
        {
            switch (self.id)
            {
            case dyn_enum_bool:
                return self.value != 0.0 ? 1.0 : 0.0;
            case dyn_enum_char:
            case dyn_enum_short:
            case dyn_enum_int:
            case dyn_enum_float:
            case dyn_enum_long:
            case dyn_enum_double:
                return self.value;
            default:
                printf("run time error: Invalid dynamic type for cast_double");
            }
        }

        static inline cdynamic cdynamic_cast2bool(cdynamic self)
        {
            if (self.id == dyn_enum_bool)
            {
                return self;
            }
            return cdynamic_bool(self.value != 0.0);
        }

        static inline cdynamic cdynamic_cast2char(cdynamic self)
        {
            if (self.id == dyn_enum_char)
            {
                return self;
            }
            if (self.value > '~' || self.value < '\0')
            {
                printf("out of range error: the value is out of range of the type char.\n");
                return cdynamic_new();
            }
            return cdynamic_char(self.value);
        }

        static inline cdynamic cdynamic_cast2short(cdynamic self)
        {
            if (self.id == dyn_enum_short)
            {
                return self;
            }
            if (self.value > SHRT_MAX || self.value < SHRT_MIN)
            {
                printf("out of range error: the value is out of range of the type short.\n");
                return cdynamic_new();
            }
            return cdynamic_short(self.value);
        }

        static inline cdynamic cdynamic_cast2int(cdynamic self)
        {
            if (self.id == dyn_enum_int)
            {
                return self;
            }
            if (self.value > INT_MAX || self.value < INT_MIN)
            {
                printf("out of range error: the value is out of range of the type int.\n");
                return cdynamic_new();
            }
            return cdynamic_int(self.value);
        }

        static inline cdynamic cdynamic_cast2float(cdynamic self)
        {
            if (self.id == dyn_enum_float)
            {
                return self;
            }
            return cdynamic_float(self.value);
        }

        static inline cdynamic cdynamic_cast2double(cdynamic self)
        {
            if (self.id == dyn_enum_double)
            {
                return self;
            }
            return cdynamic_double(self.value);
        }

        /**
         * @brief Convert the object to a specified target type.
         *
         * Performs the appropriate cast based on @p target_type and returns a new
         * cdynamic with that type and value.  Throws if the target type is
         * unsupported.
         *
         * @param self        Source object to convert.
         * @param target_type Desired dynamic_index value.
         * @return New cdynamic holding the converted value.
         */
        static inline cdynamic cdynamic_convert_to(cdynamic self, uint8_t target_type)
        {
            switch (target_type)
            {
            case dyn_enum_null:
                return cdynamic_new();
            case dyn_enum_bool:
                return cdynamic_cast2bool(self);
            case dyn_enum_char:
                return cdynamic_cast2char(self);
            case dyn_enum_short:
                return cdynamic_cast2short(self);
            case dyn_enum_int:
                return cdynamic_cast2int(self);
            case dyn_enum_float:
                return cdynamic_cast2float(self);
            case dyn_enum_double:
                return cdynamic_cast2double(self);
            default:
                printf("run time error: Invalid target type for convert_to");
                return cdynamic_new();
            }
        }

        /**
         * @brief Retrieve the stored numeric value.
         *
         * @param self Pointer to cdynamic instance.
         * @return Underlying double value.
         */
        static inline double cdynamic_get_value(cdynamic self) { return self.value; }

        /**
         * @brief Get the type tag of the dynamic object.
         *
         * @param self Pointer to cdynamic instance.
         * @return The current uint8_t id.
         */
        static inline uint8_t cdynamic_get_id(cdynamic self) { return self.id; }

        static inline bool cdynamic_is_null(cdynamic self) { return self.id == dyn_enum_null; }

        static inline bool cdynamic_is_bool(cdynamic self) { return self.id == dyn_enum_bool; }

        static inline bool cdynamic_is_char(cdynamic self) { return self.id == dyn_enum_char; }

        static inline bool cdynamic_is_short(cdynamic self) { return self.id == dyn_enum_short; }

        static inline bool cdynamic_is_int(cdynamic self) { return self.id == dyn_enum_int; }

        static inline bool cdynamic_is_long(cdynamic self) { return self.id == dyn_enum_long; }

        static inline bool cdynamic_is_float(cdynamic self) { return self.id == dyn_enum_float; }

        static inline bool cdynamic_is_double(cdynamic self) { return self.id == dyn_enum_double; }
    #endif
#endif // OPENCF___CFROST___CGEN___DDT_DYNAMIC_H