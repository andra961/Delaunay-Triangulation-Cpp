#include "triangulation.h"

/**
 * @brief default constructor initialises the triangulation with a triangle representing the bounding space,so triangles with no adjacents triangles will point to that(0)
 */

Triangulation::Triangulation()
{
    std::array<cg3::Point2Dd,3> bounding_space;
    cg3::Point2Dd point = cg3::Point2Dd(0,0);

    bounding_space[0] = point;
    bounding_space[1] = point;
    bounding_space[2] = point;

    this->triangles.push_back(Triangulation_member(bounding_space));

    std::vector<size_t> adj_list;

    adj_list.push_back(0);
    adj_list.push_back(0);
    adj_list.push_back(0);

    this->adjacency_lists.push_back(adj_list);
}

/**
 * @brief get triangle by index
 * @param index the index
 */

Triangulation_member Triangulation::getTriangle(const size_t index) const{
    return this->triangles[index];
}

/**
 * @brief add a triangle and its neighbours
 * @param triangle_points the triangle to add
 * @param adjacency1 neighbour,put 0 if it has not neighbours
 * @param adjacency2 neighbour,put 0 if it has not neighbours
 * @param adjacency3 neighbour,put 0 if it has not neighbours
 */

void Triangulation::addTriangle(std::array<cg3::Point2Dd,3>& triangle_points,size_t adjacency1,size_t adjacency2,size_t adjacency3){
    this->triangles.push_back(Triangulation_member(triangle_points));
    std::vector<size_t> adj_list;

    adj_list.push_back(adjacency1);
    adj_list.push_back(adjacency2);
    adj_list.push_back(adjacency3);

    this->adjacency_lists.push_back(adj_list);
}

std::vector<size_t> Triangulation::getNeighbours(const size_t index) const{
    return this->adjacency_lists[index];
}

void Triangulation::setTriangleActive(const size_t index){
    this->triangles[index].setActive();
}
void Triangulation::setTriangleInactive(const size_t index){
    this->triangles[index].setInactive();
}
