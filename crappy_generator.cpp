// File: crappy_generator.cpp

#include "crappy_generator.h"
#include <math.h>

// CONSTRUCTOR
crappy_generator::crappy_generator(int seed){
	this->seed = seed;
	current = seed;
}

// ACCESSORS
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

int crappy_generator::get_seed() const{
	return seed;
}

// MODIFIERS
void crappy_generator::set_seed(int seed){
	this->seed = seed;
}

// OTHER
int crappy_generator::numDigits(int num) const{
	int digits = 1;
	while(num > 9){
		num/=10;
		digits++;
	}
	return digits;
}
