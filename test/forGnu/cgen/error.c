#define OPENCF_FOR_GNU
#include "cfrost.h"
#include "cfrost/cgen/error.h"

OCF_TEST_MAIN(cgen: error);

    // Test 1: error_init() - Initialize error with default values
    ocf_error err1 = ocf_error_init();
    OCF_TEST_EQU(err1.name == NULL, true); // name should be NULL
    OCF_TEST_EQU(err1.description == NULL, true); // description should be NULL
    OCF_TEST_EQU(err1.file == NULL, true); // file should be NULL
    OCF_TEST_EQU(err1.time == NULL, true); // time should be NULL
    OCF_TEST_EQU(err1.line, 0); // line should be 0
    
    // Test 2: error_indexing() - Create wrong indexing error
    ocf_error err_index = ocf_error_indexing("Array out of bounds");
    OCF_TEST_EQU(err_index.name != NULL, true); // name should not be NULL
    OCF_TEST_EQU(strcmp(err_index.name, "Wrong Indexing"), 0); // name should be "Wrong Indexing"
    OCF_TEST_EQU(err_index.description != NULL, true); // description should not be NULL
    OCF_TEST_EQU(strcmp(err_index.description, "Array out of bounds"), 0); // verify description
    OCF_TEST_EQU(err_index.file != NULL, true); // file should be set
    OCF_TEST_EQU(err_index.time != NULL, true); // time should be set
    OCF_TEST_ASSERT(err_index.line > 0); // line should be set (> 0)
    
    // Test 3: error_declaration() - Create wrong declaration error
    ocf_error err_decl = ocf_error_declaration("Invalid variable type");
    OCF_TEST_EQU(err_decl.name != NULL, true); // name should not be NULL
    OCF_TEST_EQU(strcmp(err_decl.name, "Wrong declaration"), 0); // verify name
    OCF_TEST_EQU(err_decl.description != NULL, true); // description should not be NULL
    OCF_TEST_EQU(strcmp(err_decl.description, "Invalid variable type"), 0); // verify description
    
    // Test 4: error_construction() - Create wrong construction error
    ocf_error err_cons = ocf_error_construction("Struct member missing");
    OCF_TEST_EQU(err_cons.name != NULL, true); // name should not be NULL
    OCF_TEST_EQU(strcmp(err_cons.name, "Wrong Construction"), 0); // verify name
    OCF_TEST_EQU(err_cons.description != NULL, true); // description should not be NULL
    
    // Test 5: error_bad_input() - Create bad input error
    ocf_error err_input = ocf_error_bad_input("Invalid parameter value");
    OCF_TEST_EQU(err_input.name != NULL, true); // name should not be NULL
    OCF_TEST_EQU(strcmp(err_input.name, "Bad Input"), 0); // verify name
    OCF_TEST_EQU(err_input.description != NULL, true); // description should not be NULL
    
    // Test 6: error_undefined_behavior() - Create undefined behavior error
    ocf_error err_undef = ocf_error_undefined_behavior("NULL pointer dereference");
    OCF_TEST_EQU(err_undef.name != NULL, true); // name should not be NULL
    OCF_TEST_EQU(strcmp(err_undef.name, "Undefined Behavior"), 0); // verify name
    OCF_TEST_EQU(err_undef.description != NULL, true); // description should not be NULL
    
    // Test 7: error_invalid_argument() - Create invalid argument error
    ocf_error err_arg = ocf_error_invalid_argument("Argument count mismatch");
    OCF_TEST_EQU(err_arg.name != NULL, true); // name should not be NULL
    OCF_TEST_EQU(strcmp(err_arg.name, "Invalid Argument"), 0); // verify name
    OCF_TEST_EQU(err_arg.description != NULL, true); // description should not be NULL
    
    // Test 8: Multiple errors with different descriptions
    ocf_error err_multi1 = ocf_error_indexing("First error");
    ocf_error err_multi2 = ocf_error_indexing("Second error");
    OCF_TEST_EQU(strcmp(err_multi1.description, "First error"), 0);   // verify first
    OCF_TEST_EQU(strcmp(err_multi2.description, "Second error"), 0);  // verify second
    OCF_TEST_EQU(strcmp(err_multi1.name, err_multi2.name), 0);         // both have same name
    
    // Test 9: Error with empty string description
    ocf_error err_empty = ocf_error_bad_input("");
    OCF_TEST_EQU(err_empty.name != NULL, true);             // name should not be NULL
    OCF_TEST_EQU(err_empty.description != NULL, true);      // description initialized (empty string)
    OCF_TEST_EQU(strlen(err_empty.description), 0);         // should be empty
    
    // Test 10: All error creators preserve name correctly
    ocf_error e1 = ocf_error_indexing("test");
    ocf_error e2 = ocf_error_declaration("test");
    ocf_error e3 = ocf_error_construction("test");
    ocf_error e4 = ocf_error_bad_input("test");
    ocf_error e5 = ocf_error_undefined_behavior("test");
    ocf_error e6 = ocf_error_invalid_argument("test");
    OCF_TEST_ASSERT(e1.name != NULL && strlen(e1.name) > 0); // all names set
    OCF_TEST_ASSERT(e2.name != NULL && strlen(e2.name) > 0);
    OCF_TEST_ASSERT(e3.name != NULL && strlen(e3.name) > 0);
    OCF_TEST_ASSERT(e4.name != NULL && strlen(e4.name) > 0);
    OCF_TEST_ASSERT(e5.name != NULL && strlen(e5.name) > 0);
    OCF_TEST_ASSERT(e6.name != NULL && strlen(e6.name) > 0);

OCF_TEST_EXIT(true)