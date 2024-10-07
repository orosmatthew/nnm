#define NNM_BOUNDS_CHECK
#include <nnm/nnm.hpp>

#include "geom_tests.hpp"
#include "nnm_tests.hpp"

#include "test.hpp"

int main()
{
    nnm_tests();
    geom_tests();
    END_TESTS
}
