// File: neha_generator.cpp

#include "neha_generator.h"
#include <math.h>

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
	current*=9;
	random_number/=10;
	random_number%=10; // take middle of the three digits

	return random_number;

}
