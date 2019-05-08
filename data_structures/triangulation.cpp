#include "triangulation.h"

/**
 * @brief default constructor initialises the triangulation with a triangle representing the bounding space,so triangles with no adjacents triangles will point to that(0)
 */

Triangulation::Triangulation(const Triangle2d& init_triangle,Dag_node* dag_node)
{
    std::array<size_t,3> adjList;
    for (size_t i = 0;i < 3;i++) {
        adjList[i] = 0;
    }

    this->triangles.push_back(Triangulation_member(init_triangle,adjList,dag_node));
}

/**
 * @brief get triangle by index
 * @param index the index
 */

const Triangulation_member& Triangulation::getTriangle(const size_t index){
    return this->triangles[index];
}

std::vector<Triangulation_member>& Triangulation::getTriangles(){
    return this->triangles;
}

size_t Triangulation::size(){
    return this->triangles.size();
}

void Triangulation::addTriangle(const Triangulation_member triangle){
    this->triangles.push_back(triangle);
}

void Triangulation::setTriangleActive(const size_t index){
    this->triangles[index].setActive();
}

void Triangulation::setTriangleInactive(const size_t index){
    this->triangles[index].setInactive();
}

void Triangulation::setTriangleNeighbour(size_t triangle,size_t neighbour,size_t new_index){
    this->triangles[triangle].setNeighbour(neighbour,new_index);
}
