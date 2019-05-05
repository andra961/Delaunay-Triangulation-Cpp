#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include <data_structures/triangulation_member.h>
#include <cg3/core/cg3/geometry/2d/point2d.h>

/**
 * @brief class that represents a triangulation;
 */

class Triangulation
{
public:
    Triangulation(const Triangle2d& init_triangle,Dag_node* dag_node);
    Triangulation_member getTriangle(const size_t index) const;
    size_t size();
    void addTriangle(const Triangulation_member triangle);
    void setTriangleActive(const size_t index);
    void setTriangleInactive(const size_t index);

protected:
    std::vector<Triangulation_member> triangles;
};



#endif // TRIANGULATION_H
