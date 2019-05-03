#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include <array>
#include <cg3/geometry/2d/point2d.h>
#include <algorithms/triangle_utilities.h>

/**
 * @brief class that represents a triangle;contains an array of 3 points ordered in clockwise or anticlockwise order
 */

class Triangle2d
{
public:
    Triangle2d();
    Triangle2d(std::array<cg3::Point2Dd,3>& points);
    Triangle2d(const cg3::Point2Dd& point1,const cg3::Point2Dd& point2,const cg3::Point2Dd& point3);
    const std::array<cg3::Point2Dd,3>& getPoints() const;
    const cg3::Point2Dd& getPoint(const size_t index) const;
    void setPoints(std::array<cg3::Point2Dd,3>& points);
    void setPoints(cg3::Point2Dd& point1,cg3::Point2Dd& point2,cg3::Point2Dd& point3);

protected:
    std::array<cg3::Point2Dd,3> vertices;
};



#endif // TRIANGLE2D_H
