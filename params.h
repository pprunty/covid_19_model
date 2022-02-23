/**
 * \file            params.h
 * \brief           Header file containing some structures for the program
 * \author          P. Prunty
 * \version         1.0
 * \date            2020-04-11
 */
#ifndef PARAMS_H_BAPBFPZN
#define PARAMS_H_BAPBFPZN

#include <random>
#include <fstream>

extern std::default_random_engine gen;

/**
 * \brief Structure to hold parameters needed by program
 */
struct Params{
    int xdim 			= 100;          	//!< width of the grid
    int ydim 			= 100; 		        //!< height of the grid
    double spring_constant   	= 0.0; 		//!< "Spring constant" which controls attraction to "home"

    int time_to_recovery     	= 14; 		//!< Number of days until a person recovers. This will be set to a constant
    double death_percentage    	= 0.2; 		//!< Percentage of infected people who die before time_to_recovery
    double transmission_prob 	= 0.5;   	//!< Probability that a sick person will infect another person at same grid site on each iteration.
};



#endif /* end of include guard: PARAMS_H_BAPBFPZN */
