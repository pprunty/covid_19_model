/**
 * \file grid.h
 * \brief File to hold class definition for Grid class
 * \author R. Morrin
 * \version 1.0
 * \date 2020-04-12
 */
#ifndef GRID_H_XXELF1GY
#define GRID_H_XXELF1GY

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>

#include "params.h"
#include "person.h"

/**
 * \brief  Class to represent a Grid
 */
class Grid {
public:

    // Rule of 5 defaults
    Grid(int x, int y, int z);               //< Constructor
    ~Grid() {                                //< Destructor
        data_.clear();
    };

    Grid(const Grid &) = default;              //< Copy constructor
    Grid(Grid &&) = default;                   //< Move constructor
    Grid &operator=(const Grid &) = default;   //< Copy assignment operator
    Grid &operator=(Grid &&) = default;        //< Move assignment operator


    // Public member function declarations
    void update_configuration(std::vector <Person> &pop);
    void print_stats(std::string in, int i);
    friend std::ostream &operator<<(std::ostream &os, Grid &in);


    /**
     * \brief This function will cause a Person to be marked as "infected" and increment the corresponding grid counter
     *
     * \param p  Person to infect.
     */
    void infect_on_grid(Person &p) {
        p.infect();              //<! Infects the person on the grid
        ++currently_infected_;  //<! Increments the number of infected people on the grid
    }

    /**
     * \brief Simple function to determine whether there are any Persons still infected on the grid
     *
     * \return  true if infected people remain on the grid
     */
    bool still_infected() {
        return (currently_infected_ > 0);
    }

//    void update_max_infected() {
//        if (currently_infected_ > max_infected_) {
//            max_infected_ = currently_infected_;
//        }
//    }


private:
    void reset_grid_();

    void update_health_status_(std::vector <Person> &pop);

    int width_;                //<! Width of the grid. i.e. number of sites in x direction
    int height_;               //<! Height of the grid. i.e. number of sites in y direction
    int orig_population_;      //<! Number of people on grid at start of simulation

    //!< Store locations as vector-of-vectors. Each location has vector of Persons
    std::vector <std::vector<std::vector < int>>> data_;

    void update_grid_counts_(std::vector <Person> &pop);

    int currently_infected_ = 0;    //<! Holds number of currently infected Persons
    int dead_ = 0;                  //<! Holds number of dead Persons
    int recovered_ = 0;             //<! Holds number of recovered Persons
//    int max_infected_ = currently_infected_; //<! The maximum number of infections for a given simulation
};


#endif /* end of include guard: GRID_H_XXELF1GY */
