#include "test.hpp"

#include <iostream>
#include <optional>
#include <sstream>

static bool g_tests_success = true;
static std::optional<std::string> g_test_case = std::nullopt;
static std::optional<std::string> g_test_section = std::nullopt;

void test_case(const std::string& name)
{
    g_test_case = name;
}

void test_section(const std::string& name)
{
    g_test_section = name;
}

void test_failed(const char* file, const int line)
{
    g_tests_success = false;
    std::stringstream ss;
    ss << file << ":" << line << " TEST_FAILED";
    if (g_test_case.has_value()) {
        ss << " [" << g_test_case.value() << "]";
    }
    if (g_test_section.has_value()) {
        ss << " [" << g_test_section.value() << "]";
    }
    std::cerr << ss.str() << std::endl;
}

int end_tests()
{
    if (g_tests_success) {
        std::cout << "All tests passed!\n";
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}