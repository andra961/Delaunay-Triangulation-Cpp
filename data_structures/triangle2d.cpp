#include "triangle2d.h"

#include <algorithms/dag_utilities.h>

/**
 * @brief constructor given the points
 * @param points array containing 3 points
 */

Triangle2d::Triangle2d(const std::array<cg3::Point2Dd,3>& points){

    this->vertices=points;
}

/**
 * @brief constructor given the points
 * @param point1 the first point
 * @param point2 the second point
 * @param point3 the third point
 */

Triangle2d::Triangle2d(const cg3::Point2Dd& point1,const cg3::Point2Dd& point2,const cg3::Point2Dd& point3){

        std::array<cg3::Point2Dd,3> points;
        points[0] = point1;
        points[1] = point2;
        points[2] = point3;

    this->vertices=points;
}

/**
 * @brief get the points
 * @return the points of the triangle
 */

const std::array<cg3::Point2Dd,3>& Triangle2d::getPoints() const{
    return this->vertices;
}

/**
 * @brief get a point given the index
 * @param index the index of the point to be returned
 */

const cg3::Point2Dd& Triangle2d::getPoint(const size_t index) const{
    return this->vertices[index];
}

/**
 * @brief set the points of the triangle
 * @param points array of 3 points that will overwrite the current 3 ones
 */

void Triangle2d::setPoints(const std::array<cg3::Point2Dd,3>& points){

    this->vertices = points;
}

/**
 * @brief set the points of the triangle
 * @param point1 overwrites the first point
 * @param point2 overwrites the second point
 * @param point3 overwrites the third point
 */

void Triangle2d::setPoints(const cg3::Point2Dd& point1,const cg3::Point2Dd& point2,const cg3::Point2Dd& point3){

    std::array<cg3::Point2Dd,3> points;
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;

    this->vertices = points;
}
