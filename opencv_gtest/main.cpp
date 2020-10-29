#include <gtest/gtest.h>

//#include <opencv2/core.hpp>

TEST(TestTest, EmptyTest) {
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

