#pragma once

#include <iostream>
#include <optional>
#include <string>

void test_case(const std::string& name);

const std::optional<std::string>& test_case();

void test_section(const std::string& name);

const std::optional<std::string>& test_section();

void test_failed(const char* file, int line);

bool tests_succeeded();

#define END_TESTS                               \
    {                                           \
        if (tests_succeeded()) {                \
            std::cout << "All tests passed!\n"; \
            return EXIT_SUCCESS;                \
        }                                       \
        return EXIT_FAILURE;                    \
    }

#define TEST_ASSERT(expression) \
    if (!(expression))          \
        test_failed(__FILE__, __LINE__);

#define TEST_ASSERT_FALSE(expression) \
    if (expression)                   \
        test_failed(__FILE__, __LINE__);
