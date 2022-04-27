#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "../mathlib/mathlib.h"


Calculator calc;

int main()
{
    double number, count = 0, sum = 0, x = 0, sumExp2 = 0, s = 0;
    char whiteSpace;

    if (isatty(0)){

        printf("Input was not redirected.\n");
        return -1;
    }

    else{

        while(scanf("%lf%c", &number, &whiteSpace)!=EOF){

            sum = calc.processInput(to_string(sum)+'+'+to_string(number));
            sumExp2 = calc.processInput(to_string(sumExp2)+'+'+to_string(number)+"^2");
            count++;
        }

        if(count != 0){
            x = calc.processInput(to_string(sum)+'/'+to_string(count));
        }

        x = calc.processInput(to_string(x)+"^2");
        x = calc.processInput(to_string(x)+"*"+to_string(count));
        
        s = calc.processInput(to_string(sumExp2)+"/("+to_string(count-1)+')');
        s = calc.processInput("2_"+to_string(s));
    }

    cout << s << "\n";
    
    return 0;
}