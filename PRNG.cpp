#define _USE_MATH_DEFINES


#include "matplotlibcpp.h" // graphing
#include "homemade_generator.h" // homemade generators
#include "neha_generator.h"
#include "crappy_generator.h"
#include "lin_con_gen.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <random> // C++ generators
#include <map>
#include <unordered_map>

using namespace std;
namespace plt = matplotlibcpp;

/*
compile:
g++ *.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7

run:
./a.out [numTests] [type] [seed]
*/

// this function calculates the chi squared value for a given vector of data points.
double calculate_chi_squared(vector<int> observed, double expected){
	double sum = 0;
	for(int i = 0; i < 10; i++){
		sum+=(((double)observed[i] - expected) * ((double)observed[i] - expected)) / expected;
	} // The expected value should always be the same because we are expecting a uniform distribution.
	return sum;
}


// generate random numbers using the rand function and add them to the vector
void calculate_using_rand(vector<int> &data, int numTests, unsigned int seed){
	srand(seed); // set the seed value
	for(int i = 0; i < numTests; i++){
		// gets the last digit of each number - not the best way to use this generator, but sufficient for our purposes
		data[rand()%10]++;
	}
}

// generate random numbers using the uniform_int_distribution function and add them to the vector
void calculate_using_uniform_int_distribution(vector<int> &data, int numTests, unsigned int seed){
	default_random_engine generator(seed); // set the seed value
	uniform_int_distribution<int> distribution(0,9); // min=0, max=9. We can do this because the generator produces integers.
	for(int i = 0; i < numTests; i++){
		data[distribution(generator)]++; // adds each random digit to the vector
	}
}

// generate random numbers using the discrete_distribution function and add them to the vector
void calculate_using_discrete_distribution(vector<int> &data, int numTests, unsigned int seed){
	default_random_engine generator(seed); // set the seed value
	discrete_distribution<int> distribution {1,1,1,1,1,1,1,1,1,1}; // the probability of generating the numbers 0-9 is equal
	for(int i = 0; i < numTests; i++){
		data[distribution(generator)]++; // adds each random digit to the vector
	}
}

// generate random numbers using Neha Deshpande's homemade generator and add them to the vector
void calculate_using_neha_generator(vector<int> &data, int numTests, unsigned int seed){
	neha_generator generator(seed);
	for(int i = 0; i < numTests; i++){
		data[generator.random_number()]++; // adds each random digit to the vector
	}
}

// generate random numbers using the crappy, cyclic, predictable generator and add them to the vector
void calculate_using_crappy_generator(vector<int> &data, int numTests, unsigned int seed){
	crappy_generator generator(seed);
	for(int i = 0; i < numTests; i++){
		data[generator.random_number()]++; // adds each random digit to the vector
	}
}

// generate random numbers using the piecewise_constant_distribution generator and add them to the vector
void calculate_using_piecewise_constant_distribution(vector<int> &data, int numTests, unsigned int seed){
	std::default_random_engine generator( seed ); // set the seed value
	std::array<double,11> intervals {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}; 
 	std::array<double,10> weights {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 }; //defines the distribution based on corresponding 'weights'
	std::piecewise_constant_distribution<double> distribution (intervals.begin(),intervals.end(),weights.begin()); 
	for(int i = 0; i < numTests; i++){
		data[distribution(generator)]++; // adds each random digit to the vector
	}
}

// generate random numbers using java.util.Random's linear congruential generator and add them to the vector
void calculate_using_java_util_Random(vector<int> &data, int numTests, unsigned int seed){
	lin_con_gen generator(seed, 25214903917, 11, pow(2,48));
	for(int i = 0; i < numTests; i++){
		data[generator.random_number()]++; // adds each random digit to the vector
	}
}

// generate random numbers using java.util.Random's linear congruential generator and add them to the vector
void calculate_using_visual_basic(vector<int> &data, int numTests, unsigned int seed){
	lin_con_gen generator(seed, 1140671485, 12820163, pow(2,24));
	for(int i = 0; i < numTests; i++){
		data[generator.random_number()]++; // adds each random digit to the vector
	}
}

// generate random numbers using java.util.Random's linear congruential generator and add them to the vector
void calculate_using_carbon(vector<int> &data, int numTests, unsigned int seed){
	lin_con_gen generator(seed, 16807, 0, pow(2,31) - 1);
	for(int i = 0; i < numTests; i++){
		data[generator.random_number()]++; // adds each random digit to the vector
	}
}

// generate random numbers using a custom linear congruential generator and add them to the vector
void calculate_using_custom(vector<int> &data, int numTests, unsigned int seed, long a, long c, long m){
	lin_con_gen generator(seed, a, c, m);
	for(int i = 0; i < numTests; i++){
		data[generator.random_number()]++; // adds each random digit to the vector
	}
}

// prints a command line error message, then exits the program
void command_line_error(){
	cout << "Error: command line arguments\nUsage: ./a.out [numTests] [type] [seed] OR ./a.out [numTests] custom_lin_con [seed] [a] [c] [m]" << endl;
	exit(1);
}

// from https://stackoverflow.com/questions/8888748/how-to-check-if-given-c-string-or-char-contains-only-digits
bool ensure_num(const std::string &str) {
	if (!(str.find_first_not_of("0123456789") == std::string::npos)){
		command_line_error();
	}
    return true;
}

int main(int argc, char **argv) {

	// unordered map with command line argument and the official name for printing statistics
	// This is complicated - it is a map, with the unofficial name string as the key and a pair as the value.
	// The pair has the official name string as first and a function pointer as a second.
	// The function pointer points to a void function with arguments below. All the functions should have this format
	unordered_map<string, pair<string, void (*)(vector<int>&, int, unsigned int)> > PRNGs = {
		{"rand", make_pair("C++ rand", calculate_using_rand) },
		{"uniform_int_distribution", make_pair("C++ uniform_int_distribution", calculate_using_uniform_int_distribution) },
		{"discrete_distribution", make_pair("C++ discrete_distribution", calculate_using_discrete_distribution) },
		{"neha_generator", make_pair("Neha Deshpande's Homemade PRNG", calculate_using_neha_generator) },
		{"crappy_generator", make_pair("Crappy Homemade PRNG", calculate_using_crappy_generator) },
		{"piecewise_constant_distribution", make_pair("C++ piecewise_constant_distribution", calculate_using_piecewise_constant_distribution) },
		{"java", make_pair("java.util.Random", calculate_using_java_util_Random) },
		{"visual_basic", make_pair("Microsoft Visual Basic (6 and earlier)", calculate_using_visual_basic) },
		{"carbon", make_pair("Apple Carbon", calculate_using_carbon) }
	};

	//initialize the map values to 0
	//the index is the generated number
	//data[index] is the number of occurrences of that number
    vector<int> data(10, 0); 

	//ensure we have the correct number of command line args
	if(argc != 4 && argc != 7){
		command_line_error();
	}
	
	// PARSE ARGUMENTS & CALCULATE DATA
	ensure_num(argv[1]);
	int numTests = atoi(argv[1]);
	unsigned int seed;

	if(argv[3] == string("time")){
		seed = time(NULL);
	}
	else{
		ensure_num(argv[3]);
		seed = atoi(argv[3]);
	}

	string official_name;
	//check command line arguments
	if(argc == 7){ //linear congruential generator with custom a, c, and m values
		if(argv[2] != string("custom_lin_con")){ // cannot have a, c, and m values for other generators
			command_line_error();
		}
		official_name = "a Custom Linear Congruental Generator";
		ensure_num(argv[4]);
		ensure_num(argv[5]);
		ensure_num(argv[6]);
		calculate_using_custom(data,numTests,seed,atoi(argv[4]),atoi(argv[5]),atoi(argv[6]));
	}
	else{
		//call the function to calculate random numbers
		// argv[2] is the unofficial name, PRNGs[argv[2]] is the pair for that PRNG, and .second is the function pointer in the pair.
		// The three arguments to the function are data, numTests, and seed.
		// Function pointers allow dynamic data structures without needing to individually call each function.
		if (PRNGs.find(argv[2]) == PRNGs.end()) {
			command_line_error();
		}
		PRNGs[argv[2]].second(data,numTests,seed);;
		official_name = PRNGs[argv[2]].first;
	}

  	//print out data using the generator's official name
	cout << "Using " << official_name << ".\nThe random number seed is " << seed << ".\nRunning " << numTests << " tests." << endl;


	// PLOT STYLING HERE
	// using the data vector

    plt::figure_size(1200, 780); // size of the graph

    plt::bar(data); //we want to plot a bar graph with the random number data

	vector<double> x; // plot a line at y=1000 to show uniform distribution
	x.push_back(-0.5);
	x.push_back(9.5);
	vector<double> y;
	y.push_back(numTests/10);
	y.push_back(numTests/10);
	plt::plot(x, y,"r--");

    map<string,string> style; //styling of subtitle
    style["family"]="serif";
    style["color"]="black";
    style["weight"]="bold";
    style["size"]="20";
    plt::suptitle("Frequency of Pseudo-Random Numbers",style);

    style["size"]="17"; // styling of title
    style["weight"]="normal";
	plt::title("generated using " + official_name + "; seed=" + to_string(seed), style);

	style["size"]="14"; // styling of graph
	plt::xlabel("Generated Number",style);
	plt::ylabel("Frequency",style);

	plt::axis("on"); // styling the x and y axes
	vector<int> ints;
	for(int i = 0; i < 10; i++){
		ints.push_back(i);
	}
	plt::xticks(ints);

    map<string,double> adjust_spacing;    // styling the spacing
    adjust_spacing["top"]=0.89;
	plt::subplots_adjust(adjust_spacing);


	// CALCULATE & PRINT STATISTICS HERE

    //degrees of freedom = 10-1=9, alpha value = 0.05; so, critical value = 16.919
    double critical_value = 16.919; // see README for more information
    string good_or_bad = "good";

   	double chi_squared = calculate_chi_squared(data,numTests/10.0);
   	if(chi_squared > critical_value) good_or_bad = "bad";

   	//			 chi^2 unicode
	cout << "\u03A7\u00B2 = " << chi_squared << "." << endl;
	cout << "A good generator's \u03A7\u00B2 should be below " << critical_value << "." << endl;
	cout.precision(3);
	cout << "This generator's \u03A7\u00B2 is " << fixed << chi_squared << "." << endl;
	cout << "Based on this test, " << official_name << " is a " << good_or_bad << " generator." << endl;


	//SAVE FILE
	//save the graph to a file (can be pdf, png, jpg, etc.)
	replace( official_name.begin(), official_name.end(), ' ', '_');
    plt::save(official_name + "__tests-" + to_string(numTests) + "__seed-" + to_string(seed) + ".png"); // come up with a better name than this

    return (0);
}
