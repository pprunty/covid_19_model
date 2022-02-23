/**
 * \file assignment4b.cc
 * \brief Main function for second part of Assignment 4
 * \author R. Morrin
 * \version 1.0
 * \date 2020-04-12
 */
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstddef>
#include <iterator>

#include "params.h"
#include "person.h"
#include "grid.h"

std::random_device rd;
std::default_random_engine gen(rd());


int main(int argc, char *argv[]) {

    const int NUM_POPULATION{10'000}; //20000
    const int NUM_INITIAL_INFECTED{100};

    auto p = std::make_shared<Params>();

    // If more than one argument, read second argument as spring constant
    if (argc > 1) {
        if (sscanf(argv[1], "%lf", &(p->spring_constant)) != 1) {
            throw "Error reading from argv[1]";
        }
    }

    // Create object of type Grid
    Grid grid(p->xdim, p->ydim, NUM_POPULATION);

    // Vector of Persons
    std::vector <Person> population;

    // Create name for output file
    std::ofstream f1;
    std::stringstream fname;
    fname << p->xdim << "x" << p->ydim << "_p" << NUM_POPULATION << "_i" << NUM_INITIAL_INFECTED << "_k"
          << p->spring_constant << "_d" << p->death_percentage << "_t" << p->transmission_prob << ".txt";

    // Open existing file if it exists and truncate it.
    f1.open(fname.str(), std::ios::trunc);
    if (f1.is_open()) {
        f1.close();
    }

    // Two uniform integer distributions. One for each dimension
    auto uix = std::uniform_int_distribution<>(0, p->xdim - 1);
    auto uiy = std::uniform_int_distribution<>(0, p->ydim - 1);

    // Create Person objects at randomly generated coordinates.
    for (int i = 0; i < NUM_POPULATION; i++) {
        // emplace_back adds a random element pair (x,y) to the end of the population vector.
        population.emplace_back(Point{uix(gen), uiy(gen)}, p);
    }

    // Makes a certain number of Persons flags to infected.
    for (int i = 0; i < NUM_INITIAL_INFECTED; i++) {
        grid.infect_on_grid(population[i]);
    }

    int i = 0;

    // Write t=0 to stats table
    grid.print_stats(fname.str(), i);
    ++i;

    // Initial grid
    std::cout << "Initial grid at t=0" << std::endl;
    std::cout << std::endl << grid;

    std::cout << "Writing final results to file: " << fname.str() << std::endl;


    //grid.print_stats(fname.str(), i);
    while (grid.still_infected()) {
        // Uncomment line below to print grid to screen
        // std::cout << grid << '\n';
        for (auto it = population.begin(); it != population.end(); ++it) {
            it->propose_move();
        }
        grid.update_configuration(population);
        grid.print_stats(fname.str(), i);
        ++i;
    }

    // Final update
    grid.update_configuration(population);

    std::cout << "Final grid at t=T" << std::endl;
    std::cout << std::endl << grid;

    return 0;
}
