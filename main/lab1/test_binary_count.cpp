#include "gtest/gtest.h"
#include "utils.h"

TEST(BinaryCountTests, TestRange1) {
    EXPECT_EQ(utils::countDigit1OfBinaryNumbersInRange(1, 5), 7); // 1, 10, 11, 100, 101 → 1 + 1 + 2 + 1 + 2 = 7
}

TEST(BinaryCountTests, TestRange2) {
    EXPECT_EQ(utils::countDigit1OfBinaryNumbersInRange(0, 0), 0); // 0 → 0 единиц
}

TEST(BinaryCountTests, TestRange3) {
    EXPECT_EQ(utils::countDigit1OfBinaryNumbersInRange(10, 15), 17); // 10, 11, 12, 13, 14, 15 → 2 + 3 + 2 + 3 + 3 + 4 = 17
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    std::cout << "Type range. From A to B:" << std::endl;
    int a, b;
    
    std::cin >> a >> b;

    int result_number = utils::countDigit1OfBinaryNumbersInRange(a, b);

    std::cout << "Result is: " << result_number << std::endl;

    return 0;
}
