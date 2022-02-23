#include <memory>
#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

#include "params.h"
#include "person.h"

/**
 * \brief           This is the default constructor for the class Person, which initializes the private members of the class
 *                  using a member initialistion list.
 * \param s         The original location initialized when the object is created (home location).
 * \param p         Shared pointer to parameters structure.
 *
 * \return          Default constructor never has a return type.
 */
Person::Person(Point s, std::shared_ptr <Params> p) : original_location_{s}, params_{p} {

    // Initialise current (beginning location) to the original (home location).
    current_location_ = original_location_;
}

/**
 * \brief           Overloading output stream operator for a Point. The operator should simply print the x and y coordinates
 *                  of Point "in". Here, the stream operator has already been overloaded to print the coordinates of the struct
 *                  Point, so all we have to do is simply use a std::cout to print the current location to screen.
 * \param os        Reference to output stream.
 * \param in        Reference to Point which we want to print.
 *
 * \return          Reference to output stream.
 */
std::ostream &operator<<(std::ostream &os, const Person &p) {

    // Print current location to the outstream
    std::cout << p.current_location_;
    return os;
}

/**
 * \brief       This function randomly proposes a move from one location to another location on the grid. For the avoidance of
 *              doubt. The proposal to move to a particular state is equally weighted. The probability of accepting that move is not.
 *              Thus, the probability of moving from one state to another is uniform and depends on the number of neighbours the
 *              current state has. The energy of a state is modelled by a spring, where the potential energy of the spring (location)
 *              is 0.5*k*r^2. Here, k is some spring constant defined by the user and r is the displacement of the spring from home,
 *              which is initialized in the main function as being the center of the grid, {5,5}. If the new, randomly generated state
 *              is closer to home, then we accept the new state unconditionally. However, if the new state is further away from home
 *              we accept it with some probability.  This process is similar to that of a Simulated Annealing process.
 * \return      void function.
 */
void Person::propose_move() {


    int xmin{current_location_.x}, xmax{current_location_.x}, ymin{current_location_.y}, ymax{current_location_.y};

    int deltax{original_location_.x - current_location_.x};
    int deltay{original_location_.y - current_location_.y};
    int curdist_xsq = {deltax * deltax + deltay * deltay};

    if (current_location_.x > 0)
        xmin--;
    if (current_location_.x < params_->xdim - 1)
        xmax++;
    if (current_location_.y > 0)
        ymin--;
    if (current_location_.y < params_->ydim - 1)
        ymax++;

    //
    std::uniform_int_distribution<> xdis{xmin, xmax};
    std::uniform_int_distribution<> ydis{ymin, ymax};

    int propx{xdis(gen)};
    int propy{ydis(gen)};

    deltax = original_location_.x - propx;
    deltay = original_location_.y - propy;

    int propdist_xsq = {deltax * deltax + deltay * deltay};

    std::uniform_real_distribution<> U(0, 1);

    if (propdist_xsq <= curdist_xsq) {
        current_location_.x = propx;
        current_location_.y = propy;
    } else if (U(gen) < std::exp(-params_->spring_constant * (propdist_xsq - curdist_xsq))) {
        current_location_.x = propx;
        current_location_.y = propy;
    }
}

/**
 * \brief       This functions sets the member bool infected to true for the person. It also randomly assigns the days to death
 *              variable for that person and finally, copies the time to recovery from the Params class to the member variable
 *              days to recover.
 * \return      void function.
 */
void Person::infect() {

    // Infect the person
    infected = true;
    just_infected = true;

    // Copy the time to recover from Params class to days to recovery.
    days_to_recovery_ = params_->time_to_recovery;

    // The rate on average a person will live
    double lambda = 1.0 / days_to_recovery_;

    // Initialize uniform dist
    std::uniform_real_distribution<> U(0, 1);

    double u = U(gen);

    // Use inverse transform method to map back to exponentially distributed number
    days_to_death_ = static_cast<int>(-1.0/lambda * std::log(1-u));
}