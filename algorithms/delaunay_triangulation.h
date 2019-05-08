#ifndef DELAUNAY_TRIANGULATION_H
#define DELAUNAY_TRIANGULATION_H

#include <data_structures/triangulation.h>
#include <data_structures/dag_node.h>
#include <cg3/core/cg3/geometry/2d/utils2d.h>
#include <algorithms/triangle_utilities.h>
#include <utils/delaunay_checker.h>

void updateIndexInNeighbour(Triangulation& triangulation,const size_t triangle_index,const size_t neighbour_index,const size_t new_index);
size_t findIndexInNeighbour(Triangulation& triangulation,const size_t triangle_index,const size_t neighbour_index);
void flipEdge(Triangulation& triangulation,const size_t triangle_index,const size_t point_index);
void incrementalStep(Triangulation& triangulation, Dag_node* dag,const cg3::Point2Dd& point);
void getTriangulation(Triangulation& triangulation, Dag_node* dag,const std::vector<cg3::Point2Dd>& points);

#endif // DELAUNAY_TRIANGULATION_H
