#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>

#include "params.h"
#include "person.h"
#include "grid.h"

/**
 * \brief       This is the default constructor for the class Grid. The constructor takes three arguments,
 *              the x and y dimensions of the grid and z being the number of people on the grid at time=0.
 *              The constructor allocates space for the data container to store a vector of ints at each
 *              point (x,y).
 * \param x     The number of sites in the x direction.
 * \param y     The number of sites in the y direction.
 * \param z     The number of people on the grid at the start of the simulation (population).
 * \return      Default constructor never has a return type.
 */
Grid::Grid(int x, int y, int z) : width_{x}, height_{y}, orig_population_{z} {

    data_.resize(width_);
    for (auto i = 0; i <= width_; ++i) {
        data_[i].resize(height_);
    }
}

/**
 * \brief       This data_ member of Grid keeps track of the persons at each site, this function
 *              simply clears the list at each site in between each timestep so that it can be
 *              populated again for the next time-step.
 * \return      void function.
 */
void Grid::reset_grid_() {

    for (unsigned long i = 0; i < data_.size(); ++i) {
        for (unsigned long j = 0; j < data_[i].size(); ++j) {
            data_[i][j].clear();
        }
    }
    /*
     for(auto it = data_.begin(); it != data_.end(); ++it){
         for(auto it2 = it->begin(); it2 != it->end(); ++it2){
             it2->clear();
         }
    }
    */
}

/**
 * \brief           This function updates the number of Persons at each (x,y) site. To do this, it loops through the
 *                  the population vector and checks each Person's curret location (x,y) and pushes the grid container
 *                  back appropriately with the number associated with the Person at that site. For example, if Person
 *                  0 is at (1,1), then data[1][1].push_back(1). So data[1][1][0] = 1. Likewise, if Person 5 is at (1,1), then
 *                  data[1][1].push_back(5). Now data[1][1][1] = 5. pop.at(5) =
 * \param &pop      Reference to the population vector.
 * \return          void function.
 */
void Grid::update_grid_counts_(std::vector <Person> &pop) {

    reset_grid_();  // Reset previous counter.

    for (unsigned long i = 0; i < pop.size(); ++i)
        data_[pop[i].current_location_.x][pop[i].current_location_.y].push_back(i);

}

/**
 * \brief           This function is an overload operator << for Grid. When this operator is called on an object of type Grid
 *                  it should print the grid to screen with the counts of the number of Persons at each site. Through the
 *                  simple use of std::cout << grid;
 * \param &os       Reference to output stream
 * \param in        Reference to grid object.
 * \return          os
 */
std::ostream &operator<<(std::ostream &os, Grid &in) {

    // We are interested in the number of Persons at each (x,y) on the
    // grid, so we print the size of the third dimension.
    for (unsigned long i = 0; i < in.data_.size(); ++i) {
        os << "| ";
        for (unsigned long j = 0; j < in.data_[i].size(); ++j) {
            os << in.data_[i][j].size();
        }
        os << "|\n";
    }
    os << "\n";

    return os;
}

/**
 * \brief           This function updates the health status of the people on the grid. If a Person's days to death counter
 *                  has reached zero, then this person is erased from the population vector, and the number of dead flag
 *                  is incremented. All other flags are set appropriately, with similar arguments.
 * \param &pop      Reference to population vector of Persons, so we can access members of each Person's class,
 *                  pop[0].member.
*/
void Grid::update_health_status_(std::vector <Person> &pop) {


    for (auto it = pop.begin(); it != pop.end();) {
        if (it->infected) {
            if ((it->days_to_recovery_)-- == 0) {
                it->infected = false;
                it->immune = true;
                ++recovered_;
                --currently_infected_;
                ++it;
            } else if ((it->days_to_death_)-- <=
                       0) { // This is <= 0 as days_to_death can be zero (can die suddenly after infection)
                it = pop.erase(it);
                ++dead_;
                --currently_infected_;
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    // Reset all just infected cases back to false - they are no longer "just infected" after a day's infection
    for (auto it = pop.begin(); it!=pop.end(); ++it) {
        if (it->just_infected) {
            it->just_infected = false;
        }
    }

}


/**
 * \brief           This function updates the configuration after all of the moves between grid sites have been made. It  loops through the population vector.
 *                  Each infected Person has a probability of infecting other Persons on the same site. If one infected Person infects another, then the status
 *                  and counters of that Person are set appropriately by calling infect_on_grid().
 * \param &pop      Reference to population of persons vector, such that members of each Person class can be accessed.
*/
void Grid::update_configuration(std::vector <Person> &pop) {

    // Uniform distribution
    std::uniform_real_distribution<> U(0, 1);

    // Transmission probability
    double prob = pop[0].params_->transmission_prob;   //< Probability an infected person transmits infection

    // Update the location of people on the grid
    update_grid_counts_(pop);

    std::vector<int> just_infected;

    // Iterate over people population
    for (auto it = pop.begin(); it != pop.end(); ++it) {

        // Inspect when there are more than two people on a single coordinate (x,y) on the grid & one is infected
        int people_on_point = data_[it->current_location_.x][it->current_location_.y].size();
        if (it->infected && !it->just_infected && people_on_point > 1) {

            // Loop through the other people on this (x,y) coordinate
            for (auto i = 0; i < people_on_point; ++i) {

                int person_idx = data_[it->current_location_.x][it->current_location_.y][i];

                if (!pop[person_idx].infected &&
                    !pop[person_idx].immune &&
                    prob > U(gen))
                         {
                        // Infect this person
                        infect_on_grid(pop[data_[it->current_location_.x][it->current_location_.y][i]]);
                        // Keep track of this person's index for future reference
                        just_infected.push_back(data_[it->current_location_.x][it->current_location_.y][i]);
                }
            }
        }
    }

    // Update health status
    update_health_status_(pop);

}

/**
 * \brief               This function prints to a file the stats on the grid until there is no more people infected.
 * \param in            The name of the file from main
 * \param i             The iteration number from loop in main
*/
void Grid::print_stats(std::string in, int i) {

    std::ofstream outfile;
    outfile.open(in, std::ios_base::app);   // Append instead of overwrite

    if (outfile.is_open()) {
        outfile << i << '\t' << currently_infected_ << '\t' << recovered_ + currently_infected_ <<
                '\t' << dead_ + currently_infected_ << '\t' << orig_population_ - dead_ << std::endl;
    } else {
        std::cerr << "Error opening outfile." << std::endl;
    }

}
