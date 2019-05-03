#ifndef TRIANGULATION_MEMBER_H
#define TRIANGULATION_MEMBER_H

#include <data_structures/triangle2d.h>


class Triangulation_member: public Triangle2d
{
public:
    Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList);
    Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList,const bool isActive);
    void setActive();
    void setInactive();
    bool isActive() const;
    size_t getNeighbour(const size_t index) const;
    void setNeighbour(size_t neighbour,const size_t new_index);

protected:
    bool active;
    std::array<size_t,3> adjList;
};

#endif // TRIANGULATION_MEMBER_H
