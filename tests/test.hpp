#pragma once

#include "test_helper.hpp"

#define ASSERT(expression) \
    if (!(expression))     \
        test_failed(__FILE__, __LINE__);

#define ASSERT_FALSE(expression) \
    if (expression)              \
        test_failed(__FILE__, __LINE__);
