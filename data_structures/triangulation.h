#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include <data_structures/triangulation_member.h>
#include <cg3/core/cg3/geometry/2d/point2d.h>

/**
 * @brief class that represents a triangulation,contains a vector of triangulation members and the first triangle represents the bounding triangle
 */

class Triangulation
{
public:
    Triangulation(const Triangle2d& init_triangle,Dag_node* dag_node);
    const Triangulation_member& getTriangle(const size_t index);
    std::vector<Triangulation_member>& getTriangles();
    size_t size();
    void addTriangle(const Triangulation_member triangle);
    void setTriangleActive(const size_t index);
    void setTriangleInactive(const size_t index);
    void setTriangleNeighbour(size_t triangle,size_t neighbour,size_t new_index);
protected:
    std::vector<Triangulation_member> triangles;
};



#endif // TRIANGULATION_H
