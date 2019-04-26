#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include <array>
#include <cg3/geometry/2d/point2d.h>
#include <algorithms/triangle_utilities.h>

class Triangle2d
{
public:
    Triangle2d();
    Triangle2d(std::array<cg3::Point2Dd,3>& points,bool clockWiseOrAntiClockWise);

    //const std::array<cg3::Point2Dd,3> getPoints() const;
    //void setPoints(const std::array<cg3::Point2Dd,3>);

protected:
    std::array<cg3::Point2Dd,3> vertexes;
};



#endif // TRIANGLE2D_H
