#include "triangulation_member.h"

Triangulation_member::Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList) : Triangle2d (points)
{
    this->adjList = adjList;
}

Triangulation_member::Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList,const bool isActive) : Triangle2d (points)
{
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

void Triangulation_member::setNeighbour(const size_t neighbour,const size_t new_index){
    this->adjList[neighbour] = new_index;
}
