#pragma once

#include <string>

void test_case(const std::string& name);
void test_section(const std::string& name);
void test_failed(const char* file, int line);
int end_tests();

#define ASSERT(expression) \
    if (!(expression))     \
        test_failed(__FILE__, __LINE__);

#define ASSERT_FALSE(expression) \
    if (expression)              \
        test_failed(__FILE__, __LINE__);
