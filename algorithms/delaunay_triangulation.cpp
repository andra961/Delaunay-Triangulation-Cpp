#include "delaunay_triangulation.h"

#include <data_structures/dag_node.h>
#include <cg3/core/cg3/geometry/2d/utils2d.h>

std::array<Triangle2d,3> divideTriangleIn3(Triangle2d triangle, cg3::Point2Dd point){

    std::array<Triangle2d,3> new_triangles;

    cg3::Point2Dd new_point1 = cg3::Point2Dd(triangle.getPoints()[0]);
    cg3::Point2Dd new_point2 = cg3::Point2Dd(triangle.getPoints()[1]);
    Triangle2d new_triangle = Triangle2d(new_point1,new_point2,point);

    new_triangles[0] = new_triangle;

    new_point1 = cg3::Point2Dd(triangle.getPoints()[1]);
    new_point2 = cg3::Point2Dd(triangle.getPoints()[2]);
    new_triangle = Triangle2d(new_point1,new_point2,point);

    new_triangles[1] = new_triangle;

    new_point1 = cg3::Point2Dd(triangle.getPoints()[2]);
    new_point2 = cg3::Point2Dd(triangle.getPoints()[0]);
    new_triangle = Triangle2d(new_point1,new_point2,point);

    new_triangles[2] = new_triangle;

    return new_triangles;
}


Triangulation getTriangulation(cg3::Point2Dd bounding_point1,cg3::Point2Dd bounding_point2,cg3::Point2Dd bounding_point3,std::vector<cg3::Point2Dd> points){

    Triangulation triangulation = Triangulation();
    Triangle2d bounding_triangle = Triangle2d(bounding_point1,bounding_point2,bounding_point3);
    triangulation.addTriangle(bounding_triangle,0,0,0);
    Dag_node dag = Dag_node(1);

    for(size_t i = 0; i < points.size(); i++)
    {
        Dag_node* current_node = dag.searchTriangle(triangulation,points[i]);
        triangulation.getTriangle(current_node->getIndex()).setInactive();
        Triangle2d current_triangle = triangulation.getTriangle(current_node->getIndex());
        if(positionOfPointWithRespectToSegment(current_triangle.getPoints()[0],current_triangle.getPoints()[1],points[i]) != 0.0 &&
             positionOfPointWithRespectToSegment(current_triangle.getPoints()[1],current_triangle.getPoints()[2],points[i]) != 0.0 &&
                positionOfPointWithRespectToSegment(current_triangle.getPoints()[2],current_triangle.getPoints()[0],points[i]) != 0.0)
        {

            std::array<Triangle2d,3> new_triangles = divideTriangleIn3(current_triangle,points[i]);



            size_t new_index = triangulation.addTriangle(new_triangles[0],0,0,0);

        }
    }
}
