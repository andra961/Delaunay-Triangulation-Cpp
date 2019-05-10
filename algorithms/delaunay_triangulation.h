#ifndef DELAUNAY_TRIANGULATION_H
#define DELAUNAY_TRIANGULATION_H

#include <data_structures/triangulation.h>
#include <data_structures/dag_node.h>
#include <algorithms/dag_utilities.h>
#include <utils/delaunay_checker.h>

namespace Delaunay {

    void updateIndexInNeighbour(Triangulation& triangulation,const size_t triangle_index,const size_t neighbour_index,const size_t new_index);
    size_t findIndexInNeighbour(Triangulation& triangulation,const size_t triangle_index,const size_t neighbour_index);
    void flipEdge(Triangulation& triangulation,const size_t triangle_index,const size_t point_index);
    void insertPointInsideAndFlip(Triangulation& triangulation,const Triangulation_member& current_triangle, const cg3::Point2Dd& point);
    void insertPointOnEdgeAndFlip(Triangulation& triangulation,const Triangulation_member& current_triangle,const size_t edge_index,const cg3::Point2Dd& point);
    void incrementalStep(Triangulation& triangulation, Dag_node* dag,const cg3::Point2Dd& point);
    void discardBoundingVertexes(Triangulation& triangulation);
    void getTriangulation(Triangulation& triangulation, Dag_node* dag,const std::vector<cg3::Point2Dd>& points);
}



#endif // DELAUNAY_TRIANGULATION_H
