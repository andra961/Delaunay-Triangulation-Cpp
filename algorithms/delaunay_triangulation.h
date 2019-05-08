#ifndef DELAUNAY_TRIANGULATION_H
#define DELAUNAY_TRIANGULATION_H

#include <data_structures/triangulation.h>
#include <data_structures/dag_node.h>
#include <cg3/core/cg3/geometry/2d/utils2d.h>
#include <algorithms/triangle_utilities.h>
#include <utils/delaunay_checker.h>

std::array<Triangle2d,3> splitTriangleIn3(Triangle2d& triangle,const cg3::Point2Dd& point);
size_t findPointIndex(Triangle2d& triangle,const cg3::Point2Dd& point);
void updateIndexInNeighbour(Triangulation& triangulation,size_t triangle_index,size_t neighbour_index,size_t new_index);
size_t findIndexInNeighbour(Triangulation& triangulation,size_t triangle_index,size_t neighbour_index);
void flipEdge(Triangulation& triangulation,size_t triangle_index,size_t point_index);
void incrementalStep(Triangulation& triangulation, Dag_node* dag,const cg3::Point2Dd& point);
void getTriangulation(Triangulation& triangulation, Dag_node* dag,const std::vector<cg3::Point2Dd>& points);

#endif // DELAUNAY_TRIANGULATION_H
