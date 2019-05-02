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
    Triangulation();
    Triangulation(std::array<cg3::Point2Dd,3>& init_triangle_points);
    Triangulation(const Triangulation_member& init_triangle);

    Triangulation_member getTriangle(const size_t index) const;
    size_t addTriangle(std::array<cg3::Point2Dd,3>& triangle_points,size_t adjacency1,size_t adjacency2,size_t adjacency3);
    size_t addTriangle(Triangle2d& triangle_points,size_t adjacency1,size_t adjacency2,size_t adjacency3);
    std::vector<size_t> getNeighbours(const size_t index) const;
    void setTriangleActive(const size_t index);
    void setTriangleInactive(const size_t index);

protected:
    std::vector<Triangulation_member> triangles;
    std::vector<std::vector<size_t>> adjacency_lists;
};



#endif // TRIANGULATION_H
