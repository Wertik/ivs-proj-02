#include "../mathlib/mathlib2.cpp"
#include "gtest/gtest.h"

class Math_test : public ::testing::Test{
    protected:
        Calculator math;
};

TEST_F(Math_test, Plus){

    // integer tests
    EXPECT_EQ(math.processInput("1 + 1"), 2);
    EXPECT_EQ(math.processInput("0 + 0"), 0);
    EXPECT_EQ(math.processInput("1000 + 1000"), 2000);
    EXPECT_EQ(math.processInput("1 + 1 + 1"), 3);
    EXPECT_EQ(math.processInput("76+24"), 100);
    EXPECT_EQ(math.processInput("1000000 + 1000000"), 2000000);
    EXPECT_EQ(math.processInput("1000000 + 1000000 + 1000000"), 3000000);

    // float
    EXPECT_EQ(math.processInput("1 + 0.1"), 1.1);
    EXPECT_EQ(math.processInput("0.5 + 0.5"), 1);
    EXPECT_EQ(math.processInput("0.32 + 0.001"), 0.321);
    EXPECT_EQ(math.processInput("0.76+0.24"), 1);
    EXPECT_EQ(math.processInput("1000000.111 + 1000000.111"), 2000000.222);
    
    // not equal
    EXPECT_NE(math.processInput("0 + 0.000001"), 0);
}

TEST_F(Math_test, Minus){

    // integer
    EXPECT_EQ(math.processInput("1 - 1"), 0);
    EXPECT_EQ(math.processInput("0 - 0"), 0);
    EXPECT_EQ(math.processInput("1 - 2"), -1);
    EXPECT_EQ(math.processInput("1 - 1 - 1"), -1);
    EXPECT_EQ(math.processInput("76 - 26"), 50);
    EXPECT_EQ(math.processInput("1000000 - 1000000"), 0);
    EXPECT_EQ(math.processInput("1000000 - 1000000 - 1000000"), -1000000);

    // float
    EXPECT_EQ(math.processInput("1 - 0.1"), 0.9);
    EXPECT_EQ(math.processInput("0.5 - 0.5"), 0);
    EXPECT_EQ(math.processInput("0.32 - 0.001"), 0.319);
    EXPECT_EQ(math.processInput("0.76 - 0.26"), 0.5);
    EXPECT_EQ(math.processInput("1000000.111 - 1000000.111"), 0);
    
    // not equal
    EXPECT_NE(math.processInput("0 - 0.000001"), 0);
}

TEST_F(Math_test, Divission){

    // integer tests
    EXPECT_EQ(math.processInput("1 / 1"), 1);
    EXPECT_EQ(math.processInput("1 / 2"), 0.5);
    EXPECT_EQ(math.processInput("2 / 2/ 2"), 0.5);
    EXPECT_EQ(math.processInput("48 / 12"), 4);
    EXPECT_EQ(math.processInput("1000000 / 1000000"), 1);
    EXPECT_EQ(math.processInput("2000000 / 2000000 / 2"), 0.5);

    // float
    EXPECT_EQ(math.processInput("1 / 0.1"), 10);
    EXPECT_EQ(math.processInput("1.1 / 1.1"), 1);
    EXPECT_EQ(math.processInput("0.32 / 2"), 0.16);
    EXPECT_EQ(math.processInput("0.76 / 4"), 0.19);
    EXPECT_EQ(math.processInput("1000000.111 / 1000000.111"), 1);
    
    // zero division
    EXPECT_ANY_THROW(math.processInput("1 / 0"));
}

TEST_F(Math_test, Brackets){
    EXPECT_EQ(math.processInput("(4 + 3)"), 7);
    EXPECT_EQ(math.processInput("(4)"), 4);
    EXPECT_EQ(math.processInput("((1 + 1) - 3)"), -1);
    EXPECT_EQ(math.processInput("((((1))))"), 1);
    EXPECT_EQ(math.processInput("((1 + 1) - 3) + 1"), 0);
}

TEST_F(Math_test, Factorial){
    EXPECT_ANY_THROW(math.processInput("21!"));
    EXPECT_ANY_THROW(math.processInput("1000000!"));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
