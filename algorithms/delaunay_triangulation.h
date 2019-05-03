#ifndef DELAUNAY_TRIANGULATION_H
#define DELAUNAY_TRIANGULATION_H

#include <data_structures/triangulation.h>

Triangulation getTriangulation(const cg3::Point2Dd bounding_point1,const cg3::Point2Dd bounding_point2,const cg3::Point2Dd bounding_point3,const std::vector<cg3::Point2Dd> points);

#endif // DELAUNAY_TRIANGULATION_H
