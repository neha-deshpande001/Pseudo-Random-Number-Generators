// File: neha_generator.cpp

#include "neha_generator.h"
#include <math.h>

// CONSTRUCTOR
neha_generator::neha_generator(int seed){
	this->seed = seed;
	current = seed;
}

// ACCESSORS
int neha_generator::random_number(){
	if(current == 0){
		current += 1;
	}
	if(numDigits(current) % 2 == 0){ // even length
		current/=10;
	}
	while(numDigits(current) < 3){
		current*=9;
	}
	while(numDigits(current) > 3){ // make current 3 digits
		current/=10;
		current%=(int)pow(10,numDigits(current)-1);
	}

	int random_number = current;
	current = current * 9;
	random_number/=10;
	random_number%=10;

	return random_number;

}

int neha_generator::get_seed() const{
	return seed;
}

// MODIFIERS
void neha_generator::set_seed(int seed){
	this->seed = seed;
}

// OTHER
int neha_generator::numDigits(int num) const{
	int digits = 1;
	while(num > 9){
		num/=10;
		digits++;
	}
	return digits;
}
