#include "delaunay_triangulation.h"

#include <data_structures/dag_node.h>
#include <cg3/core/cg3/geometry/2d/utils2d.h>


std::array<Triangle2d,3> splitTriangleIn3(Triangle2d triangle, cg3::Point2Dd point){

    std::array<Triangle2d,3> new_triangles;

    for (size_t i = 0;i < 3;i++) {
        new_triangles[i] = Triangle2d(triangle.getPoint(i),triangle.getPoint((i+1)%3),point);
    }

    return new_triangles;
}

size_t findPointIndex(Triangle2d& triangle,cg3::Point2Dd point){
    for (size_t i = 0;i < 3;i++) {
        if(triangle.getPoint(i) == point)
        {
            return i;
        }
    }
}

void updateIndexInNeighbour(Triangulation triangulation,size_t triangle,size_t neighbour,size_t new_index)
{
    for (size_t i = 0;i < 3;i++) {
        if(triangulation.getTriangle(neighbour).getNeighbour(i) == triangle)
        {
            triangulation.getTriangle(neighbour).setNeighbour(i,new_index);
        }
    }
}


Triangulation getTriangulation(const cg3::Point2Dd bounding_point1,const cg3::Point2Dd bounding_point2, const cg3::Point2Dd bounding_point3, const std::vector<cg3::Point2Dd> points){

    Triangulation triangulation = Triangulation(Triangle2d(bounding_point1,bounding_point2,bounding_point3));

    Dag_node dag = Dag_node(0);

    for(size_t i = 0; i < points.size(); i++)
    {
        Dag_node* current_node = dag.searchTriangle(triangulation,points[i]);
        triangulation.setTriangleInactive(i);
        Triangulation_member current_triangle = triangulation.getTriangle(current_node->getIndex());

        size_t current_index = triangulation.size();

        if(positionOfPointWithRespectToSegment(current_triangle.getPoint(0),current_triangle.getPoint(1),points[i]) != 0.0 &&
             positionOfPointWithRespectToSegment(current_triangle.getPoint(1),current_triangle.getPoint(2),points[i]) != 0.0 &&
                positionOfPointWithRespectToSegment(current_triangle.getPoint(2),current_triangle.getPoint(0),points[i]) != 0.0)
        {

            std::array<Triangle2d,3> new_triangles = splitTriangleIn3(current_triangle,points[i]);

            std::array<size_t,3> new_triangles_indexes;
            new_triangles_indexes[0] = current_index;
            new_triangles_indexes[1] = current_index+1;
            new_triangles_indexes[2] = current_index+2;

            for (size_t j = 0;j<3;j++) {
                Triangle2d triangle = new_triangles[j];
                size_t reference_index = findPointIndex(triangle,points[i]);
                std::array<size_t,3> adjList;
                adjList[reference_index] = new_triangles_indexes[(j+2)%3];
                adjList[(reference_index+1)%3] = current_triangle.getNeighbour(j);
                adjList[(reference_index+2)%3] = new_triangles_indexes[(j+1)%3];
                triangulation.addTriangle(Triangulation_member(triangle,adjList));
                updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(j),new_triangles_indexes[j]);
                current_node->appendChild(new_triangles_indexes[0]);
                current_node->appendChild(new_triangles_indexes[1]);
                current_node->appendChild(new_triangles_indexes[2]);
            }
        }
    }
}
