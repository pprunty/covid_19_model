#ifndef POINT_H_OMJSZLDH
#define POINT_H_OMJSZLDH
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>

#include "point.h"

/**
 * \brief Simple structure to store coordinates of a point on the grid
 */
struct Point {
    int x; 					//!< x-coordinate
    int y; 					//!< y-coordinate

    // Write the definition of this in point.cc
    bool operator==(const Point & rhs) {
        return x == rhs.x && y == rhs.y;
    }
};

/**
 * \brief Overloading output stream operator for a Point.
 * The operator should simply print the x and y coordinates of Point "in"
 *
 * \param os    Reference to output stream
 * \param in    Reference to Point which we want to print.
 *
 * \return      Reference to output stream
 */
inline std::ostream & operator<<(std::ostream & os,const Point & in){
    os << std::fixed << std::setw(9) << in.x << ", " << std::setw(9) << in.y;
    return os;
}

#endif /* end of include guard: POINT_H_OMJSZLDH */
