#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <optional>
#include <sstream>
#include <string>

inline bool g_tests_success = true;
inline std::optional<std::string> g_test_case = std::nullopt;
inline std::optional<std::string> g_test_section = std::nullopt;

inline void test_case(const std::string& name)
{
    g_test_case = name;
}

inline void test_section(const std::string& name)
{
    g_test_section = name;
}

inline void test_failed(const char* file, const int line)
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

#define END_TESTS                               \
    {                                           \
        if (g_tests_success) {                  \
            std::cout << "All tests passed!\n"; \
            return EXIT_SUCCESS;                \
        }                                       \
        return EXIT_FAILURE;                    \
    }

#define ASSERT(expression) \
    if (!(expression))     \
        test_failed(__FILE__, __LINE__);

#define ASSERT_FALSE(expression) \
    if (expression)              \
        test_failed(__FILE__, __LINE__);

#endif