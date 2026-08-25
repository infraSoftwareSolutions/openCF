#include "string.h"

#ifndef OPENCF___CFROST___CGEN___WARNING_H
#define OPENCF___CFROST___CGEN___WARNING_H

#if defined(OPENCF_FOR_GNU)

    size_t ocf_warning_counter = 0;

    typedef struct ocf_warning {
        char* name;
        char* description;
        char* file;
        char* time;
        size_t line;
        size_t number;
    } ocf_warning;

    static inline ocf_warning ocf_warning_init() {
        ocf_warning w;
        w.name = NULL;
        w.description = NULL;
        w.file = NULL;
        w.time = NULL;
        w.line = 0;
        w.number = ocf_warning_counter;
        ocf_warning_counter++;
        return w;
    }

    static inline void ocf_warning_print(ocf_warning w) {
        printf("\n");
        printf("------------\n");
        printf("<<< WARNING >>>\n");
        printf("------------\n");
        if(w.name != NULL && strlen(w.name) != 0) {
            printf("NAME: %s \n", w.name);
        }
        if(w.description != NULL && strlen(w.description) != 0) {
            printf("DESCRIPTION: %s \n", w.description);
        }
        printf("FILE: %s \n", w.file);
        printf("TIME: %s \n", w.time);
        printf("LINE: %d \n", w.line);
        printf("NUMBER: %d \n", w.number);
        printf("------------\n");
    }

    static inline ocf_warning ocf_warning_wrong_indexing(char* description) {
        ocf_warning w;
        w.name = "Wrong Indexing";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = ocf_warning_counter;
        ocf_warning_counter++;
        return w;
    }

    static inline ocf_warning ocf_warning_wrong_declaration(char* description) {
        ocf_warning w;
        w.name = "Wrong declaration";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = ocf_warning_counter;
        ocf_warning_counter++;
        return w;
    }

    static inline ocf_warning ocf_warning_wrong_construction(char* description) {
        ocf_warning w;
        w.name = "Wrong Construction";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = ocf_warning_counter;
        ocf_warning_counter++;
        return w;
    }

    static inline ocf_warning ocf_warning_bad_input(char* description) {
        ocf_warning w;
        w.name = "Bad Input";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = ocf_warning_counter;
        ocf_warning_counter++;
        return w;
    }

    static inline ocf_warning ocf_warning_undefined_behavior(char* description) {
        ocf_warning w;
        w.name = "Undefined Behavior";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = ocf_warning_counter;
        ocf_warning_counter++;
        return w;
    }

    static inline ocf_warning ocf_warning_invalid_argument(char* description) {
        ocf_warning w;
        w.name = "Invalid Argument";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = ocf_warning_counter;
        ocf_warning_counter++;
        return w;
    }

    static inline ocf_warning ocf_warning_out_of_range(char* description) {
        ocf_warning w;
        w.name = "Out Of Range";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = ocf_warning_counter;
        ocf_warning_counter++;
        return w;
    }

    static inline ocf_warning ocf_warning_internal_problem(char* description) {
        ocf_warning w;
        w.name = "Internal Problem";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = ocf_warning_counter;
        ocf_warning_counter++;
        return w;
    }

    static void ocf_warning_free(ocf_warning* self) {
        free(self->name);
        free(self->description);
        free(self->file);
        free(self->time);
    }

#else

    size_t cwarningCounter = 0;

    typedef struct cwarning {
        char* name;
        char* description;
        char* file;
        char* time;
        size_t line;
        size_t number;
    } cwarning;

    static inline cwarning cwarning_init() {
        cwarning w;
        w.name = NULL;
        w.description = NULL;
        w.file = NULL;
        w.time = NULL;
        w.line = 0;
        w.number = cwarningCounter;
        cwarningCounter++;
        return w;
    }

    static inline void cwarning_print(cwarning w) {
        printf("\n");
        printf("------------\n");
        printf("<<< WARNING >>>\n");
        printf("------------\n");
        if(w.name != NULL && strlen(w.name) != 0) {
            printf("NAME: %s \n", w.name);
        }
        if(w.description != NULL && strlen(w.description) != 0) {
            printf("DESCRIPTION: %s \n", w.description);
        }
        printf("FILE: %s \n", w.file);
        printf("TIME: %s \n", w.time);
        printf("LINE: %d \n", w.line);
        printf("NUMBER: %d \n", w.number);
        printf("------------\n");
    }

    static inline cwarning cwarning_wrong_indexing(char* description) {
        cwarning w;
        w.name = "Wrong Indexing";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = cwarningCounter;
        cwarningCounter++;
        return w;
    }

    static inline cwarning cwarning_wrong_declaration(char* description) {
        cwarning w;
        w.name = "Wrong declaration";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = cwarningCounter;
        cwarningCounter++;
        return w;
    }

    static inline cwarning cwarning_wrong_construction(char* description) {
        cwarning w;
        w.name = "Wrong Construction";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = cwarningCounter;
        cwarningCounter++;
        return w;
    }

    static inline cwarning cwarning_bad_input(char* description) {
        cwarning w;
        w.name = "Bad Input";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = cwarningCounter;
        cwarningCounter++;
        return w;
    }

    static inline cwarning cwarning_undefined_behavior(char* description) {
        cwarning w;
        w.name = "Undefined Behavior";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = cwarningCounter;
        cwarningCounter++;
        return w;
    }

    static inline cwarning cwarning_invalid_argument(char* description) {
        cwarning w;
        w.name = "Invalid Argument";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = cwarningCounter;
        cwarningCounter++;
        return w;
    }

    static inline cwarning cwarning_out_of_range(char* description) {
        cwarning w;
        w.name = "Out Of Range";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = cwarningCounter;
        cwarningCounter++;
        return w;
    }

    static inline cwarning cwarning_internal_problem(char* description) {
        cwarning w;
        w.name = "Internal Problem";
        w.description = description;
        w.file = __FILE_NAME__;
        w.time = __TIME__;
        w.line = __LINE__;
        w.number = cwarningCounter;
        cwarningCounter++;
        return w;
    }

    static void cwarning_free(cwarning* self) {
        free(self->name);
        free(self->description);
        free(self->file);
        free(self->time);
    }

#endif

#endif // OPENCF___CFROST___CGEN___WARNING_H