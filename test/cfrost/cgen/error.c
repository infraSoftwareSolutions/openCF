#include "cfrost.h"
#include "cfrost/cgen/error.h"

TEST_MAIN(cgen: error);

    // Test 1: error_init() - Initialize error with default values
    cerror err1 = error_init();
    TEST_EQU(err1.name == NULL, true); // name should be NULL
    TEST_EQU(err1.description == NULL, true); // description should be NULL
    TEST_EQU(err1.file == NULL, true); // file should be NULL
    TEST_EQU(err1.time == NULL, true); // time should be NULL
    TEST_EQU(err1.line, 0); // line should be 0
    
    // Test 2: error_indexing() - Create wrong indexing error
    cerror err_index = error_indexing("Array out of bounds");
    TEST_EQU(err_index.name != NULL, true); // name should not be NULL
    TEST_EQU(strcmp(err_index.name, "Wrong Indexing"), 0); // name should be "Wrong Indexing"
    TEST_EQU(err_index.description != NULL, true); // description should not be NULL
    TEST_EQU(strcmp(err_index.description, "Array out of bounds"), 0); // verify description
    TEST_EQU(err_index.file != NULL, true); // file should be set
    TEST_EQU(err_index.time != NULL, true); // time should be set
    TEST_ASSERT(err_index.line > 0); // line should be set (> 0)
    
    // Test 3: error_declaration() - Create wrong declaration error
    cerror err_decl = error_declaration("Invalid variable type");
    TEST_EQU(err_decl.name != NULL, true); // name should not be NULL
    TEST_EQU(strcmp(err_decl.name, "Wrong declaration"), 0); // verify name
    TEST_EQU(err_decl.description != NULL, true); // description should not be NULL
    TEST_EQU(strcmp(err_decl.description, "Invalid variable type"), 0); // verify description
    
    // Test 4: error_construction() - Create wrong construction error
    cerror err_cons = error_construction("Struct member missing");
    TEST_EQU(err_cons.name != NULL, true); // name should not be NULL
    TEST_EQU(strcmp(err_cons.name, "Wrong Construction"), 0); // verify name
    TEST_EQU(err_cons.description != NULL, true); // description should not be NULL
    
    // Test 5: error_bad_input() - Create bad input error
    cerror err_input = error_bad_input("Invalid parameter value");
    TEST_EQU(err_input.name != NULL, true); // name should not be NULL
    TEST_EQU(strcmp(err_input.name, "Bad Input"), 0); // verify name
    TEST_EQU(err_input.description != NULL, true); // description should not be NULL
    
    // Test 6: error_undefined_behavior() - Create undefined behavior error
    cerror err_undef = error_undefined_behavior("NULL pointer dereference");
    TEST_EQU(err_undef.name != NULL, true); // name should not be NULL
    TEST_EQU(strcmp(err_undef.name, "Undefined Behavior"), 0); // verify name
    TEST_EQU(err_undef.description != NULL, true); // description should not be NULL
    
    // Test 7: error_invalid_argument() - Create invalid argument error
    cerror err_arg = error_invalid_argument("Argument count mismatch");
    TEST_EQU(err_arg.name != NULL, true); // name should not be NULL
    TEST_EQU(strcmp(err_arg.name, "Invalid Argument"), 0); // verify name
    TEST_EQU(err_arg.description != NULL, true); // description should not be NULL
    
    // Test 8: Multiple errors with different descriptions
    cerror err_multi1 = error_indexing("First error");
    cerror err_multi2 = error_indexing("Second error");
    TEST_EQU(strcmp(err_multi1.description, "First error"), 0);   // verify first
    TEST_EQU(strcmp(err_multi2.description, "Second error"), 0);  // verify second
    TEST_EQU(strcmp(err_multi1.name, err_multi2.name), 0);         // both have same name
    
    // Test 9: Error with empty string description
    cerror err_empty = error_bad_input("");
    TEST_EQU(err_empty.name != NULL, true);             // name should not be NULL
    TEST_EQU(err_empty.description != NULL, true);      // description initialized (empty string)
    TEST_EQU(strlen(err_empty.description), 0);         // should be empty
    
    // Test 10: All error creators preserve name correctly
    cerror e1 = error_indexing("test");
    cerror e2 = error_declaration("test");
    cerror e3 = error_construction("test");
    cerror e4 = error_bad_input("test");
    cerror e5 = error_undefined_behavior("test");
    cerror e6 = error_invalid_argument("test");
    TEST_ASSERT(e1.name != NULL && strlen(e1.name) > 0); // all names set
    TEST_ASSERT(e2.name != NULL && strlen(e2.name) > 0);
    TEST_ASSERT(e3.name != NULL && strlen(e3.name) > 0);
    TEST_ASSERT(e4.name != NULL && strlen(e4.name) > 0);
    TEST_ASSERT(e5.name != NULL && strlen(e5.name) > 0);
    TEST_ASSERT(e6.name != NULL && strlen(e6.name) > 0);

TEST_EXIT(true)