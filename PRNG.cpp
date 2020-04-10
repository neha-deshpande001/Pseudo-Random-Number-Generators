#define _USE_MATH_DEFINES

#include "matplotlibcpp.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <random>
#include <map>
#include <unordered_map>

namespace plt = matplotlibcpp;

//compile: g++ PRNG.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7
//run: ./a.out [numTests] [type] [seed]

/*
numTests
-integer

type
-rand
-uniform_int_distribution

seed
-time
-integer >0
*/
double calculate_chi_squared(std::vector<int> observed, double expected){
	double sum = 0;
	for(int i = 0; i < 10; i++){
		sum+=(((double)observed[i] - expected) * ((double)observed[i] - expected)) / expected;
	}
	return sum;
}

void calculate_using_rand(std::map<int,int> &counts, int numTests, unsigned int seed){
	srand(seed);
	for(int i = 0; i < numTests; i++){
		counts[rand()%10]++;
	}
}

void calculate_using_uniform_int(std::map<int,int> &counts, int numTests, unsigned int seed){
	std::default_random_engine generator( seed );
	std::uniform_int_distribution<int> distribution(0,9);
	for(int i = 0; i < numTests; i++){
		counts[distribution(generator)]++;
	}

}

int main(int argc, char **argv) {

	// unordered map with command line argument and the official name
	std::unordered_map<std::string, std::string> PRNGnames {
		{"rand","C++ rand"},
		{"uniform_int_distribution", "C++ uniform_int_distribution"}
	};
	//TODO: make this an unordered_map<std::string, std::set<std::string, function> >
	// so that we can call the calculate function from here rather than having an if statement later on
	// void pointer(? do more research)

	//initialize the map values to 0
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
		calculate_using_uniform_int(counts,numTests,seed);
	}

	std::string official_name = PRNGnames[argv[2]];
	std::cout << "Using " << official_name << ". The random number seed is " << seed << ". Running " << numTests << " tests." << std::endl;

	//convert the data from a map to a vector for graphing
	std::vector<int> data;
    for (std::map<int, int>::iterator itr = counts.begin(); itr != counts.end(); ++itr) { 
    	data.push_back(itr->second);
    }


	// PLOT STYLING HERE

    plt::figure_size(1200, 780);

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

    //degrees of freedom = 10-1=9, alpha value = 0.5
    // so, critical value = 16.919
    double critical_value = 16.919; // see README for more information
    std::string good_or_bad = "good";

   	double chi_squared = calculate_chi_squared(data,numTests/10.0);
   	if(chi_squared > critical_value) good_or_bad = "bad";

   	// print PRNG statistics

   	//			 chi^2 unicode
	std::cout << "\u03A7\u00B2 = " << chi_squared << std::endl;
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



/*
TODO:
-maybe have chi^2 info on the side of the graphs
-void pointer for efficiency
-do this for many PRNGs
	-homemade!
	-other C++ generators
	-KISS algorithm
	-atmospheric noise from random.org (would be interesting but more difficult)- http://www.random.org/clients/http/
-clean up comments
-update README
-make this todo list into issues on github
*/

/*
How this works:
1. run the test 1000 times - num %10 -> [0,9]
2. count how many times each number appears
3. graph- ideally, it should be a uniform distribution
4. chi squared test - if p is below 0.05, the die is not balanced

Do this for many PRNGs
	-C++ rand with seed 1
	-C++ rand with seed time
	-KISS algorithm
*/
 