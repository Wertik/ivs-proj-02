/**
 * @file mathlib2.h
 * @author Jakub Skunda (xskund02)
 * @brief Implementation of math library and PSA analysis
 * @version 0.1
 * @date 2022-04-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MATHLIB_H
#define MATHLIB_H



#include <iostream>
#include <stdio.h>
#include <string>
#include <stack>
#include <list>
#include <cmath>
using namespace std;
 
/** \relates
 * @brief Class for Stack and List
 * @param type type of element in stack or list
 * @param value value of element
 */
class StackElement{
    public:
        string type;
        double value;
};

enum ErrorCode{
    ZERO_DIVISION,
    NEGATIVE_FACTORIAL,
    TOO_LARGE_FACTORIAL,
    NO_INTEGER_FACTORIAL,
    NO_INTEGER_ROOT,
    ROOT_NR_LESS_THAN_1,
    ROOT_EVEN_NR_NEGATIVE,
    PSA_ERROR,
    WRONG_INPUT,
};

// functions for PSA

/** \relates Calculator
 * @brief Function that selects state from PSA table
 * 
 * @param myList 
 * @return double 
 */
double precedenceAnalysis(list<StackElement> myList);


/** \relates Calculator
 * @brief Returns type of top terminal from stack
 * @param myStack 
 * @return int 
 */
int stackTop(stack<StackElement> myStack);


/** \relates Calculator
 * @brief Returns type of incoming symbol
 * @param myList 
 * @return int 
 */
int incomingType(list<StackElement> myList);

 
/** \relates Calculator
 * @brief Function that reduces terminal to non-term or group of non-terms to non-term
 * 
 * @param myStack 
 * @return stack<StackElement> 
 */
stack<StackElement> reduceByRule(stack<StackElement> myStack);


// my math operations

/** \relates Calculator
 * @brief implementation of addition
 * 
 * @param nr1 first number
 * @param nr2 second number
 * @return sum of nr1 and nr2
 */
double myPlus(double nr1, double nr2);


/** \relates Calculator
 * @brief implementation of subtraction
 * 
 * @param nr1 first number
 * @param nr2 second number
 * @return subtraction of nr1 and nr2
 */
double myMinus(double nr1, double nr2);


/** \relates Calculator
 * @brief implementation of multiplication
 * 
 * @param nr1 first number
 * @param nr2 second number
 * @return mupltiplication of nr1 and nr2
 */
double myMultiplication(double nr1, double nr2);


/** \relates 
 * @brief implementation of division
 * 
 * @param nr1 first number
 * @param nr2 second number
 * @return division of nr1 and nr2
 * @throw Zero division 
 */
double myDivision(double nr1, double nr2);


/** \relates Calculator
 * @brief implementation of factorial
 * 
 * @param nr 
 * @return factorial of nr
 * @throw invalid argument nr is greater that 20
 * @throw invalid argument nr is less than 0
 */
double myFactiorial(double nr);


/** \relates Calculator
 * @brief implementation of exponent function 
 * 
 * @param nr1 base of exponent
 * @param nr2 exponent
 * @return 
 */
double myExponent(double nr1, double nr2);


/** \relates Calculator
 * @brief implementation of root function
 * 
 * @param nr1 Degree of the root
 * @param nr2 number from which root is calculated
 * @return double 
 */
double myRoot(double nr1, double nr2);


class Calculator{

public:

    /**
    * @brief Function that process expression on input
    * @param expression expression to process
    */
    double processInput(string expression);

};

#endif // MATHLIB_H
