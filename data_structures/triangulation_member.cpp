#include "triangulation_member.h"

Triangulation_member::Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList,Dag_node* dag_node) : Triangle2d (points)
{
    this->dag_node = dag_node;
    this->adjList = adjList;
}

Triangulation_member::Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList,Dag_node* dag_node,const bool isActive) : Triangle2d (points)
{
    this->dag_node = dag_node;
    this->adjList = adjList;
    this->active = isActive;
}

void Triangulation_member::setActive(){
    this->active = true;
}

void Triangulation_member::setInactive(){
    this->active = false;
}

bool Triangulation_member::isActive() const{
    return this->active;
}

size_t Triangulation_member::getNeighbour(const size_t index) const{
    return this->adjList[index];
}

Dag_node* Triangulation_member::getDagNode() const{
    return this->dag_node;
}

void Triangulation_member::setNeighbour(const size_t neighbour,const size_t new_index){
    this->adjList[neighbour] = new_index;
}
