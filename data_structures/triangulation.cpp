#include "triangulation.h"

/**
 * @brief constructor initialises the triangulation with a triangle representing the bounding space,so triangles with no adjacents triangles will point to that(0)
 * @param init_triangle the bounding triangle,MUST be sorted in anti-clockwise order
 * @param dag_node the node of the dag which will point to the bounding triangle(the root of the dag)
 */

Triangulation::Triangulation(const Triangle2d& init_triangle,Dag_node* dag_node)
{
    std::array<size_t,3> adjList;
    // the bounding triangle has no neighbour,so we set each element of the adj list to 0(we use 0 to indicate that a triangle has no neighbour on a side)
    for (size_t i = 0;i < 3;i++) {
        adjList[i] = 0;
    }
    this->triangles.push_back(Triangulation_member(init_triangle,adjList,dag_node));
}

/**
 * @brief get triangulation member by index
 * @param index the index
 * @return the triangulation member
 */

const Triangulation_member& Triangulation::getTriangle(const size_t index){
    return this->triangles[index];
}

/**
 * @brief get the vector of the triangles
 * @param index the index
 * @return the vector of triangulation members
 */

std::vector<Triangulation_member>& Triangulation::getTriangles(){
    return this->triangles;
}

/**
 * @brief get the triangulation's size
 * @return the size of the triangulation
 */

size_t Triangulation::size(){
    return this->triangles.size();
}

/**
 * @brief adds a triangulation member to the triangulation
 * @param triangle the member to add
 */

void Triangulation::addTriangle(const Triangulation_member triangle){
    this->triangles.push_back(triangle);
}

/**
 * @brief sets a member of the triangulation active
 * @param index the index of the member to activate
 */

void Triangulation::setTriangleActive(const size_t index){
    this->triangles[index].setActive();
}

/**
 * @brief sets a member of the triangulation inactive
 * @param index the index of the member to deactivate
 */

void Triangulation::setTriangleInactive(const size_t index){
    this->triangles[index].setInactive();
}

/**
 * @brief changes the value of a neighbour of a triangulation member
 * @param triangle the index of the member
 * @param neighbour the index in the adj list of the neighbour to change
 * @param new_index the neighbour will be set to the this new index
 */

void Triangulation::setTriangleNeighbour(size_t triangle,size_t neighbour,size_t new_index){
    this->triangles[triangle].setNeighbour(neighbour,new_index);
}
