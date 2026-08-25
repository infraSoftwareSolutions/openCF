#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef OPENCF___CFROST___CGEN___STRING_H
#define OPENCF___CFROST___CGEN___STRING_H

#if defined(OPENCF_FOR_GNU)

    static inline size_t ocf_length(const char * value) { return (value != NULL) ? strlen(value) : 0; }

    static inline bool ocf_equal(const char * value_1, const char * value_2)
    {
        if (value_1 == NULL || value_2 == NULL)
        return false;
        return strcmp(value_1, value_2) == 0 ? true : false;
    }

    static inline char* ocf_concatenate(char* value_1, const char * value_2)
    {
        if (value_1 == NULL || value_2 == NULL)
        return value_1;
        return strcat(value_1, value_2);
    }

    static inline bool ocf_is_empty(const char * value) { return (value == NULL || strlen(value) == 0) ? true : false; }

    /**
     * @brief Clear string content by reallocating to empty string
     * @param value The string to clear
     * @return Pointer to cleared string or NULL if input is NULL
     * @note Properly handles memory reallocation for empty string
     */
    static void *ocf_empty(char* value)
    {
        if (value == NULL)
        return NULL;
        
        // Free old memory and allocate fresh 1 byte for empty string
        char* temp = (char *) malloc( 1);
        if (temp != NULL) {
            temp[0] = '\0';
            free(value);
            return temp;
        }
        return NULL;
    }

    /**
     * @brief Free allocated string memory
     * @param value The string to free
     * @note Safely handles NULL pointers, frees any non-NULL string regardless of content
     */
    static void ocf_charptr_free(char* value)
    {
        if (value == NULL)
        {
            printf("Warning: attempting to free NULL pointer.\n");
            return;
        }
        free(value);
    }

    static bool ocf_exist(const char * value, char c)
    {
        if (value == NULL || ocf_is_empty(value))
        {
            printf("bad input: input string is empty.\n");
            return false;
        }
        for (size_t i = 0, e = ocf_length(value); i < e; i++)
        {
            if (value[i] == c)
                return true;
        }
        return false;
    }
        
    /**
     * @brief Check if substring exists in string
     * @param value_1 The main string to search in
     * @param value_2 The substring to search for
     * @return true if substring is found, false otherwise
     * @note Uses standard strstr for reliable substring search with proper pattern handling
     */
    static bool ocf_sub_exist(const char * value_1, const char * value_2)
    {
        if (value_1 == NULL || value_2 == NULL || ocf_is_empty(value_1) || ocf_is_empty(value_2))
        {
            printf("bad input: one of the input strings is empty.\n");
            return false;
        }
            
        // Use standard strstr function for reliable substring search
        // This properly handles overlapping patterns and multiple occurrences
        return strstr(value_1, value_2) != NULL ? true : false;
    }

    static size_t ocf_count(const char * value, char c)
    {
        if (value == NULL || ocf_is_empty(value))
        {
            printf("bad input: input string is empty.");
            return (size_t)0;
        }
        size_t result = 0;
        for (size_t i = 0, e = ocf_length(value); i < e; i++)
        {
            if (value[i] == c)
                result++;
        }
        return result;
    }

    static inline size_t ocf_find(const char * strInput, char ch)
    {
        size_t index = 0;
        while (strInput[index] != '\0')
        {
            if (strInput[index] == ch)
            {
                return index;
            }
            index++;
        }
        return -1; // Not found
    }

    static inline bool ocf_compare(const char * strInput1, const char * strInput2)
    {
        size_t index = 0;
        while (strInput1[index] != '\0' && strInput2[index] != '\0')
        {
            if (strInput1[index] != strInput2[index])
            {
                return false;
            }
            index++;
        }
        return strInput1[index] == '\0' && strInput2[index] == '\0'; // Both should end at the same time
    }

    static inline void ocf_copy(char* destination, const char * source)
    {
        size_t index = 0;
        while (source[index] != '\0')
        {
            destination[index] = source[index];
            index++;
        }
        destination[index] = '\0'; // Null-terminate the destination strInputing
    }

    static inline size_t ocf_count_char(const char * strInput, char ch)
    {
        size_t count = 0;
        size_t index = 0;
        while (strInput[index] != '\0')
        {
            if (strInput[index] == ch)
            {
                count++;
            }
            index++;
        }
        return count;
    }

    static size_t ocf_count_substr(const char * strInput, const char * substrInput)
    {
        size_t count = 0;
        size_t index = 0;
        size_t substrInput_len = ocf_length(substrInput);
        while (strInput[index] != '\0')
        {
            if (ocf_compare(strInput + index, substrInput))
            {
                count++;
                index += substrInput_len; // Move past the found substrInputing
            }
            else
            {
                index++;
            }
        }
        return count;
    }

    static int *ocf_locations(const char * strInput, char ch, size_t out_count)
    {
        size_t char_count = ocf_count_char(strInput, ch);
        int *indices = ocf_alloc(int, char_count);
        size_t index = 0;
        size_t found_index = 0;
        while (strInput[index] != '\0')
        {
            if (strInput[index] == ch)
            {
                indices[found_index++] = index;
            }
            index++;
        }
        out_count = char_count;
        return indices;
    }

    typedef struct ocf_str
    {
        char* data;
        size_t length;
        size_t capacity;
    }
    ocf_str;

    /**
     * @brief Initialize a cstr object.
     *
     * Allocates an initial buffer of 16 bytes, sets the length to zero and
     * ensures the string is null-terminated.  The caller must eventually
     * call cstr_free() to release the allocated memory.
     *
     * @param str Pointer to the cstr structure to initialize.
     */
    void ocf_str_init(ocf_str * strInput)
    {
        strInput->capacity = 16;
        strInput->length = 0;
        strInput->data = (char *) malloc( strInput->capacity);
        strInput->data[0] = '\0';
    }

    /**
     * @brief Append a C‑style string to a cstr.
     *
     * Ensures there is enough capacity (doubling when necessary), then
     * copies the contents of @p src to the end of @p dest and updates the
     * length field.  The destination must have been initialized.
     *
     * @param dest Pointer to the target cstr.
     * @param src  Null‑terminated source string to append.
     */
    static inline void ocf_str_append(ocf_str *dest, const char * src)
    {
        size_t src_len = strlen(src);

        if (dest->length + src_len + 1 > dest->capacity)
        {
            dest->capacity = (dest->length + src_len + 1) * 2;
            dest->data = (char* )realloc(dest->data, dest->capacity);
        }

        strcpy(dest->data + dest->length, src);
        dest->length += src_len;
    }

    /**
     * @brief Release memory held by a cstr.
     *
     * Frees the heap buffer associated with the string.  After this call the
     * cstr is no longer valid unless re‑initialized by cstr_init().
     *
     * @param str Pointer to the cstr to free.
     */
    static inline void ocf_str_free(ocf_str *strInput)
    {
        free(strInput->data);
    }

    /**
     * @brief Assign a raw C string to a cstr (by value).
     *
     * This function operates on a *copy* of the destination structure, so it
     * has no effect on the caller's object.  It simply illustrates intended
     * semantics; consider using a pointer or returning the updated struct
     * instead.
     *
     * @param destination Copy of the destination cstr structure.
     * @param source      Null‑terminated C string to assign.
     */
    static inline void ocf_str_set(ocf_str destination, char* source)
    {
        destination.data = source;
        destination.length = strlen(destination.data);
    }

    /**
     * @brief Assign one cstr to another (by value).
     *
     * Like the other overload, this modifies only the local copy of
     * @p destination.  It does not copy the character data.
     *
     * @param destination Copy of the destination cstr.
     * @param source      Source cstr to copy from.
     */
    static inline void ocf_str_copy(ocf_str destination, ocf_str source)
    {
        destination.data = source.data;
        destination.length = source.length;
    }

    /**
     * @brief Change the length of a cstr (on a copy).
     *
     * Adjusts the capacity if necessary and updates the length field.  The
     * passed structure is modified by value, so the caller's string is
     * unaffected.  After increasing the length the contents beyond the old
     * length are undefined except for the terminating null.
     *
     * @param str     cstr structure to resize (copied).
     * @param NLength New desired length (not including terminating null).
     */
    static inline void ocf_str_resize(ocf_str strInput, size_t NLength)
    {
        if (NLength + 1 > strInput.capacity)
        {
            strInput.capacity = (NLength + 1) * 2;
            strInput.data = (char* )realloc(strInput.data, strInput.capacity);
        }
        strInput.length = NLength;
        strInput.data[NLength] = '\0';
    }

    /**
     * @brief Copy cstr contents into a C buffer.
     *
     * The destination buffer must be large enough to hold the string plus
     * terminating null.
     *
     * @param destination Buffer where data will be stored.
     * @param source      Source cstr to copy from.
     */
    static inline void ocf_str_copy_to(char* destination, ocf_str source) { strcpy(destination, source.data); }

    /**
     * @brief Return the length of a cstr.
     *
     * @param source cstr whose length is queried.
     * @return Number of characters in the string (excluding null).
     */
    static inline size_t ocf_str_length(ocf_str source) { return source.length; }

    /**
     * @brief Create a lowercase copy of a cstr.
     *
     * Allocates a new buffer and returns a cstr whose characters are the
     * lowercase equivalents of those in @p source.  The caller must free the
     * returned string's data when finished.
     *
     * @param source Input string to convert.
     * @return New cstr containing lowercase text.
     */
    static inline ocf_str ocf_str_lower(ocf_str source)
    {
        ocf_str result;
        result.data = (char *) malloc( source.length + 1);
        strcpy(result.data, source.data);
        result.length = source.length;
        result.capacity = source.capacity;
        for (size_t i = 0; i < result.length; i++) {
            result.data[i] = tolower(result.data[i]);
        }
        return result;
    }

    /**
     * @brief Create an uppercase copy of a cstr.
     *
     * Similar to lower(), but converts characters to uppercase.
     *
     * @param source Input string to convert.
     * @return New cstr containing uppercase text.
     */
    static inline ocf_str ocf_str_upper(ocf_str source)
    {
        ocf_str result;
        result.data = (char *) malloc( source.length + 1);
        strcpy(result.data, source.data);
        result.length = source.length;
        result.capacity = source.capacity;
        for (size_t i = 0; i < result.length; i++) {
            result.data[i] = toupper(result.data[i]);
        }
        return result;
    }

    /**
     * @brief Concatenate two cstrs and return a new one.
     *
     * Allocates a fresh cstr containing the contents of @p destination
     * followed by @p source.  The original arguments are not modified.
     *
     * @param destination First operand.
     * @param source      Second operand to append.
     * @return Newly allocated cstr with combined text.
     */
    static inline ocf_str ocf_str_append_cstr(ocf_str destination, ocf_str source)
    {
        ocf_str result;
        result.data = (char *) malloc( destination.length + source.length + 1);
            if(destination.capacity <= destination.length + source.length) {
            result.capacity = destination.capacity + source.length + source.length / 2;
        } else {
            result.capacity = destination.capacity;
        }
        strcpy(result.data, destination.data);
        strcat(result.data, source.data);
        result.length = strlen(result.data);
        return result;
    }

    /**
     * @brief Append a C string to a cstr, returning a new object.
     *
     * Similar to the previous overload but takes a raw C string as second
     * argument.
     *
     * @param destination Base string.
     * @param source      Null‑terminated C string to append.
     * @return New cstr containing the concatenation.
     */
    static inline ocf_str ocf_str_append_string(ocf_str destination, char* source)
    {
        ocf_str result;
        result.data = (char *) malloc( destination.length + strlen(source) + 1);
        if(destination.capacity <= destination.length + strlen(source)) {
            result.capacity = destination.capacity + strlen(source) + strlen(source) / 2;
        } else {
            result.capacity = destination.capacity;
        }
        strcpy(result.data, destination.data);
        strcat(result.data, source);
        result.length = strlen(result.data);
        return result;
    }

    /**
     * @brief Append a single character to a cstr, returning a new one.
     *
     * Allocates space for the extra character and null terminator.  The
     * original string is left unchanged.
     *
     * @param destination Original string.
     * @param source      Character to append.
     * @return New cstr containing the result.
     */
    static inline ocf_str ocf_str_append_char(ocf_str destination, char source)
    {
        ocf_str result;
        result.data = (char *) malloc( destination.length + 2);
        strcpy(result.data, destination.data);
        result.capacity = destination.capacity + 2;
        result.data[destination.length] = source;
        result.data[destination.length + 1] = '\0';
        result.length = strlen(result.data);
        return result;
    }

    /**
     * @brief Determine if a character exists in the string.
     *
     * @param source The string to search.
     * @param target Character to look for.
     * @return true if @p target appears anywhere, false otherwise.
     */
    static inline bool ocf_str_search(ocf_str source, char target)
    {
        for (size_t i = 0; i < source.length; i++)
        {
            if (source.data[i] == target)
                return true;
        }
        return false;
    }

    /**
     * @brief Search for a C string inside the cstr.
     *
     * @param source The string to scan.
     * @param target Null‑terminated substring to find.
     * @return true if @p target is found, false otherwise.
     */
    static inline bool ocf_str_search_string(ocf_str source, char* target)
    {
        return strstr(source.data, target) != NULL;
    }

    /**
     * @brief Search for another cstr within this one.
     *
     * @param source Source string to examine.
     * @param target cstr to search for.
     * @return true if @p target is a substring of @p source.
     */
    static inline bool ocf_str_search_cstr(ocf_str source, ocf_str target)
    {
        return strstr(source.data, target.data) != NULL;
    }

    /**
     * @brief Split a cstr into tokens on a delimiter.
     *
     * The function uses strtok() on a writable copy of the data and returns
     * an array of freshly initialized cstrs.  The caller is responsible for
     * freeing each element and the array itself.
     *
     * @param source    The string to split; its contents are modified.
     * @param delimiter Character used as separator (default is space).
     * @param count     If non‑NULL, receives the number of tokens produced.
     * @return Pointer to dynamically allocated array of cstr tokens.
     */
    static inline ocf_str *ocf_str_split(ocf_str source, char delimiter, size_t *count)
    {
        size_t capacity = 4;
        size_t length = 0;
        ocf_str *result = ocf_alloc(ocf_str, capacity);

        char* token = strtok(source.data, delimiter);
        while (token != NULL)
        {
            if (length >= capacity)
            {
                capacity *= 2;
                result = (ocf_str *)realloc(result, capacity * sizeof(ocf_str));
            }
            ocf_str_init(&result[length]);
            ocf_str_append(&result[length], token);
            length++;
            token = strtok(NULL, delimiter);
        }
        *count = length;
        return result;
    }

    /**
     * @brief Extract a substring from a cstr.
     *
     * Allocates a new cstr containing @p length characters starting at
     * position @p start from @p source.  No bounds checking is performed.
     *
     * @param source The original string.
     * @param start  Zero‑based start index.
     * @param length Number of characters to include.
     * @return New cstr with the requested slice.
     */
    static inline ocf_str ocf_str_substring(ocf_str source, size_t start, size_t length)
    {
        ocf_str result;
        result.data = (char *) malloc( length + 1);
        strncpy(result.data, source.data + start, length);
        result.data[length] = '\0';
        result.length = length;
        result.capacity = source.capacity;
        return result;
    }

    /**
     * @brief Return a new cstr containing the reverse of the input.
     *
     * The returned string is freshly allocated; the original is unchanged.
     *
     * @param source String to reverse.
     * @return Reversed copy of @p source.
     */
    static inline ocf_str ocf_str_reverse(ocf_str source)
    {
        ocf_str result;
        result.data = (char *) malloc( source.length + 1);
        for (size_t i = 0; i < source.length; i++)
            result.data[i] = source.data[source.length - 1 - i];
        result.data[source.length] = '\0';
        result.length = source.length;
        result.capacity = source.capacity;
        return result;
    }

    // Insert Begning and End

    /**
     * @brief Insert a substring at an arbitrary position.
     *
     * The function shifts the tail of @p source to make room for
     * @p substring.  If @p position is larger than the current length it is
     * treated as an append.  Capacity is grown if necessary.
     *
     * @param source    Pointer to the string to modify.
     * @param substring Null‑terminated substring to insert.
     * @param position  Insertion index (0 = beginning).
     */
    static inline void ocf_str_insertBE(ocf_str *source, char* substring, size_t position)
    {
        if (position > source->length)
            position = source->length;

        size_t substring_len = strlen(substring);
        size_t new_length = source->length + substring_len;

        if (new_length + 1 > source->capacity)
        {
            source->capacity = (new_length + 1) * 2;
            source->data = (char* )realloc(source->data, source->capacity);
        }

        memmove(source->data + position + substring_len, source->data + position, source->length - position + 1);
        memcpy(source->data + position, substring, substring_len);
        source->length = new_length;
    }

    /**
     * @brief Insert a substring at the beginning of a cstr.
     *
     * Convenience wrapper around insertBE() with position set to 0.
     *
     * @param source    Pointer to the string to modify.
     * @param substring Null‑terminated substring to insert.
     */
    static inline void ocf_str_insertB(ocf_str *source, char* substring)
    {
        ocf_str_insertBE(source, substring, 0);
    }

    // Insert End

    /**
     * @brief Append a substring to the end of a cstr.
     *
     * Convenience wrapper around insertBE() with position equal to the
     * current string length, effectively performing an append.
     *
     * @param source    Pointer to the string to modify.
     * @param substring Null‑terminated substring to insert.
     */
    static inline void ocf_str_insertE(ocf_str *source, char* substring)
    {
        ocf_str_insertBE(source, substring, source->length);
    }

    static inline size_t ocf_str_where(ocf_str strInput, char ch)
    {
        for (size_t index = 0; index < strInput.length; index++)
        {
            if (strInput.data[index] == ch)
            {
                return index;
            }
        }
        return -1; // Not found
    }

    static inline bool ocf_str_exist(ocf_str strInput, char ch)
    {
        for (size_t index = 0; index < strInput.length; index++)
        {
            if (strInput.data[index] == ch)
            {
                return true;
            }
        }
        return false; // Not found
    }

    static inline bool ocf_str_exist(ocf_str strInput, char* substr)
    {
        return strstr(strInput.data, substr) != NULL;
    }

    static inline bool ocf_str_exist(ocf_str strInput, ocf_str substr)
    {
        return strstr(strInput.data, substr.data) != NULL;
    }

#else

    static inline size_t length(const char * value) { return (value != NULL) ? strlen(value) : 0; }

    static inline bool equal(const char * value_1, const char * value_2)
    {
        if (value_1 == NULL || value_2 == NULL)
        return false;
        return strcmp(value_1, value_2) == 0 ? true : false;
    }

    static inline char* concatenate(char* value_1, const char * value_2)
    {
        if (value_1 == NULL || value_2 == NULL)
        return value_1;
        return strcat(value_1, value_2);
    }

    static inline bool is_empty(const char * value) { return (value == NULL || strlen(value) == 0) ? true : false; }

    /**
     * @brief Clear string content by reallocating to empty string
     * @param value The string to clear
     * @return Pointer to cleared string or NULL if input is NULL
     * @note Properly handles memory reallocation for empty string
     */
    static void *empty(char* value)
    {
        if (value == NULL)
        return NULL;
        
        // Free old memory and allocate fresh 1 byte for empty string
        char* temp = (char *) malloc( 1);
        if (temp != NULL) {
            temp[0] = '\0';
            free(value);
            return temp;
        }
        return NULL;
    }

    /**
     * @brief Free allocated string memory
     * @param value The string to free
     * @note Safely handles NULL pointers, frees any non-NULL string regardless of content
     */
    static void charptr_free(char* value)
    {
        if (value == NULL)
        {
            printf("Warning: attempting to free NULL pointer.\n");
            return;
        }
        free(value);
    }

    static bool exist(const char * value, char c)
    {
        if (value == NULL || is_empty(value))
        {
            printf("bad input: input string is empty.\n");
            return false;
        }
        for (size_t i = 0, e = length(value); i < e; i++)
        {
            if (value[i] == c)
                return true;
        }
        return false;
    }
        
    /**
     * @brief Check if substring exists in string
     * @param value_1 The main string to search in
     * @param value_2 The substring to search for
     * @return true if substring is found, false otherwise
     * @note Uses standard strstr for reliable substring search with proper pattern handling
     */
    static bool sub_exist(const char * value_1, const char * value_2)
    {
        if (value_1 == NULL || value_2 == NULL || is_empty(value_1) || is_empty(value_2))
        {
            printf("bad input: one of the input strings is empty.\n");
            return false;
        }
            
        // Use standard strstr function for reliable substring search
        // This properly handles overlapping patterns and multiple occurrences
        return strstr(value_1, value_2) != NULL ? true : false;
    }

    static size_t count(const char * value, char c)
    {
        if (value == NULL || is_empty(value))
        {
            printf("bad input: input string is empty.");
            return (size_t)0;
        }
        size_t result = 0;
        for (size_t i = 0, e = length(value); i < e; i++)
        {
            if (value[i] == c)
                result++;
        }
        return result;
    }

    static inline size_t find(const char * strInput, char ch)
    {
        size_t index = 0;
        while (strInput[index] != '\0')
        {
            if (strInput[index] == ch)
            {
                return index;
            }
            index++;
        }
        return -1; // Not found
    }

    static inline bool compare(const char * strInput1, const char * strInput2)
    {
        size_t index = 0;
        while (strInput1[index] != '\0' && strInput2[index] != '\0')
        {
            if (strInput1[index] != strInput2[index])
            {
                return false;
            }
            index++;
        }
        return strInput1[index] == '\0' && strInput2[index] == '\0'; // Both should end at the same time
    }

    static inline void copy(char* destination, const char * source)
    {
        size_t index = 0;
        while (source[index] != '\0')
        {
            destination[index] = source[index];
            index++;
        }
        destination[index] = '\0'; // Null-terminate the destination strInputing
    }

    static inline size_t count_char(const char * strInput, char ch)
    {
        size_t count = 0;
        size_t index = 0;
        while (strInput[index] != '\0')
        {
            if (strInput[index] == ch)
            {
                count++;
            }
            index++;
        }
        return count;
    }

    static size_t count_substr(const char * strInput, const char * substrInput)
    {
        size_t count = 0;
        size_t index = 0;
        size_t substrInput_len = length(substrInput);
        while (strInput[index] != '\0')
        {
            if (compare(strInput + index, substrInput))
            {
                count++;
                index += substrInput_len; // Move past the found substrInputing
            }
            else
            {
                index++;
            }
        }
        return count;
    }

    static int *locations(const char * strInput, char ch, size_t out_count)
    {
        size_t char_count = count_char(strInput, ch);
        int *indices = (int *) malloc( char_count);
        size_t index = 0;
        size_t found_index = 0;
        while (strInput[index] != '\0')
        {
            if (strInput[index] == ch)
            {
                indices[found_index++] = index;
            }
            index++;
        }
        out_count = char_count;
        return indices;
    }

    typedef struct cstr
    {
        char* data;
        size_t length;
        size_t capacity;
    }
    cstr;

    /**
     * @brief Initialize a cstr object.
     *
     * Allocates an initial buffer of 16 bytes, sets the length to zero and
     * ensures the string is null-terminated.  The caller must eventually
     * call cstr_free() to release the allocated memory.
     *
     * @param str Pointer to the cstr structure to initialize.
     */
    void cstr_init(cstr * strInput)
    {
        strInput->capacity = 16;
        strInput->length = 0;
        strInput->data = (char *) malloc( strInput->capacity);
        strInput->data[0] = '\0';
    }

    /**
     * @brief Append a C‑style string to a cstr.
     *
     * Ensures there is enough capacity (doubling when necessary), then
     * copies the contents of @p src to the end of @p dest and updates the
     * length field.  The destination must have been initialized.
     *
     * @param dest Pointer to the target cstr.
     * @param src  Null‑terminated source string to append.
     */
    static inline void cstr_append(cstr *dest, const char * src)
    {
        size_t src_len = strlen(src);

        if (dest->length + src_len + 1 > dest->capacity)
        {
            dest->capacity = (dest->length + src_len + 1) * 2;
            dest->data = (char* )realloc(dest->data, dest->capacity);
        }

        strcpy(dest->data + dest->length, src);
        dest->length += src_len;
    }

    /**
     * @brief Release memory held by a cstr.
     *
     * Frees the heap buffer associated with the string.  After this call the
     * cstr is no longer valid unless re‑initialized by cstr_init().
     *
     * @param str Pointer to the cstr to free.
     */
    static inline void cstr_free(cstr *strInput)
    {
        free(strInput->data);
    }

    /**
     * @brief Assign a raw C string to a cstr (by value).
     *
     * This function operates on a *copy* of the destination structure, so it
     * has no effect on the caller's object.  It simply illustrates intended
     * semantics; consider using a pointer or returning the updated struct
     * instead.
     *
     * @param destination Copy of the destination cstr structure.
     * @param source      Null‑terminated C string to assign.
     */
    static inline void cstr_set(cstr destination, char* source)
    {
        destination.data = source;
        destination.length = strlen(destination.data);
    }

    /**
     * @brief Assign one cstr to another (by value).
     *
     * Like the other overload, this modifies only the local copy of
     * @p destination.  It does not copy the character data.
     *
     * @param destination Copy of the destination cstr.
     * @param source      Source cstr to copy from.
     */
    static inline void cstr_copy(cstr destination, cstr source)
    {
        destination.data = source.data;
        destination.length = source.length;
    }

    /**
     * @brief Change the length of a cstr (on a copy).
     *
     * Adjusts the capacity if necessary and updates the length field.  The
     * passed structure is modified by value, so the caller's string is
     * unaffected.  After increasing the length the contents beyond the old
     * length are undefined except for the terminating null.
     *
     * @param str     cstr structure to resize (copied).
     * @param NLength New desired length (not including terminating null).
     */
    static inline void cstr_resize(cstr strInput, size_t NLength)
    {
        if (NLength + 1 > strInput.capacity)
        {
            strInput.capacity = (NLength + 1) * 2;
            strInput.data = (char* )realloc(strInput.data, strInput.capacity);
        }
        strInput.length = NLength;
        strInput.data[NLength] = '\0';
    }

    /**
     * @brief Copy cstr contents into a C buffer.
     *
     * The destination buffer must be large enough to hold the string plus
     * terminating null.
     *
     * @param destination Buffer where data will be stored.
     * @param source      Source cstr to copy from.
     */
    static inline void cstr_copy_to(char* destination, cstr source) { strcpy(destination, source.data); }

    /**
     * @brief Return the length of a cstr.
     *
     * @param source cstr whose length is queried.
     * @return Number of characters in the string (excluding null).
     */
    static inline size_t cstr_length(cstr source) { return source.length; }

    /**
     * @brief Create a lowercase copy of a cstr.
     *
     * Allocates a new buffer and returns a cstr whose characters are the
     * lowercase equivalents of those in @p source.  The caller must free the
     * returned string's data when finished.
     *
     * @param source Input string to convert.
     * @return New cstr containing lowercase text.
     */
    static cstr cstr_lower(cstr source)
    {
        cstr result;
        result.data = (char *) malloc( source.length + 1);
        strcpy(result.data, source.data);
        result.length = source.length;
        result.capacity = source.capacity;
        for (size_t i = 0; i < result.length; i++) {
            result.data[i] = tolower(result.data[i]);
        }
        return result;
    }

    /**
     * @brief Create an uppercase copy of a cstr.
     *
     * Similar to lower(), but converts characters to uppercase.
     *
     * @param source Input string to convert.
     * @return New cstr containing uppercase text.
     */
    static cstr cstr_upper(cstr source)
    {
        cstr result;
        result.data = (char *) malloc( source.length + 1);
        strcpy(result.data, source.data);
        result.length = source.length;
        result.capacity = source.capacity;
        for (size_t i = 0; i < result.length; i++) {
            result.data[i] = toupper(result.data[i]);
        }
        return result;
    }

    /**
     * @brief Concatenate two cstrs and return a new one.
     *
     * Allocates a fresh cstr containing the contents of @p destination
     * followed by @p source.  The original arguments are not modified.
     *
     * @param destination First operand.
     * @param source      Second operand to append.
     * @return Newly allocated cstr with combined text.
     */
    static cstr cstr_append_cstr(cstr destination, cstr source)
    {
        cstr result;
        result.data = (char *) malloc( destination.length + source.length + 1);
            if(destination.capacity <= destination.length + source.length) {
            result.capacity = destination.capacity + source.length + source.length / 2;
        } else {
            result.capacity = destination.capacity;
        }
        strcpy(result.data, destination.data);
        strcat(result.data, source.data);
        result.length = strlen(result.data);
        return result;
    }

    /**
     * @brief Append a C string to a cstr, returning a new object.
     *
     * Similar to the previous overload but takes a raw C string as second
     * argument.
     *
     * @param destination Base string.
     * @param source      Null‑terminated C string to append.
     * @return New cstr containing the concatenation.
     */
    static cstr cstr_append_string(cstr destination, char* source)
    {
        cstr result;
        result.data = (char *) malloc( destination.length + strlen(source) + 1);
        if(destination.capacity <= destination.length + strlen(source)) {
            result.capacity = destination.capacity + strlen(source) + strlen(source) / 2;
        } else {
            result.capacity = destination.capacity;
        }
        strcpy(result.data, destination.data);
        strcat(result.data, source);
        result.length = strlen(result.data);
        return result;
    }

    /**
     * @brief Append a single character to a cstr, returning a new one.
     *
     * Allocates space for the extra character and null terminator.  The
     * original string is left unchanged.
     *
     * @param destination Original string.
     * @param source      Character to append.
     * @return New cstr containing the result.
     */
    static cstr cstr_append_char(cstr destination, char source)
    {
        cstr result;
        result.data = (char *) malloc( destination.length + 2);
        strcpy(result.data, destination.data);
        result.capacity = destination.capacity + 2;
        result.data[destination.length] = source;
        result.data[destination.length + 1] = '\0';
        result.length = strlen(result.data);
        return result;
    }

    /**
     * @brief Determine if a character exists in the string.
     *
     * @param source The string to search.
     * @param target Character to look for.
     * @return true if @p target appears anywhere, false otherwise.
     */
    static inline bool cstr_search(cstr source, char target)
    {
        for (size_t i = 0; i < source.length; i++)
        {
            if (source.data[i] == target)
                return true;
        }
        return false;
    }

    /**
     * @brief Search for a C string inside the cstr.
     *
     * @param source The string to scan.
     * @param target Null‑terminated substring to find.
     * @return true if @p target is found, false otherwise.
     */
    static inline bool cstr_search_string(cstr source, char* target)
    {
        return strstr(source.data, target) != NULL;
    }

    /**
     * @brief Search for another cstr within this one.
     *
     * @param source Source string to examine.
     * @param target cstr to search for.
     * @return true if @p target is a substring of @p source.
     */
    static inline bool cstr_search_cstr(cstr source, cstr target)
    {
        return strstr(source.data, target.data) != NULL;
    }

    /**
     * @brief Split a cstr into tokens on a delimiter.
     *
     * The function uses strtok() on a writable copy of the data and returns
     * an array of freshly initialized cstrs.  The caller is responsible for
     * freeing each element and the array itself.
     *
     * @param source    The string to split; its contents are modified.
     * @param delimiter Character used as separator (default is space).
     * @param count     If non‑NULL, receives the number of tokens produced.
     * @return Pointer to dynamically allocated array of cstr tokens.
     */
    static cstr *cstr_split(cstr source, char delimiter, size_t *count)
    {
        size_t capacity = 4;
        size_t length = 0;
        cstr *result = (cstr *) malloc(capacity);

        char* token = strtok(source.data, delimiter);
        while (token != NULL)
        {
            if (length >= capacity)
            {
                capacity *= 2;
                result = (cstr *)realloc(result, capacity * sizeof(cstr));
            }
            cstr_init(&result[length]);
            cstr_append(&result[length], token);
            length++;
            token = strtok(NULL, delimiter);
        }
        *count = length;
        return result;
    }

    /**
     * @brief Extract a substring from a cstr.
     *
     * Allocates a new cstr containing @p length characters starting at
     * position @p start from @p source.  No bounds checking is performed.
     *
     * @param source The original string.
     * @param start  Zero‑based start index.
     * @param length Number of characters to include.
     * @return New cstr with the requested slice.
     */
    static cstr cstr_substring(cstr source, size_t start, size_t length)
    {
        cstr result;
        result.data = (char *) malloc( length + 1);
        strncpy(result.data, source.data + start, length);
        result.data[length] = '\0';
        result.length = length;
        result.capacity = source.capacity;
        return result;
    }

    /**
     * @brief Return a new cstr containing the reverse of the input.
     *
     * The returned string is freshly allocated; the original is unchanged.
     *
     * @param source String to reverse.
     * @return Reversed copy of @p source.
     */
    static cstr cstr_reverse(cstr source)
    {
        cstr result;
        result.data = (char *) malloc( source.length + 1);
        for (size_t i = 0; i < source.length; i++)
            result.data[i] = source.data[source.length - 1 - i];
        result.data[source.length] = '\0';
        result.length = source.length;
        result.capacity = source.capacity;
        return result;
    }

    // Insert Begning and End

    /**
     * @brief Insert a substring at an arbitrary position.
     *
     * The function shifts the tail of @p source to make room for
     * @p substring.  If @p position is larger than the current length it is
     * treated as an append.  Capacity is grown if necessary.
     *
     * @param source    Pointer to the string to modify.
     * @param substring Null‑terminated substring to insert.
     * @param position  Insertion index (0 = beginning).
     */
    static void cstr_insertBE(cstr *source, char* substring, size_t position)
    {
        if (position > source->length)
            position = source->length;

        size_t substring_len = strlen(substring);
        size_t new_length = source->length + substring_len;

        if (new_length + 1 > source->capacity)
        {
            source->capacity = (new_length + 1) * 2;
            source->data = (char* )realloc(source->data, source->capacity);
        }

        memmove(source->data + position + substring_len, source->data + position, source->length - position + 1);
        memcpy(source->data + position, substring, substring_len);
        source->length = new_length;
    }

    /**
     * @brief Insert a substring at the beginning of a cstr.
     *
     * Convenience wrapper around insertBE() with position set to 0.
     *
     * @param source    Pointer to the string to modify.
     * @param substring Null‑terminated substring to insert.
     */
    static inline void cstr_insertB(cstr *source, char* substring)
    {
        cstr_insertBE(source, substring, 0);
    }

    // Insert End

    /**
     * @brief Append a substring to the end of a cstr.
     *
     * Convenience wrapper around insertBE() with position equal to the
     * current string length, effectively performing an append.
     *
     * @param source    Pointer to the string to modify.
     * @param substring Null‑terminated substring to insert.
     */
    static inline void cstr_insertE(cstr *source, char* substring)
    {
        cstr_insertBE(source, substring, source->length);
    }

    static inline size_t cstr_where(cstr strInput, char ch)
    {
        for (size_t index = 0; index < strInput.length; index++)
        {
            if (strInput.data[index] == ch)
            {
                return index;
            }
        }
        return -1; // Not found
    }

    static inline bool cstr_exist(cstr strInput, char ch)
    {
        for (size_t index = 0; index < strInput.length; index++)
        {
            if (strInput.data[index] == ch)
            {
                return true;
            }
        }
        return false; // Not found
    }

    static inline bool cstr_exist(cstr strInput, char* substr)
    {
        return strstr(strInput.data, substr) != NULL;
    }

    static inline bool cstr_exist(cstr strInput, cstr substr)
    {
        return strstr(strInput.data, substr.data) != NULL;
    }

#endif

#endif // OPENCF___CFROST___CGEN___STRING_H