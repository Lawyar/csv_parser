#include <a.h>

#include <gtest/gtest.h>

// f(x) = (x - 1) * (x - 2)^2 * (x - 3)^3
// [0.1, 1.76]
TEST(build_tests, test_stability) {
    A a;
    std::cout << a.Print() << std::endl;
}

