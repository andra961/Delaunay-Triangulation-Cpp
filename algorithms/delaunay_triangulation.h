#ifndef DELAUNAY_TRIANGULATION_H
#define DELAUNAY_TRIANGULATION_H

#include <data_structures/triangulation.h>

Triangulation getTriangulation(cg3::Point2Dd bounding_point1,cg3::Point2Dd bounding_point2,cg3::Point2Dd bounding_point3,std::vector<cg3::Point2Dd> points);

#endif // DELAUNAY_TRIANGULATION_H
