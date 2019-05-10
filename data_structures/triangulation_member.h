#ifndef TRIANGULATION_MEMBER_H
#define TRIANGULATION_MEMBER_H

#include <data_structures/triangle2d.h>
#include <data_structures/dag_node.h>

/**
 * @brief class that represents a triangulation member,extends Triangle2d and contains the adjlist of the triangle,
 * a pointer to his corrispective node in the dag and a bool stating if it is active
 */

class Triangulation_member: public Triangle2d
{
public:
    Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList,Dag_node* dag_node);
    Triangulation_member(const Triangle2d& points,const std::array<size_t,3>& adjList,Dag_node* dag_node,const bool isActive);
    void setActive();
    void setInactive();
    bool isActive() const;
    size_t getNeighbour(const size_t index) const;
    Dag_node* getDagNode() const;
    void setNeighbour(size_t neighbour, size_t new_index);

protected:
    bool active;
    std::array<size_t,3> adjList;
    Dag_node* dag_node;
};

#endif // TRIANGULATION_MEMBER_H
