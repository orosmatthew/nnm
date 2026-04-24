#include "test_helper.hpp"

#include <iostream>
#include <optional>
#include <string>

bool g_tests_success = true;
std::optional<std::string> g_test_case = std::nullopt;
std::optional<std::string> g_test_section = std::nullopt;

void test_case(const std::string& name)
{
    g_test_case = name;
    g_test_section = std::nullopt;
}

const std::optional<std::string>& test_case()
{
    return g_test_case;
}

void test_section(const std::string& name)
{
    g_test_section = name;
}

const std::optional<std::string>& test_section()
{
    return g_test_section;
}

void test_failed(const char* file, const int line)
{
    g_tests_success = false;
    std::cerr << file << ":" << line << " TEST_FAILED";
    if (g_test_case.has_value()) {
        std::cerr << " [" << g_test_case.value() << "]";
    }
    if (g_test_section.has_value()) {
        std::cerr << " [" << g_test_section.value() << "]";
    }
    std::cerr << std::endl;
}

bool tests_succeeded()
{
    return g_tests_success;
}