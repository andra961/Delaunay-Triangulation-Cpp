#ifndef TRIANGULATION_MEMBER_H
#define TRIANGULATION_MEMBER_H

#include <data_structures/triangle2d.h>


class Triangulation_member: public Triangle2d
{
public:
    Triangulation_member(std::array<cg3::Point2Dd,3>& points);
    Triangulation_member(std::array<cg3::Point2Dd,3>& points,bool isActive);
    Triangulation_member(Triangle2d& points);
    Triangulation_member(Triangle2d& points,bool isActive);
    void setActive();
    void setInactive();
    bool isActive() const;

protected:
    bool active;
};

#endif // TRIANGULATION_MEMBER_H
