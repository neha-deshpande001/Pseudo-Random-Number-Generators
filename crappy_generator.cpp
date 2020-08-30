// File: crappy_generator.cpp

#include "crappy_generator.h"
#include <math.h>

//implementation of the crappy generator
// starts with the least significant digit of the seed
// adds 1 each time, if the number is greater than 9, makes the number 0
//This generator is very, VERY predictable, the numbers are not at all random.
//However, this is one of the cases where the chi-squared test shows a false positive, meaning
//it shows perfectly uniform distribution, but it is an AWFUL random number generator.

int crappy_generator::random_number(){
    while(numDigits(current) > 1){ // make current 1 digit
        current%=10;
    }

    int random_number = current;
    current++;
    if(current == 10){
        current = 0;
    }

    return random_number;
}
