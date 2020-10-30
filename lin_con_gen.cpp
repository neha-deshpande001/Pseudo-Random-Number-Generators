// File: lin_con_gen.cpp

#include "lin_con_gen.h"
#include <math.h>


lin_con_gen::lin_con_gen(int seed, long a, long c, long m){
    this->seed = seed;
    current = seed;
    this->a = a;
    this->c = c;
    this->m = m;
}

long lin_con_gen::random_number(){
	current = (a * current + c) % m;
	if(current > 9){ //take the middle digit
		current /= 10;
		current %= 10;
	}
	return current;
}
