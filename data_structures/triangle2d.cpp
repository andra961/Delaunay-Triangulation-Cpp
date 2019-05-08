#include "triangle2d.h"

#include <algorithms/triangle_utilities.h>

/**
 * @brief constructor given the points
 * @param points array containing 3 points
 * @param clockWiseOrAntiClockWise if true the triangle must be in clockwise order else in anticlockwise order
 */

Triangle2d::Triangle2d(const std::array<cg3::Point2Dd,3>& points){

    this->vertices=points;
}

Triangle2d::Triangle2d(const cg3::Point2Dd& point1,const cg3::Point2Dd& point2,const cg3::Point2Dd& point3){

        std::array<cg3::Point2Dd,3> points;
        points[0] = point1;
        points[1] = point2;
        points[2] = point3;

    this->vertices=points;
}

/**
 * @return the points of the triangle
 */

const std::array<cg3::Point2Dd,3>& Triangle2d::getPoints() const{
    return this->vertices;
}

const cg3::Point2Dd& Triangle2d::getPoint(const size_t index) const{
    return this->vertices[index];
}

/**
 * @brief set the points of the triangle
 * @param points array of 3 points that will overwrite the current 3 ones
 * @param clockWiseOrAntiClockWise if true the triangle must be in clockwise order else in anticlockwise order
 */

void Triangle2d::setPoints(const std::array<cg3::Point2Dd,3>& points){

    this->vertices = points;
}

void Triangle2d::setPoints(const cg3::Point2Dd& point1,const cg3::Point2Dd& point2,const cg3::Point2Dd& point3){

    std::array<cg3::Point2Dd,3> points;
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;

    this->vertices = points;
}
