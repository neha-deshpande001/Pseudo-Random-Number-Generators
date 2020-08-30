// File: homemade_generator.h
#ifndef HGEN_H
#define HGEN_H

#include <math.h>
#include <iostream>

class homemade_generator {
public:
    homemade_generator(int seed);

    int numDigits(int num) const;
    int get_seed() const;

    void set_seed(int seed);
    virtual int random_number() = 0; // virtual function needs to be implemented in all subclasses

    int seed;
    int current;

};

#endif