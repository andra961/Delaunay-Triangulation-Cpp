#include "triangle2d.h"

/**
 * @brief default constructor
 */

Triangle2d::Triangle2d()
{

}

/**
 * @brief constructor given the points
 * @param points array containing 3 points
 * @param clockWiseOrAntiClockWise if true the triangle must be in clockwise order else in anticlockwise order
 */

Triangle2d::Triangle2d(std::array<cg3::Point2Dd,3>& points){

        sortTriangleAntiClockWise(points);

    this->vertices=points;
}

/**
 * @return the points of the triangle
 */

const std::array<cg3::Point2Dd,3>& Triangle2d::getPoints() const{
    return this->vertices;
}

/**
 * @brief set the points of the triangle
 * @param points array of 3 points that will overwrite the current 3 ones
 * @param clockWiseOrAntiClockWise if true the triangle must be in clockwise order else in anticlockwise order
 */

void Triangle2d::setPoints(std::array<cg3::Point2Dd,3>& points){

        sortTriangleAntiClockWise(points);

    this->vertices = points;
}
