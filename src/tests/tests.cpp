/**
 * @file tests.cpp
 * @author Jakub Skunda (xskund02)
 * @brief Tests for math library
 * @version 0.1
 * @date 2022-04-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../mathlib/mathlib.cpp"
#include "gtest/gtest.h"

class Math_test : public ::testing::Test{
    protected:
        Calculator math;
};

TEST_F(Math_test, badInput){
    EXPECT_ANY_THROW(math.processInput("2*"));
    EXPECT_ANY_THROW(math.processInput("2+"));
    EXPECT_ANY_THROW(math.processInput("2-"));
    EXPECT_ANY_THROW(math.processInput("2/"));

    EXPECT_ANY_THROW(math.processInput("*2"));
    EXPECT_ANY_THROW(math.processInput("+2"));
    EXPECT_ANY_THROW(math.processInput("-2"));
    EXPECT_ANY_THROW(math.processInput("/2"));

    EXPECT_ANY_THROW(math.processInput("(2*"));
    EXPECT_ANY_THROW(math.processInput("(2"));
    EXPECT_ANY_THROW(math.processInput("2)"));
    EXPECT_ANY_THROW(math.processInput("2*)"));
    EXPECT_ANY_THROW(math.processInput("2+)"));
    EXPECT_ANY_THROW(math.processInput("2/)"));

    EXPECT_ANY_THROW(math.processInput("("));
    EXPECT_ANY_THROW(math.processInput(")2"));
    EXPECT_ANY_THROW(math.processInput("*"));
    EXPECT_ANY_THROW(math.processInput("+"));
    EXPECT_ANY_THROW(math.processInput("-"));
    EXPECT_ANY_THROW(math.processInput("/"));

    EXPECT_ANY_THROW(math.processInput("2+-2"))
    EXPECT_ANY_THROW(math.processInput("2*/2"))
}


TEST_F(Math_test, plus){

    // integer tests
    EXPECT_EQ(math.processInput("1+1"), 2);
    EXPECT_EQ(math.processInput("0+0"), 0);
    EXPECT_EQ(math.processInput("1000+1000"), 2000);
    EXPECT_EQ(math.processInput("1+1+1"), 3);
    EXPECT_EQ(math.processInput("76+24"), 100);
    EXPECT_EQ(math.processInput("1000000+1000000"), 2000000);
    EXPECT_EQ(math.processInput("1000000+1000000+1000000"), 3000000);
    EXPECT_EQ(math.processInput("-1+1"), 0);
    EXPECT_EQ(math.processInput("-11+111"), 100);
    EXPECT_EQ(math.processInput("-11+0"), -11);

    // float
    EXPECT_EQ(math.processInput("1+0.1"), 1.1);
    EXPECT_EQ(math.processInput("0.5+0.5"), 1);
    EXPECT_EQ(math.processInput("0.32+0.001"), 0.321);
    EXPECT_EQ(math.processInput("0.76+0.24"), 1);
    EXPECT_EQ(math.processInput("1000000.111+1000000.111"), 2000000.222);
    
    // not equal
    EXPECT_NE(math.processInput("0+0.000001"), 0);
}

TEST_F(Math_test, minus){

    // integer
    EXPECT_EQ(math.processInput("1-1"), 0);
    EXPECT_EQ(math.processInput("0-0"), 0);
    EXPECT_EQ(math.processInput("1-2"), -1);
    EXPECT_EQ(math.processInput("1-1-1"), -1);
    EXPECT_EQ(math.processInput("76-26"), 50);
    EXPECT_EQ(math.processInput("1000000-1000000"), 0);
    EXPECT_EQ(math.processInput("1000000-1000000-1000000"), -1000000);

    // float
    EXPECT_EQ(math.processInput("1-0.1"), 0.9);
    EXPECT_EQ(math.processInput("0.5-0.5"), 0);
    EXPECT_EQ(math.processInput("0.32-0.001"), 0.319);
    EXPECT_EQ(math.processInput("0.76-0.26"), 0.5);
    EXPECT_EQ(math.processInput("1000000.111-1000000.111"), 0);
    
    // not equal
    EXPECT_NE(math.processInput("0-0.000001"), 0);
}

TEST_F(Math_test, multiplication){
    
    // integer tests
    EXPECT_EQ(math.processInput("1*1"), 1);
    EXPECT_EQ(math.processInput("1*0"), 0);
    EXPECT_EQ(math.processInput("1000*1000"), 1000000);
    EXPECT_EQ(math.processInput("0*0"), 0);
    EXPECT_EQ(math.processInput("1*1*2"), 2);
    EXPECT_EQ(math.processInput("2*2*2"), 8);
    EXPECT_EQ(math.processInput("1*1*2*4*8*0"), 0);
    EXPECT_EQ(math.processInput("0*1*2*4*8*10"), 0);

    // float
    EXPECT_EQ(math.processInput("1.5*2"), 3);
    EXPECT_EQ(math.processInput("1.1*1"), 1.1);
    EXPECT_EQ(math.processInput("10001.56*0"), 0);
    EXPECT_EQ(math.processInput("0.5*0.5"), 0.25);
    EXPECT_EQ(math.processInput("1*0.99"), 0.99);

}

TEST_F(Math_test, divission){

    // integer tests
    EXPECT_EQ(math.processInput("1/1"), 1);
    EXPECT_EQ(math.processInput("1/2"), 0.5);
    EXPECT_EQ(math.processInput("2/2/2"), 0.5);
    EXPECT_EQ(math.processInput("48/12"), 4);
    EXPECT_EQ(math.processInput("1000000/1000000"), 1);
    EXPECT_EQ(math.processInput("2000000/2000000/2"), 0.5);

    // float
    EXPECT_EQ(math.processInput("1/0.1"), 10);
    EXPECT_EQ(math.processInput("1.1/1.1"), 1);
    EXPECT_EQ(math.processInput("0.32/2"), 0.16);
    EXPECT_EQ(math.processInput("0.76/4"), 0.19);
    EXPECT_EQ(math.processInput("1000000.111/1000000.111"), 1);
    
    // zero division
    EXPECT_ANY_THROW(math.processInput("1/0"));
}

TEST_F(Math_test, brackets){
    EXPECT_EQ(math.processInput("(4+3)"), 7);
    EXPECT_EQ(math.processInput("(4)"), 4);
    EXPECT_EQ(math.processInput("((1+1)-3)"), -1);
    EXPECT_EQ(math.processInput("((((1))))"), 1);
    EXPECT_EQ(math.processInput("((1+1)-3)+1"), 0);
    EXPECT_EQ(math.processInput("(+4)"), 4);
}

TEST_F(Math_test, factorial){

    // throws
    EXPECT_ANY_THROW(math.processInput("21!"));
    EXPECT_ANY_THROW(math.processInput("1000000!"));
    EXPECT_ANY_THROW(math.processInput("0.3!"));

    // valid
    EXPECT_EQ(math.processInput("0!"), 1);
    EXPECT_EQ(math.processInput("5!"), 120);
    EXPECT_EQ(math.processInput("3!"), 6);
    EXPECT_EQ(math.processInput("3!!"), 720);
}

TEST_F(Math_test, exponent){
    
    EXPECT_EQ(math.processInput("2^2"), 4);
    EXPECT_EQ(math.processInput("2^0"), 1);
    EXPECT_EQ(math.processInput("2^4"), 16);
    EXPECT_EQ(math.processInput("20^2"), 400);
    EXPECT_EQ(math.processInput("-2^3"), -8);
    EXPECT_EQ(math.processInput("2.5^2"), 6.25);
    EXPECT_EQ(math.processInput("2^(-2)"), 0.25);
    EXPECT_EQ(math.processInput("2^-2"), 0.25);
}

TEST_F(Math_test, Root) {
    // equal
    ASSERT_EQ(math.processInput("2_4"), 2);
    EXPECT_EQ(math.processInput("2_0"), 0);
    EXPECT_EQ(math.processInput("2_9"), 3);
    EXPECT_EQ(math.processInput("3_27"), 3);
    EXPECT_EQ(math.processInput("3_-8"), -2);
    EXPECT_EQ(math.processInput("2_1000000"), 1000);

    // not equal
    ASSERT_NE(math.processInput("2_16"), 8);
    EXPECT_NE(math.processInput("2_9"), 4.5);
    EXPECT_NE(math.processInput("3_-8"), 2);

    // false
    EXPECT_ANY_THROW(math.processInput("-3_8"));
    EXPECT_ANY_THROW(math.processInput("2_-1"));
    EXPECT_ANY_THROW(math.processInput("4_-1"));
}

TEST_F(Math_test, mixed){
    
    EXPECT_EQ(math.processInput("2+2*2"), 6);
    EXPECT_EQ(math.processInput("2^0+1"), 2);
    EXPECT_EQ(math.processInput("(9/3!)-8*76+3"), -603.5);
    EXPECT_ANY_THROW(math.processInput("(9/-3!)-8*76+3"));
    EXPECT_EQ(math.processInput("589365-(4!*3!/9*9+3^2)"), 589212);
}

TEST_F(Math_test, numbersOnly) {
    EXPECT_EQ(math.processInput("0"), 0);
    EXPECT_EQ(math.processInput("0.2"), 0.2);
    EXPECT_EQ(math.processInput("1"), 1);
    EXPECT_EQ(math.processInput("-1"), -1);
}

TEST_F(Math_test, precedence) {
    EXPECT_EQ(math.processInput("10+3*7"), 31);
    EXPECT_EQ(math.processInput("3*7+10"), 31);
    EXPECT_EQ(math.processInput("2*5/2"), 5);
    EXPECT_EQ(math.processInput("9-3^2"), 0);
    EXPECT_EQ(math.processInput("12+3!-17"), 1);
    EXPECT_EQ(math.processInput("7/3*3"), 7);
}

TEST_F(Math_test, plusMore) {
    EXPECT_EQ(math.processInput("1+0"), 1);
    EXPECT_EQ(math.processInput("2+3"), 5);
    EXPECT_EQ(math.processInput("-3+-2"), -5);
    EXPECT_EQ(math.processInput("125000+250000"), 375000);
    EXPECT_EQ(math.processInput("125.32+3.31"), 128.63);
}

TEST_F(Math_test, minusMore) {
    EXPECT_EQ(math.processInput("1-0"), 1);
    EXPECT_EQ(math.processInput("2-3"), -1);
    EXPECT_EQ(math.processInput("-3-2"), -5);
    EXPECT_EQ(math.processInput("125000-250000"), -125000);
    EXPECT_EQ(math.processInput("125.32-3.32"), 122);
}

TEST_F(Math_test, multiplicationMore) {
    EXPECT_EQ(math.processInput("1*0"), 0);
    EXPECT_EQ(math.processInput("2*3"), 6);
    EXPECT_EQ(math.processInput("-3*2"), -6);
    EXPECT_EQ(math.processInput("125000*2"), 250000);
    EXPECT_EQ(math.processInput("125*3"), 375);
}

TEST_F(Math_test, divisionMore) {
    EXPECT_ANY_THROW(math.processInput("1/0"));
    EXPECT_EQ(math.processInput("4/2"), 2);
    EXPECT_EQ(math.processInput("-3/2"), -1.5);
    EXPECT_EQ(math.processInput("125000/250000"), 0.5);
    EXPECT_EQ(math.processInput("125/5"), 25);
}

TEST_F(Math_test, exponentMore) {
    EXPECT_EQ(math.processInput("3^2"), 9);
    EXPECT_EQ(math.processInput("-3^2"), 9);
    EXPECT_EQ(math.processInput("0^12"), 0);
    EXPECT_EQ(math.processInput("-3.6^2"), 12.96);
    EXPECT_EQ(math.processInput("1234^0"), 1);
}

TEST_F(Math_test, factorialMore) { 
    EXPECT_EQ(math.processInput("9!"), 362880);
    EXPECT_EQ(math.processInput("10!"), 3628800);
    EXPECT_EQ(math.processInput("0!"), 1);
}

TEST_F(Math_test, floatingDecimalPoint) {
    EXPECT_EQ(math.processInput("1.00000"), 1);
    EXPECT_EQ(math.processInput("1.455120000"), 1.45512);
    EXPECT_EQ(math.processInput("-31.234000"), -31.234);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}