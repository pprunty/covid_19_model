/**
 * \file                person.h
 * \brief               Header file containing class definition for Person class
 * \author              P. Prunty
 * \version             1.0
 * \date                2020-04-11
 */
#ifndef PERSON_H_UEFXG10N
#define PERSON_H_UEFXG10N

#include <memory>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>

#include "point.h"

/**
 * \brief Class to hold data related to a person in the model
 */
class Person
{
public:
    Person (Point s, std::shared_ptr<Params> p);

    friend std::ostream& operator<<(std::ostream & os, const Person & p);
    void propose_move(); 		

private:
    Point current_location_;
    Point original_location_;
    std::shared_ptr<Params> params_;

  
    friend class Grid;
    void infect();
    int days_to_recovery_;
    int days_to_death_;
    bool infected = false;
    bool immune = false;
    bool just_infected = false;

};

#endif /* end of include guard: PERSON_H_UEFXG10N */
