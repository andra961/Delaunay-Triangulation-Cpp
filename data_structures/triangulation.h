#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include <data_structures/triangle2d.h>
#include <cg3/core/cg3/geometry/2d/point2d.tpp>

/**
 * @brief class that represents a triangulation;
 */

class Triangulation
{
public:
    Triangulation();
    Triangulation(std::array<cg3::Point2Dd,3>& init_triangle_points);
    Triangulation(const Triangle2d& init_triangle);

    Triangle2d getTriangle(const int index) const;
    void eraseTriangle(const int index);
    void addTriangle(std::array<cg3::Point2Dd,3>& triangle_points,int adjacency1,int adjacency2,int adjacency3);

protected:
    std::vector<Triangle2d> triangles;
    std::vector<std::vector<int>> adjacency_lists;
};



#endif // TRIANGULATION_H
