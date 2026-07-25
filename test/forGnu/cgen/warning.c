#define OPENCF_FOR_GNU
#include "cfrost.h"
#include "cfrost/cgen/warning.h"

OCF_TEST_MAIN(cgen: warning);

    // Reset counter for consistent testing
    size_t ocf_warningCounter = 0;
    
    // Test 1: ocf_warning_init() - Initialize warning with default values
    ocf_warning w1 = ocf_warning_init();
    OCF_TEST_EQU(w1.name == NULL, true);                    // name should be NULL
    OCF_TEST_EQU(w1.description == NULL, true);             // description should be NULL
    OCF_TEST_EQU(w1.file == NULL, true);                    // file should be NULL
    OCF_TEST_EQU(w1.time == NULL, true);                    // time should be NULL
    OCF_TEST_EQU(w1.line, 0);                               // line should be 0
    OCF_TEST_EQU(w1.number, 0);                             // number should be 0 (first init)
    
    // Test 2: Counter increments after init
    size_t counter_before = ocf_warningCounter;
    ocf_warning w2 = ocf_warning_init();
    OCF_TEST_EQU(w2.number, counter_before);                // number should match counter
    OCF_TEST_EQU(ocf_warningCounter, counter_before + 1);      // counter should increment
    
    // Test 3: wrong_indexing() - Create wrong indexing warning
    size_t counter_start = ocf_warningCounter;
    ocf_warning w_index = ocf_warning_wrong_indexing("Array boundary check");
    OCF_TEST_EQU(w_index.name != NULL, true);               // name should not be NULL
    OCF_TEST_EQU(strcmp(w_index.name, "Wrong Indexing"), 0);    // verify name
    OCF_TEST_EQU(w_index.description != NULL, true);        // description should not be NULL
    OCF_TEST_EQU(strcmp(w_index.description, "Array boundary check"), 0);  // verify description
    OCF_TEST_EQU(w_index.file != NULL, true);               // file should be set
    OCF_TEST_EQU(w_index.time != NULL, true);               // time should be set
    OCF_TEST_ASSERT(w_index.line > 0);                    // line should be set (> 0)
    OCF_TEST_EQU(w_index.number, counter_start);            // number should match counter
    OCF_TEST_EQU(ocf_warningCounter, counter_start + 1);       // counter should increment
    
    // Test 4: wrong_declaration() - Create wrong declaration warning
    counter_before = ocf_warningCounter;
    ocf_warning w_decl = ocf_warning_wrong_declaration("Unused variable");
    OCF_TEST_EQU(w_decl.name != NULL, true);                // name should not be NULL
    OCF_TEST_EQU(strcmp(w_decl.name, "Wrong declaration"), 0);   // verify name
    OCF_TEST_EQU(w_decl.description != NULL, true);         // description should not be NULL
    OCF_TEST_EQU(strcmp(w_decl.description, "Unused variable"), 0);  // verify description
    OCF_TEST_EQU(w_decl.number, counter_before);            // verify counter
    OCF_TEST_EQU(ocf_warningCounter, counter_before + 1);      // counter incremented
    
    // Test 5: wrong_construction() - Create wrong construction warning
    counter_before = ocf_warningCounter;
    ocf_warning w_cons = ocf_warning_wrong_construction("Incomplete initialization");
    OCF_TEST_EQU(w_cons.name != NULL, true);                // name should not be NULL
    OCF_TEST_EQU(strcmp(w_cons.name, "Wrong Construction"), 0);   // verify name
    OCF_TEST_EQU(w_cons.description != NULL, true);         // description should not be NULL
    OCF_TEST_EQU(w_cons.number, counter_before);            // verify counter
    
    // Test 6: bad_input() - Create bad input warning
    counter_before = ocf_warningCounter;
    ocf_warning w_input = ocf_warning_bad_input("Suspicious value detected");
    OCF_TEST_EQU(w_input.name != NULL, true);               // name should not be NULL
    OCF_TEST_EQU(strcmp(w_input.name, "Bad Input"), 0);     // verify name
    OCF_TEST_EQU(w_input.description != NULL, true);        // description should not be NULL
    OCF_TEST_EQU(w_input.number, counter_before);           // verify counter incremented
    
    // Test 7: undefined_behavior() - Create undefined behavior warning
    counter_before = ocf_warningCounter;
    ocf_warning w_undef = ocf_warning_undefined_behavior("Potential memory issue");
    OCF_TEST_EQU(w_undef.name != NULL, true);               // name should not be NULL
    OCF_TEST_EQU(strcmp(w_undef.name, "Undefined Behavior"), 0);  // verify name
    OCF_TEST_EQU(w_undef.description != NULL, true);        // description should not be NULL
    OCF_TEST_EQU(w_undef.number, counter_before);           // verify counter
    
    // Test 8: invalid_argument() - Create invalid argument warning
    counter_before = ocf_warningCounter;
    ocf_warning w_arg = ocf_warning_invalid_argument("Type mismatch warning");
    OCF_TEST_EQU(w_arg.name != NULL, true);                 // name should not be NULL
    OCF_TEST_EQU(strcmp(w_arg.name, "Invalid Argument"), 0);     // verify name
    OCF_TEST_EQU(w_arg.description != NULL, true);          // description should not be NULL
    OCF_TEST_EQU(w_arg.number, counter_before);             // verify counter incremented
    
    // Test 9: Sequential warnings have unique numbers
    ocf_warningCounter = 100;  // Set custom start
    ocf_warning seq1 = ocf_warning_wrong_indexing("First");
    ocf_warning seq2 = ocf_warning_bad_input("Second");
    ocf_warning seq3 = ocf_warning_invalid_argument("Third");
    OCF_TEST_EQU(seq1.number, 100);                         // first number
    OCF_TEST_EQU(seq2.number, 101);                         // second number (incremented)
    OCF_TEST_EQU(seq3.number, 102);                         // third number (incremented)
    OCF_TEST_EQU(ocf_warningCounter, 103);                     // counter at 103
    
    // Test 10: Warning with empty description
    counter_before = ocf_warningCounter;
    ocf_warning w_empty = ocf_warning_bad_input("");
    OCF_TEST_EQU(w_empty.name != NULL, true);               // name should not be NULL
    OCF_TEST_EQU(w_empty.description != NULL, true);        // description initialized
    OCF_TEST_EQU(strlen(w_empty.description), 0);           // should be empty
    OCF_TEST_EQU(w_empty.number, counter_before);           // number properly set
    
    // Test 11: All warning creators preserve name correctly
    ocf_warning wt1 = ocf_warning_wrong_indexing("test");
    ocf_warning wt2 = ocf_warning_wrong_declaration("test");
    ocf_warning wt3 = ocf_warning_wrong_construction("test");
    ocf_warning wt4 = ocf_warning_bad_input("test");
    ocf_warning wt5 = ocf_warning_undefined_behavior("test");
    ocf_warning wt6 = ocf_warning_invalid_argument("test");
    OCF_TEST_ASSERT(wt1.name != NULL && strlen(wt1.name) > 0);  // all names set
    OCF_TEST_ASSERT(wt2.name != NULL && strlen(wt2.name) > 0);
    OCF_TEST_ASSERT(wt3.name != NULL && strlen(wt3.name) > 0);
    OCF_TEST_ASSERT(wt4.name != NULL && strlen(wt4.name) > 0);
    OCF_TEST_ASSERT(wt5.name != NULL && strlen(wt5.name) > 0);
    OCF_TEST_ASSERT(wt6.name != NULL && strlen(wt6.name) > 0);
    
    // Test 12: All warnings properly initialized
    OCF_TEST_EQU(wt1.number < wt2.number, true);            // numbers incrementing
    OCF_TEST_EQU(wt2.number < wt3.number, true);
    OCF_TEST_EQU(wt3.number < wt4.number, true);
    OCF_TEST_EQU(wt4.number < wt5.number, true);
    OCF_TEST_EQU(wt5.number < wt6.number, true);

OCF_TEST_EXIT(true)