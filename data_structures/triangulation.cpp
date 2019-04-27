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

/**
 * @brief get triangle by index
 * @param index the index
 */

Triangle2d getTriangle(const int index) const{

}

/**
 * @brief erase triangle by index
 * @param index the index
 */

void eraseTriangle(const int index){

}

/**
 * @brief add a triangle and its neighbours
 * @param triangle_points the triangle to add
 * @param adjacency1 neighbour
 * @param adjacency2 neighbour
 * @param adjacency3 neighbour
 */

void addTriangle(std::array<cg3::Point2Dd,3>& triangle_points,int adjacency1,int adjacency2,int adjacency3){

}
