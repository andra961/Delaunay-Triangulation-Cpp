#include "triangulation_member.h"

Triangulation_member::Triangulation_member(std::array<cg3::Point2Dd,3>& points) : Triangle2d (points)
{
    this->active = true;
}

Triangulation_member::Triangulation_member(std::array<cg3::Point2Dd,3>& points,bool isActive) : Triangle2d (points)
{
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

