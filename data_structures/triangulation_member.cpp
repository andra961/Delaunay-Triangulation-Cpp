#include "triangulation_member.h"

/**
 * @brief constructor for a triangulation member
 * @param points the triangle of the member
 * @param adjList an array containing indexes of his neighbours ordered on the points
 * @param dag_node the node of the dag which points to the triangulation member
 */

Triangulation_member::Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList,Dag_node* dag_node) : Triangle2d (points)
{
    this->dag_node = dag_node;
    this->adjList = adjList;
    this->active = true;
}

/**
 * @brief constructor for a triangulation member
 * @param points the triangle of the member
 * @param adjList an array containing indexes of his neighbours ordered on the points
 * @param dag_node the node of the dag which points to the triangulation member
 * @param isActive bool which states if the triangle is active or not
 */

Triangulation_member::Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList,Dag_node* dag_node,const bool isActive) : Triangle2d (points)
{
    this->dag_node = dag_node;
    this->adjList = adjList;
    this->active = isActive;
}

/**
 * @brief sets the member of the triangulation active
 */

void Triangulation_member::setActive(){
    this->active = true;
}

/**
 * @brief sets a member of the triangulation inactive
 */

void Triangulation_member::setInactive(){
    this->active = false;
}

/**
 * @brief check if the member is active
 * @return true if is active,false otherwise
 */

bool Triangulation_member::isActive() const{
    return this->active;
}

/**
 * @brief get the index of a neighbour of the member
 * @param index the index of the neighbour in the adjList
 * @return the index of the neighbour in the triangulation
 */

size_t Triangulation_member::getNeighbour(const size_t index) const{
    return this->adjList[index];
}

/**
 * @brief get a pointer to the node of the dag which points to this member
 * @return the pointer to the node
 */

Dag_node* Triangulation_member::getDagNode() const{
    return this->dag_node;
}

/**
 * @brief changes the value of a neighbour of the triangulation member
 * @param neighbour the index of the neighbour in the adjList
 * @param new_index the new value of the neighbour
 */

void Triangulation_member::setNeighbour(size_t neighbour,size_t new_index){
    this->adjList[neighbour] = new_index;
}
