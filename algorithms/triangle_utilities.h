#ifndef UTILITIES_H
#define UTILITIES_H

#include <cg3/geometry/2d/point2d.h>
#include <algorithm>
#include <cmath>


double getClockWiseAngle(const cg3::Point2Dd point);

bool comparePointsClockWise(const cg3::Point2Dd point1, const cg3::Point2Dd point2);

void sortTriangleClockWise(std::array<cg3::Point2Dd,3>& points);

void sortTriangleAntiClockWise(std::array<cg3::Point2Dd,3>& points);


#endif // UTILITIES_H
