#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Tests/Sum.h"

int main(int argc, char* argv[]) {
    // testing::InitGoogleTest(&argc, argv);
    // std::cout << "CAL Lab Class 01" << std::endl;

    generate_graph();
    return RUN_ALL_TESTS();;
}