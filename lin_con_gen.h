// File: lin_con_gen.h
#ifndef LCGEN_H
#define LCGEN_H


class lin_con_gen{
public:
    // default value for parameters is 1
    lin_con_gen(int seed = 1, long a = 1, long c = 1, long m = 1); // constructor
    long random_number(); 

    int seed;
    long current;
    long a = 1;
    long c = 1;
    long m = 1;
};
#endif
