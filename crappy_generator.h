// File: crappy_generator.h
#ifndef C_H
#define C_H

#include "homemade_generator.h"

class crappy_generator : public homemade_generator {
public:
    // default value for seed is 1
    crappy_generator(int seed = 1) : homemade_generator(seed){}; // constructor calls superclass's constructor

    int random_number(); // this is the only function that is different from the superclass

};
#endif
