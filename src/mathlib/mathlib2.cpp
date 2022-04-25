#include "mathlib2.h"

double myPlus(double nr1, double nr2){
    return nr1 + nr2;
}

double myMinus(double nr1, double nr2){
    return nr1 - nr2;
}

double myMultiplication(double nr1, double nr2){
    return nr1 * nr2;
}

double myDivision(double nr1, double nr2){
    if (nr2 == 0){
        throw(std::invalid_argument("zero divission"));
    }

    return nr1 / nr2;
}

double myFactiorial(double nr){
    
    if(nr < 0){ 
        throw(std::invalid_argument("number must be possitive"));
    }

    if(nr > 20) {
        throw(std::invalid_argument("number is too large"));
    }

    long int result = nr;
    for (size_t i = nr - 1  ; i > 1; i--) {
        result = result * i;
    }

    return result;
}

double myExponent(double nr1, double nr2){
    double result = nr1;

    if (nr2 == 0) {
        return 1; 
    }

    for (size_t i = 0; i < nr2-1; i++)
    {
        result = result * nr1;
    }
    return result;
}

double Calculator::processInput(string vyraz){
    int state = 0;
    string variable;
    list<StackElement> myList;
    for (size_t i = 0; i < vyraz.length() + 1; i++)
    {

        switch (state)
        {

            case DEFAULT:
                if(vyraz[i] >= '0' && vyraz[i] <= '9'){
                    variable = vyraz[i];
                    state = NUMBER;
                }
                
                else if(vyraz[i] == '('){
                    StackElement *el = new StackElement;
                    el->type = "lbracket";
                    myList.push_back(*el);
                    state = DEFAULT;
                }

                else if(vyraz[i] == ')'){
                    StackElement *el = new StackElement;
                    el->type = "rbracket";
                    myList.push_back(*el);
                    state = DEFAULT;
                }

                else if(vyraz[i] == '+'){
                    StackElement *el = new StackElement;
                    el->type = "plus";
                    myList.push_back(*el);
                    state = DEFAULT;
                }

                else if(vyraz[i] == '-'){
                    StackElement *el = new StackElement;
                    el->type = "minus";
                    myList.push_back(*el);
                    state = DEFAULT;
                }

                else if(vyraz[i] == '*'){
                    StackElement *el = new StackElement;
                    el->type = "multiplication";
                    myList.push_back(*el);
                    state = DEFAULT;
                }

                else if(vyraz[i] == '/'){
                    StackElement *el = new StackElement;
                    el->type = "division";
                    myList.push_back(*el);
                    state = DEFAULT;
                }

                else if(vyraz[i] == '^'){
                    StackElement *el = new StackElement;
                    el->type = "exponent";
                    myList.push_back(*el);
                    state = DEFAULT;
                }

                else if(vyraz[i] == '!'){
                    StackElement *el = new StackElement;
                    el->type = "factorial";
                    myList.push_back(*el);
                    state = DEFAULT;
                }

                else if(vyraz[i] == ' ' || vyraz[i] == '\0'){
                    state = DEFAULT;
                }

                break;

            case NUMBER:
                if((vyraz[i] >= '0' && vyraz[i] <= '9') || vyraz[i] == '.'){
                    variable = variable + vyraz[i];
                    state = NUMBER;
                }
                else{
                    StackElement *nr = new StackElement;
                    nr->type = "number";
                    nr->value = std::stod(variable);
                    myList.push_back(*nr);

                    if(vyraz[i] == '+'){
                        StackElement *op = new StackElement;
                        op->type = "plus";
                        myList.push_back(*op);
                        state = DEFAULT;
                    }

                    else if(vyraz[i] == '-'){
                        StackElement *op = new StackElement;
                        op->type = "minus";
                        myList.push_back(*op);
                        state = DEFAULT;
                    }

                    else if(vyraz[i] == '*'){
                        StackElement *op = new StackElement;
                        op->type = "multiplication";
                        myList.push_back(*op);
                        state = DEFAULT;
                    }

                    else if(vyraz[i] == '/'){
                        StackElement *op = new StackElement;
                        op->type = "division";
                        myList.push_back(*op);
                        state = DEFAULT;
                    }

                    else if(vyraz[i] == '^'){
                        StackElement *op = new StackElement;
                        op->type = "exponent";
                        myList.push_back(*op);
                        state = DEFAULT;
                    }

                    else if(vyraz[i] == '!'){
                        StackElement *op = new StackElement;
                        op->type = "factorial";
                        myList.push_back(*op);
                        state = DEFAULT;
                    }

                    else if(vyraz[i] == '('){
                        StackElement *op = new StackElement;
                        op->type = "lbracket";
                        myList.push_back(*op);
                        state = DEFAULT;
                    }

                    else if(vyraz[i] == ')'){
                        StackElement *op = new StackElement;
                        op->type = "rbracket";
                        myList.push_back(*op);
                        state = DEFAULT;
                    }

                    else if(vyraz[i] == '\0' || vyraz[i] == ' '){
                        state = DEFAULT;
                    }

                    else{
                        printf("CHYBA");
                        exit(0);
                    }

                    break;
                }
        }
    }
    StackElement *end = new StackElement;
    end->type = "end";
    myList.push_back(*end);

    double result = precedenceAnalysis(myList);
    return result;    
}

int stackTop(stack<StackElement> myStack){

    if(myStack.top().type == "plus" || myStack.top().type == "minus"){
        return 0;
    }
    else if(myStack.top().type == "multiplication" || myStack.top().type == "division"){ 
        return 1;
    }
    else if(myStack.top().type == "lbracket"){ 
        return 2;
    }
    else if(myStack.top().type == "rbracket"){ 
        return 3;
    }
    else if(myStack.top().type == "number"){ 
        return 4;
    }
    else if(myStack.top().type == "end"){ 
        return 5;
    }
    else if(myStack.top().type == "exponent"){ 
        return 6;
    }
    else if(myStack.top().type == "factorial"){ 
        return 7;
    }
    else if(myStack.top().type == "E-type"){
        StackElement e_type = myStack.top();
        myStack.pop();
        int ret = stackTop(myStack);
        myStack.push(e_type);
        return ret;
    }
    else{ 
        return -1;
    }
}

int incomingType(list<StackElement> myList){

    if(myList.front().type == "number"){
        return 4;
    }
    else if(myList.front().type == "plus" || myList.front().type == "minus"){
        return 0;
    }
    else if(myList.front().type == "multiplication" || myList.front().type == "division"){
        return 1;
    }
    else if(myList.front().type == "end"){
        return 5;
    }
    else if(myList.front().type == "lbracket"){
        return 2;
    }
    else if(myList.front().type == "rbracket"){
        return 3;
    }
    else if(myList.front().type == "exponent"){
        return 6;
    }
    else if(myList.front().type == "factorial"){
        return 7;
    }
    return -1;
}

stack<StackElement> reduceByRule(stack<StackElement> myStack){
    
    // rule i -> E
    if (stackTop(myStack) == 4){
        myStack.top().type = "E-type";
        // cout << myStack.top().type.c_str();
        return myStack;
    }

    else if(stackTop(myStack) == 0){
        StackElement el1 = myStack.top();
        myStack.pop();
        StackElement el2 = myStack.top();
        myStack.pop();
        StackElement el3 = myStack.top();


        double outNr;

        if (el2.type == "plus"){
            outNr = myPlus(el3.value, el1.value);    
        }

        else if(el2.type == "minus"){
            outNr = myMinus(el3.value, el1.value);
        }

        
        myStack.top().value = outNr;
        myStack.top().type = "E-type";
        return myStack;
    }

    else if(stackTop(myStack) == 1){
        StackElement el1 = myStack.top();
        myStack.pop();
        StackElement el2 = myStack.top();
        myStack.pop();
        StackElement el3 = myStack.top();

        double outNr;

        if (el2.type == "exponent"){
            outNr = myMultiplication(el3.value, el1.value);    
        }
        else if(el2.type == "division"){
            outNr = myDivision(el3.value, el1.value);
        }
        myStack.top().value = outNr;
        myStack.top().type = "E-type";
        return myStack;
    }

    else if(stackTop(myStack) == 6){
        StackElement el1 = myStack.top();
        myStack.pop();
        StackElement el2 = myStack.top();
        myStack.pop();
        StackElement el3 = myStack.top();

        double outNr;
        outNr = myExponent(el3.value, el1.value);
        
        myStack.top().value = outNr;
        myStack.top().type = "E-type";
        return myStack;
    }

    else if(stackTop(myStack) == 7){
        StackElement el1 = myStack.top();
        myStack.pop();
        StackElement el2 = myStack.top();

        double outNr;
        outNr = myFactiorial(el2.value);

        myStack.top().value = outNr;
        myStack.top().type = "E-type";
        return myStack;
    }

    return myStack;
    
}

double precedenceAnalysis(list<StackElement> myList){
    
    stack<StackElement> myStack;
    
    StackElement end;
    end.type = "end";
    myStack.push(end);

    StackElement el;
    do{
        // printf("%i %i", stackTop(myStack), incomingType(myList)); 
        switch(table[stackTop(myStack)][incomingType(myList)]){
            
            case 'L':
                // puts("L");
                el = myList.front();
                myList.pop_front();
                myStack.push(el);
                break;

            case 'R':
                // puts("R");
                // cout << myStack.top().type.c_str();
                myStack = reduceByRule(myStack);
                // cout << myStack.top().type.c_str();
                // cout << "\n------------------\n";
                break;

            case 'I':
                // puts("I");
                
                StackElement noterm = myStack.top();
                myStack.pop();
                myStack.pop();
                myStack.push(noterm);
                myList.pop_front();
                break;
                
        }
    }while(myStack.size() != 2 || myList.size() != 1);

    return myStack.top().value;
}