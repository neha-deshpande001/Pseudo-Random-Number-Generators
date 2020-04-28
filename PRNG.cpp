#define _USE_MATH_DEFINES

#include "matplotlibcpp.h" // graphing
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <random> // C++ generators
#include <map>
#include <unordered_map>

namespace plt = matplotlibcpp;

// this function calculates the chi squared value for a given vector of data points.
double calculate_chi_squared(std::vector<int> observed, double expected){
	double sum = 0;
	for(int i = 0; i < 10; i++){
		sum+=(((double)observed[i] - expected) * ((double)observed[i] - expected)) / expected;
	} // The expected value should always be the same because we are expecting a uniform distribution.
	return sum;
}

// generate random numbers using the rand function and add them to the map
void calculate_using_rand(std::map<int,int> &counts, int numTests, unsigned int seed){
	srand(seed); // set the seed value
	for(int i = 0; i < numTests; i++){
		// gets the last digit of each number - not the best way to use this generator, but sufficient for our purposes
		counts[rand()%10]++;
	}
}

// generate random numbers using the uniform_int_distribution function and add them to the map
void calculate_using_uniform_int_distribution(std::map<int,int> &counts, int numTests, unsigned int seed){
	std::default_random_engine generator( seed ); // set the seed value
	std::uniform_int_distribution<int> distribution(0,9); // min=0, max=9. We can do this because the generator produces integers.
	for(int i = 0; i < numTests; i++){
		counts[distribution(generator)]++; // adds each random digit to the map
	}
}

// generate random numbers using the discrete_distribution function and add them to the map
void calculate_using_discrete_distribution(std::map<int,int> &counts, int numTests, unsigned int seed){
	std::default_random_engine generator( seed ); // set the seed value
	std::discrete_distribution<int> distribution {1,1,1,1,1,1,1,1,1,1}; // the probability of generating the numbers between 0-9 is equal
	for(int i = 0; i < numTests; i++){
		counts[distribution(generator)]++; // adds each random digit to the map
	}
}



int main(int argc, char **argv) {

	// unordered map with command line argument and the official name for printing statistics
	std::unordered_map<std::string, std::string> PRNGnames {
		{"rand","C++ rand"},
		{"uniform_int_distribution", "C++ uniform_int_distribution"},
		{"discrete_distribution", "C++ discrete_distribution"}
	};

	//initialize the map values to 0
	//counts->first is the generated number
	//counts->second is the number of occurences
	std::map<int, int> counts {
		{0,0},
		{1,0},
		{2,0},
		{3,0},
		{4,0},
		{5,0},
		{6,0},
		{7,0},
		{8,0},
		{9,0},
	};

	//ensure we have the correct number of command line args
	if(argc != 4){
		std::cout << "Error: command line arguments\nUsage: ./a.out [numTests] [type] [seed]" << std::endl;
		exit(1);
	}
	
	// PARSE ARGUMENTS & CALCULATE DATA
	int numTests = atoi(argv[1]);
	unsigned int seed;

	if(argv[3] == std::string("time")){
		seed = time(NULL);
	}
	else{
		seed = atoi(argv[3]);
	}


	if(argv[2] == std::string("rand")){
		calculate_using_rand(counts,numTests,seed);
	}
	else if(argv[2] == std::string("uniform_int_distribution")){
		calculate_using_uniform_int_distribution(counts,numTests,seed);
	}
	else if(argv[2] == std::string("discrete_distribution")){
		calculate_using_discrete_distribution(counts,numTests,seed);
	}

	//print out data using the generator's official name
	std::string official_name = PRNGnames[argv[2]];
	std::cout << "Using " << official_name << ".\nThe random number seed is " << seed << ".\nRunning " << numTests << " tests." << std::endl;

	//convert the data from a map to a vector for graphing
	std::vector<int> data;
    for (std::map<int, int>::iterator itr = counts.begin(); itr != counts.end(); ++itr) { 
    	data.push_back(itr->second);
    }


	// PLOT STYLING HERE

    plt::figure_size(1200, 780); // size of the graph

    plt::bar(data); //we want to plot a bar graph with the random number data

	std::vector<double> x; // plot a line at y=1000 to show uniform distribution
	x.push_back(-0.5);
	x.push_back(9.5);
	std::vector<double> y;
	y.push_back(numTests/10);
	y.push_back(numTests/10);
	plt::plot(x, y,"r--");

    std::map<std::string,std::string> style; //styling of subtitle
    style["family"]="serif";
    style["color"]="black";
    style["weight"]="bold";
    style["size"]="20";
    plt::suptitle("Frequency of Pseudo-Random Numbers",style);

    style["size"]="17"; // styling of title
    style["weight"]="normal";
	plt::title("generated using " + official_name + "; seed=" + std::to_string(seed), style);

	style["size"]="14"; // styling of graph
	plt::xlabel("Generated Number",style);
	plt::ylabel("Frequency",style);

	plt::axis("on"); // styling the x and y axes
	std::vector<int> ints;
	for(int i = 0; i < 10; i++){
		ints.push_back(i);
	}
	plt::xticks(ints);

    std::map<std::string,double> adjust_spacing;    // styling the spacing
    adjust_spacing["top"]=0.89;
	plt::subplots_adjust(adjust_spacing);



	// CALCULATE & PRINT STATISTICS HERE

    //degrees of freedom = 10-1=9, alpha value = 0.05; so, critical value = 16.919
    double critical_value = 16.919; // see README for more information
    std::string good_or_bad = "good";

   	double chi_squared = calculate_chi_squared(data,numTests/10.0);
   	if(chi_squared > critical_value) good_or_bad = "bad";

   	//			 chi^2 unicode
	std::cout << "\u03A7\u00B2 = " << chi_squared << "." << std::endl;
	std::cout << "A good generator's \u03A7\u00B2 should be below " << critical_value << "." << std::endl;
	std::cout.precision(3);
	std::cout << "This generator's \u03A7\u00B2 is " << std::fixed << chi_squared << "." << std::endl;
	std::cout << "Based on this test, the " << official_name << " is a " << good_or_bad << " generator." << std::endl;


	//SAVE FILE
	//save the graph to a file (can be pdf, png, jpg, etc.)
	std::replace( official_name.begin(), official_name.end(), ' ', '_');
    plt::save(official_name + "__tests-" + std::to_string(numTests) + "__seed-" + std::to_string(seed) + ".png"); // come up with a better name than this

    return (0);
}