#include "triangulation.h"

/**
 * @brief default constructor;
 */

Triangulation::Triangulation()
{

}

/**
 * @brief constructor given points
 * @param init_triangle_points the array containing the points of the initial triangle of the triangulation
 */

Triangulation::Triangulation(std::array<cg3::Point2Dd,3>& init_triangle_points){
    this->triangles.push_back(Triangle2d(init_triangle_points));
}

/**
 * @brief constructor given points
 * @param init_triangle the initial triangle of the triangulation
 */

Triangulation::Triangulation(const Triangle2d& init_triangle){
    this->triangles.push_back(init_triangle);
}
