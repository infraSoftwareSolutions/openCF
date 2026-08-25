#include "string.h"

#ifndef OPENCF___CFROST___CGEN___ERROR_H
#define OPENCF___CFROST___CGEN___ERROR_H

#if defined(OPENCF_FOR_GNU)

    typedef struct ocf_error {
        char* name;
        char* description;
        char* file;
        char* time;
        size_t line;
    } ocf_error;

    static inline ocf_error ocf_error_init() {
        ocf_error err;
        err.name = NULL;
        err.description = NULL;
        err.file = NULL;
        err.time = NULL;
        err.line = 0;
        return err;
    }

    static inline void ocf_error_print(ocf_error err) {
        printf("\n");
        printf("------------\n");
        printf("<<< ERROR >>>\n");
        printf("------------\n");
        if(err.name != NULL && strlen(err.name) != 0) {
            printf("NAME: %s \n", err.name);
        }
        if(err.description != NULL && strlen(err.description) != 0) {
            printf("DESCRIPTION: %s \n", err.description);
        }
        printf("FILE: %s \n", err.file);
        printf("TIME: %s \n", err.time);
        printf("LINE: %d \n", err.line);
        printf("------------\n");
    }

    static inline ocf_error ocf_error_indexing(char* description) {
        ocf_error err;
        err.name = "Indexing Error";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline ocf_error ocf_error_declaration(char* description) {
        ocf_error err;
        err.name = "Declaration Error";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline ocf_error ocf_error_construction(char* description) {
        ocf_error err;
        err.name = "Construction Error";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline ocf_error ocf_error_bad_input(char* description) {
        ocf_error err;
        err.name = "Bad Input";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline ocf_error ocf_error_undefined_behavior(char* description) {
        ocf_error err;
        err.name = "Undefined Behavior";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline ocf_error ocf_error_invalid_argument(char* description) {
        ocf_error err;
        err.name = "Invalid Argument";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline ocf_error ocf_error_out_of_range(char* description) {
        ocf_error err;
        err.name = "Out Of Range";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline ocf_error ocf_error_internal_problem(char* description) {
        ocf_error err;
        err.name = "Internal Problem";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static void ocf_error_free(ocf_error* self) {
        free(self->name);
        free(self->description);
        free(self->file);
        free(self->time);
    }

#else

    typedef struct {
        char* name;
        char* description;
        char* file;
        char* time;
        size_t line;
    } cerror;

    static inline cerror error_init() {
        cerror err;
        err.name = NULL;
        err.description = NULL;
        err.file = NULL;
        err.time = NULL;
        err.line = 0;
        return err;
    }

    static inline void error_print(cerror err) {
        printf("\n");
        printf("------------\n");
        printf("<<< ERROR >>>\n");
        printf("------------\n");
        if(err.name != NULL && strlen(err.name) != 0) {
            printf("NAME: %s \n", err.name);
        }
        if(err.description != NULL && strlen(err.description) != 0) {
            printf("DESCRIPTION: %s \n", err.description);
        }
        printf("FILE: %s \n", err.file);
        printf("TIME: %s \n", err.time);
        printf("LINE: %d \n", err.line);
        printf("------------\n");
    }

    static inline cerror error_indexing(char* description) {
        cerror err;
        err.name = "Indexing Error";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline cerror error_declaration(char* description) {
        cerror err;
        err.name = "Declaration Error";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline cerror error_construction(char* description) {
        cerror err;
        err.name = "Construction Error";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline cerror error_bad_input(char* description) {
        cerror err;
        err.name = "Bad Input";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline cerror error_undefined_behavior(char* description) {
        cerror err;
        err.name = "Undefined Behavior";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline cerror error_invalid_argument(char* description) {
        cerror err;
        err.name = "Invalid Argument";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline cerror error_out_of_range(char* description) {
        cerror err;
        err.name = "Out Of Range";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static inline cerror error_internal_problem(char* description) {
        cerror err;
        err.name = "Internal Problem";
        err.description = description;
        err.file = __FILE_NAME__;
        err.time = __TIME__;
        err.line = __LINE__;
        return err;
    }

    static void error_free(cerror* self) {
        free(self->name);
        free(self->description);
        free(self->file);
        free(self->time);
    }

#endif

#endif // OPENCF___CFROST___CGEN___ERROR_H