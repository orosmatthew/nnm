#define NNM_BOUNDS_CHECK
#include <nnm/nnm.hpp>

#include "geom2_tests.hpp"
#include "geom3_tests.hpp"
#include "nnm_tests.hpp"

#include "test.hpp"

// ReSharper disable once CppDFATimeOver
int main()
{
    nnm_tests();
    geom2_tests();
    geom3_tests();
    return end_tests();
}
