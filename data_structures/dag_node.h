#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <stddef.h>
#include <vector>
#include <cg3/core/cg3/geometry/2d/point2d.h>
#include <cg3/core/cg3/geometry/2d/utils2d.h>

/**
 * @brief class that represents a node of a dag for the triangulation,each node contains the index of a triangle in the triangulation
 *       and a vector containing the pointers of his children
 */

class Dag_node
{
public:
    Dag_node(const size_t triangle);
    void appendChild(Dag_node* dag_node);
    void setTriangle(const size_t triangle);
    size_t getIndex() const;
    std::vector<Dag_node *>& getChildren();
    size_t numChildren();

protected:
    size_t triangle;
    std::vector<Dag_node *> children;
};

#endif // DAG_NODE_H
