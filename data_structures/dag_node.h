#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <stddef.h>
#include <vector>
#include <cg3/core/cg3/geometry/2d/point2d.h>
#include <cg3/core/cg3/geometry/2d/utils2d.h>

class Dag_node
{
public:
    Dag_node();
    Dag_node(const size_t triangle);
    Dag_node* appendChild(const size_t);
    void setTriangle(const size_t triangle);
    size_t getIndex() const;
    std::vector<Dag_node *> getChildren() const;

protected:
    size_t triangle;
    std::vector<Dag_node *> children;
};

#endif // DAG_NODE_H
