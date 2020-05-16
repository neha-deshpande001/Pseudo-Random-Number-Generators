// File: homemade_generator.cpp

#include "homemade_generator.h"
#include <math.h>

homemade_generator::homemade_generator(int seed){
    this->seed = seed;
    current = seed;
}

int homemade_generator::numDigits(int num) const{
    int digits = 1;
    while(num > 9){
        num/=10;
        digits++;
    }
    return digits;
}

int homemade_generator::get_seed() const{
    return seed;
}

void homemade_generator::set_seed(int seed){
    this->seed = seed;
}

