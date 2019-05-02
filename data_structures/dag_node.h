#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <stddef.h>
#include <vector>
#include <cg3/core/cg3/geometry/2d/point2d.h>
#include <cg3/core/cg3/geometry/2d/utils2d.h>
#include <data_structures/triangulation.h>

class Dag_node
{
public:
    Dag_node();
    Dag_node(const size_t triangle);
    void appendChild(const size_t);
    void setTriangle(const size_t triangle);
    size_t getIndex() const;
    Dag_node* searchTriangle(const Triangulation& triangulation,const cg3::Point2Dd point);
protected:
    size_t triangle;
    std::vector<Dag_node *> children;
};

#endif // DAG_NODE_H
