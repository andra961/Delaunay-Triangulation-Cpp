#include "triangle_utilities.h"

/**
 * @brief return the angle of a point formed with the positive x axis through atan2
 * @param point the point
 * @return the angle computed through atan2
 */

double getClockWiseAngle(const cg3::Point2Dd& point) {
    double angle = std::atan2(point.x(), point.y());
    return angle;
}

/**
 * @brief used to compare the angles of two points
 * @param point1 the first point
 * @param point2 the second point
 * @return true if the first angle is smaller else false
 */

bool comparePointsClockWise(const cg3::Point2Dd& point1, const cg3::Point2Dd& point2) {
    return getClockWiseAngle(point1) < getClockWiseAngle(point2);
}

/**
 * @brief sort the points in clockwise order
 * @param points an array of the 3 points to be sorted
 */

void sortTriangleClockWise(std::array<cg3::Point2Dd,3>& points){
    std::sort(points.begin(),points.end(),comparePointsClockWise);
}

/**
 * @brief sort the points in anticlockwise order
 * @param points an array of the 3 points to be sorted
 */

void sortTriangleAntiClockWise(std::array<cg3::Point2Dd,3>& points){

    sortTriangleClockWise(points);
    std::reverse(points.begin(),points.end());
}

Dag_node* searchTriangle(Triangulation& triangulation,Dag_node* dag,const cg3::Point2Dd& point)
{
    for(size_t i = 0; i < dag->getChildren().size(); i++)
        {
            Triangle2d current_triangle = triangulation.getTriangle(dag->getChildren()[i]->getIndex());
            if(isPointLyingInTriangle(current_triangle.getPoint(0),current_triangle.getPoint(1),current_triangle.getPoint(2),point,true))
            {
                return searchTriangle(triangulation,dag->getChildren()[i],point);
            }
        }

    return dag;
}

void deleteDag(Dag_node* dag){
    if(dag != NULL){
        for (size_t i = 0;i<dag->getChildren().size();i++) {
            deleteDag(dag->getChildren()[i]);
        }
        delete dag;
        dag = NULL;
    }
}


