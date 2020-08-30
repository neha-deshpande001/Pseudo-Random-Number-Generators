// File: neha_generator.h
#ifndef N_H
#define N_H

#include "homemade_generator.h"

class neha_generator : public homemade_generator {
public:
    // default value for seed is 1
    neha_generator(int seed = 1) : homemade_generator(seed){}; // constructor calls superclass's constructor

    int random_number(); // this is the only function that is different from the superclass

};
#endif
