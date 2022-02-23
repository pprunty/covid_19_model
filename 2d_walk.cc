/**
 * \file            2d_walk.cc
 * \brief           This program implements a 2d walk using the Metropolis algorithm to control the persons
 *                  degree of freedom on the grid (i.e how far they stray from their starting point). This
 *                  can be thought of as the degree of social distancing parameter when modelling an infectious
 *                  disease.
 *
 * \author          P. Prunty
 * \version         1.0
 * \date            2020-04-11
 */

#include <iostream>
#include <random>

#include "params.h"
#include "person.h"


// Need to have RNG as global variable.
std::default_random_engine gen(4321);
std::mt19937 mt(4321);


int main(int argc, char *argv[])
{
    const int DIM {10};
    const int NUM_TURNS{10};
    
    auto p = std::make_shared<Params>();
    p->xdim = DIM;
    p->ydim = DIM;
    Point home {static_cast<int>(gen() % 100),static_cast<int>(gen() % 100)};

 	/*
	 * Add a try catch block
	 */

	// If more than one argument, read second argument as spring constant
	if(argc>1){
	    if(sscanf(argv[1],"%lf", &(p->spring_constant))!=1){
		throw "Error reading from argv[1]";
	    }
	}

	// Create a person object
	Person A {home, p};

	std::cout << A << '\n';
	// Evolve the system for NUM_TURNS steps
	for(auto i = 0; i< NUM_TURNS; ++i){
	    A.propose_move();
        std::cout << A << '\n';
	}


    return 0;
}
