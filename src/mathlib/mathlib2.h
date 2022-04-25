#include <iostream>
#include <stdio.h>
#include <string>
#include <stack>
#include <list>
using namespace std;


enum states{
    DEFAULT,
    NUMBER,
};

class StackElement{
    public:
        string type;
        double value;
};


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


double precedenceAnalysis(list<StackElement> myList);




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
 * @return double 
 */
double myExponent(double nr1, double nr2);


class Calculator{

public:

    double processInput(string vyraz);

};

