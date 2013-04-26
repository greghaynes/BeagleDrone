#ifndef TEST_HELP_H
#define TEST_HELP_H

typedef struct TestInfo {
    const char *description;
    void (*test_function)(void);
} TestInfo;

void run_tests(const TestInfo tests[]);

#endif
