#ifndef UTILITIES_H
#define UTILITIES_H

#include <cg3/geometry/2d/point2d.h>
#include <algorithm>
#include <cmath>
#include <data_structures/dag_node.h>
#include <data_structures/triangulation.h>

namespace Dag {

    Dag_node* searchTriangle(Triangulation& triangulation,Dag_node* dag,const cg3::Point2Dd& point);

    void deleteDag(Dag_node* dag);

    void addNodeToDeleteRec(Dag_node* dag,std::set<Dag_node*>& allNodes);
}


#endif // UTILITIES_H
