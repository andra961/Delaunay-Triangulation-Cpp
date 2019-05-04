#ifndef DELAUNAY_TRIANGULATION_H
#define DELAUNAY_TRIANGULATION_H

#include <data_structures/triangulation.h>
#include <data_structures/dag_node.h>
#include <cg3/core/cg3/geometry/2d/utils2d.h>

std::array<Triangle2d,3> splitTriangleIn3(Triangle2d triangle, cg3::Point2Dd point);
void incrementalStep(Triangulation& triangulation, Dag_node& dag,const cg3::Point2Dd& point);
Triangulation getTriangulation(const cg3::Point2Dd bounding_point1,const cg3::Point2Dd bounding_point2,const cg3::Point2Dd bounding_point3,const std::vector<cg3::Point2Dd> points);

#endif // DELAUNAY_TRIANGULATION_H
