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

#include <iostream>
#include <stdio.h>
#include <string>
#include <stack>
#include <list>
#include <cmath>
using namespace std;

/**
 * @brief Class for Stack and List
 * @param type type of element in stack or list
 * @param value value of element
 */
class StackElement{
    public:
        string type;
        double value;
};

/**
 * @brief Table for precedence analysis
 * 
 */
int table[8][8]={

    // I       N       P       U       T
        
    //   +|- *|/  (   )   i   $   ^   !

        {'R','L','L','R','L','R','L','L'}, // + -                S
        {'R','R','L','R','L','R','L','L'}, // * / //             T
        {'L','L','L','I','L','E','L','L'}, // (                  A
        {'R','R','E','R','E','R','R','R'}, // )                  C
        {'R','R','E','R','E','R','R','R'}, // i                  K
        {'L','L','L','E','L','E','L','L'}, // $
        {'R','R','L','R','L','R','L','L'}, // ^      
        {'R','R','L','R','L','R','R','R'}  // !           
};

// functions for PSA

/**
 * @brief Function that selects state from PSA table
 * 
 * @param myList 
 * @return double 
 */
double precedenceAnalysis(list<StackElement> myList);


/**
 * @brief Returns type of top terminal from stack
 * 
 * @param myStack 
 * @return int 
 */
int stackTop(stack<StackElement> myStack);


/**
 * @brief Returns type of incoming symbol
 * 
 * @param myList 
 * @return int 
 */
int incomingType(list<StackElement> myList);


/**
 * @brief Function that reduces terminal to non-term or group of non-terms to non-term
 * 
 * @param myStack 
 * @return stack<StackElement> 
 */
stack<StackElement> reduceByRule(stack<StackElement> myStack);


// my math operations

/**
 * @brief implementation of addition
 * 
 * @param nr1 first number
 * @param nr2 second number
 * @return sum of nr1 and nr2
 */
double myPlus(double nr1, double nr2);


/**
 * @brief implementation of subtraction
 * 
 * @param nr1 first number
 * @param nr2 second number
 * @return subtraction of nr1 and nr2
 */
double myMinus(double nr1, double nr2);


/**
 * @brief implementation of multiplication
 * 
 * @param nr1 first number
 * @param nr2 second number
 * @return mupltiplication of nr1 and nr2
 */
double myMultiplication(double nr1, double nr2);


/**
 * @brief implementation of division
 * 
 * @param nr1 first number
 * @param nr2 second number
 * @return division of nr1 and nr2
 * @throw Zero division 
 */
double myDivision(double nr1, double nr2);


/**
 * @brief implementation of factorial
 * 
 * @param nr 
 * @return factorial of nr
 * @throw invalid argument nr is greater that 20
 * @throw invalid argument nr is less than 0
 */
double myFactiorial(double nr);


/**
 * @brief implementation of exponent function 
 * 
 * @param nr1 
 * @param nr2 
 * @return 
 */
double myExponent(double nr1, double nr2);


class Calculator{

public:

    double processInput(string vyraz);

};