#include "tests/test_help.h"

#include <stdio.h>

void run_tests(const TestInfo tests[]) {
    const TestInfo *test = &tests[0];
    while(test->description && test->test_function) {
        printf("Running test: %s\n", test->description);
        test->test_function();
        printf("Done\n");
        ++test;
    }
}

