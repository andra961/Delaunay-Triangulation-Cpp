#include "delaunay_triangulation.h"




std::array<Triangle2d,3> splitTriangleIn3(Triangle2d triangle, cg3::Point2Dd point){

    std::array<Triangle2d,3> new_triangles;

    for (size_t i = 0;i < 3;i++) {
        new_triangles[i] = Triangle2d(triangle.getPoint(i),triangle.getPoint((i+1)%3),point);
    }

    return new_triangles;
}

void splitTrianglesIn4(Triangulation_member triangle1,Triangulation_member triangle2,size_t adjEdge1,size_t adjEdge2){

    std::array<cg3::Point2Dd,4> bounding_points;
    bounding_points[0] = triangle1.getPoint(adjEdge1);
    bounding_points[1] = triangle2.getPoint((adjEdge2+2)%3);
    bounding_points[2] = triangle2.getPoint(adjEdge2);
    bounding_points[3] = triangle1.getPoint((adjEdge1+2)%3);
    std::array<size_t,4> bounding_neighbours;
    bounding_neighbours[0] = triangle2.getNeighbour((adjEdge2+1)%3);
    bounding_points[1] = triangle2.getPoint((adjEdge2+2)%3);
    bounding_points[2] = triangle2.getPoint(adjEdge2);
    bounding_points[3] = triangle1.getPoint((adjEdge1+2)%3);
}

size_t findPointIndex(Triangle2d& triangle,cg3::Point2Dd point){
    for (size_t i = 0;i < 3;i++) {
        if(triangle.getPoint(i) == point)
        {
            return i;
        }
    }
}

void updateIndexInNeighbour(Triangulation triangulation,size_t triangle_index,size_t neighbour_index,size_t new_index)
{
    if(neighbour_index != 0){
        for (size_t i = 0;i < 3;i++) {
            if(triangulation.getTriangle(neighbour_index).getNeighbour(i) == triangle_index)
            {
                triangulation.getTriangle(neighbour_index).setNeighbour(i,new_index);
            }
        }
    }

}

size_t findIndexInNeighbour(Triangulation triangulation,size_t triangle_index,size_t neighbour_index)
{
     for (size_t i = 0;i < 3;i++) {
         if(triangulation.getTriangle(neighbour_index).getNeighbour(i) == triangle_index)
         {
            return i;
         }
     }
}


void incrementalStep(Triangulation& triangulation, Dag_node& dag,const cg3::Point2Dd& point){
    Dag_node* current_node = dag.searchTriangle(triangulation,point);
    triangulation.setTriangleInactive(current_node->getIndex());
    Triangulation_member current_triangle = triangulation.getTriangle(current_node->getIndex());

    std::cout << "triangolo trovato : ("<<current_triangle.getPoint(0).x()<<" , "<<current_triangle.getPoint(0).y()<<") "
              <<"("<<current_triangle.getPoint(1).x()<<" , "<<current_triangle.getPoint(1).y()<<") "
             <<"("<<current_triangle.getPoint(2).x()<<" , "<<current_triangle.getPoint(2).y()<<") ";

    size_t current_index = triangulation.size();

    bool isPointOnEdge1 = positionOfPointWithRespectToSegment(current_triangle.getPoint(0),current_triangle.getPoint(1),point) == 0.0;
    bool isPointOnEdge2 = positionOfPointWithRespectToSegment(current_triangle.getPoint(1),current_triangle.getPoint(2),point) == 0.0;
    bool isPointOnEdge3 = positionOfPointWithRespectToSegment(current_triangle.getPoint(2),current_triangle.getPoint(0),point) == 0.0;
    if((!isPointOnEdge1) && (!isPointOnEdge2) && (!isPointOnEdge3))
    {

        std::array<Triangle2d,3> new_triangles = splitTriangleIn3(current_triangle,point);

        std::array<size_t,3> new_triangles_indexes;
        new_triangles_indexes[0] = current_index;
        new_triangles_indexes[1] = current_index+1;
        new_triangles_indexes[2] = current_index+2;

        for (size_t t = 0;t<3;t++) {
            Triangle2d triangle = new_triangles[t];
            size_t reference_index = findPointIndex(triangle,point);
            std::array<size_t,3> adjList;
            adjList[reference_index] = new_triangles_indexes[(t+2)%3];
            adjList[(reference_index+1)%3] = current_triangle.getNeighbour(t);
            adjList[(reference_index+2)%3] = new_triangles_indexes[(t+1)%3];
            updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(t),new_triangles_indexes[t]);
            triangulation.addTriangle(Triangulation_member(triangle,adjList));
            current_node->appendChild(new_triangles_indexes[t]);
        }
    }

    else {

    }
}


Triangulation getTriangulation(const cg3::Point2Dd bounding_point1,const cg3::Point2Dd bounding_point2, const cg3::Point2Dd bounding_point3, const std::vector<cg3::Point2Dd> points){

    Triangulation triangulation = Triangulation(Triangle2d(bounding_point1,bounding_point2,bounding_point3));

    Dag_node dag = Dag_node(0);

    for(size_t i = 0; i < points.size(); i++)
    {
        Dag_node* current_node = dag.searchTriangle(triangulation,points[i]);
        triangulation.setTriangleInactive(current_node->getIndex());
        Triangulation_member current_triangle = triangulation.getTriangle(current_node->getIndex());

        size_t current_index = triangulation.size();

        bool isPointOnEdge1 = positionOfPointWithRespectToSegment(current_triangle.getPoint(0),current_triangle.getPoint(1),points[i]) == 0.0;
        bool isPointOnEdge2 = positionOfPointWithRespectToSegment(current_triangle.getPoint(1),current_triangle.getPoint(2),points[i]) == 0.0;
        bool isPointOnEdge3 = positionOfPointWithRespectToSegment(current_triangle.getPoint(2),current_triangle.getPoint(0),points[i]) == 0.0;
        if((!isPointOnEdge1) && (!isPointOnEdge2) && (!isPointOnEdge3))
        {

            std::array<Triangle2d,3> new_triangles = splitTriangleIn3(current_triangle,points[i]);

            std::array<size_t,3> new_triangles_indexes;
            new_triangles_indexes[0] = current_index;
            new_triangles_indexes[1] = current_index+1;
            new_triangles_indexes[2] = current_index+2;

            for (size_t t = 0;t<3;t++) {
                Triangle2d triangle = new_triangles[t];
                size_t reference_index = findPointIndex(triangle,points[i]);
                std::array<size_t,3> adjList;
                adjList[reference_index] = new_triangles_indexes[(t+2)%3];
                adjList[(reference_index+1)%3] = current_triangle.getNeighbour(t);
                adjList[(reference_index+2)%3] = new_triangles_indexes[(t+1)%3];
                updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(t),new_triangles_indexes[t]);
                triangulation.addTriangle(Triangulation_member(triangle,adjList));
                current_node->appendChild(new_triangles_indexes[t]);
            }
        }

        else {
            size_t edge_index;
            if(isPointOnEdge1){edge_index = 0;}
            else if (isPointOnEdge2){edge_index = 1;}
            else {edge_index = 2;}

            Triangulation_member other_triangle = triangulation.getTriangle(current_triangle.getNeighbour(edge_index));
            size_t currentIndexInOtherTriangle = findIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(edge_index));

            std::array<size_t,4> new_triangles_indexes;
            new_triangles_indexes[0] = current_index;
            new_triangles_indexes[1] = current_index+1;
            new_triangles_indexes[2] = current_index+2;
            new_triangles_indexes[3] = current_index+3;

            Triangle2d current_new1 = Triangle2d(points[i],current_triangle.getPoint(edge_index),current_triangle.getPoint((edge_index+2)%3));
            size_t point_index = findPointIndex(current_new1,points[i]);
            std::array<size_t,3> adjList1;
            adjList1[point_index] = new_triangles_indexes[1];
            adjList1[(point_index+1)%3] = current_triangle.getNeighbour((edge_index+2)%3);
            adjList1[(point_index+2)%3] = new_triangles_indexes[3];
            updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour((edge_index+2)%3),new_triangles_indexes[0]);
            triangulation.addTriangle(Triangulation_member(current_new1,adjList1));
            current_node->appendChild(new_triangles_indexes[0]);


            Triangle2d current_new2 = Triangle2d(points[i],current_triangle.getPoint((edge_index+1)%3),current_triangle.getPoint((edge_index+2)%3));
            point_index = findPointIndex(current_new2,points[i]);
            std::array<size_t,3> adjList2;
            adjList2[point_index] = new_triangles_indexes[2];
            adjList2[(point_index+1)%3] = current_triangle.getNeighbour((edge_index+1)%3);
            adjList2[(point_index+2)%3] = new_triangles_indexes[0];
            updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour((edge_index+1)%3),new_triangles_indexes[1]);
            triangulation.addTriangle(Triangulation_member(current_new2,adjList2));
            current_node->appendChild(new_triangles_indexes[1]);

            Triangle2d current_new3 = Triangle2d(points[i],other_triangle.getPoint(currentIndexInOtherTriangle),other_triangle.getPoint((currentIndexInOtherTriangle+2)%3));
            point_index = findPointIndex(current_new3,points[i]);
            std::array<size_t,3> adjList3;
            adjList1[point_index] = new_triangles_indexes[3];
            adjList1[(point_index+1)%3] = current_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3);
            adjList1[(point_index+2)%3] = new_triangles_indexes[1];
            updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),current_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3),new_triangles_indexes[0]);
            triangulation.addTriangle(Triangulation_member(current_new3,adjList3));
            current_node->appendChild(new_triangles_indexes[2]);


            Triangle2d current_new4 = Triangle2d(points[i],other_triangle.getPoint((currentIndexInOtherTriangle+1)%3),other_triangle.getPoint((currentIndexInOtherTriangle+2)%3));
            point_index = findPointIndex(current_new4,points[i]);
            std::array<size_t,3> adjList4;
            adjList2[point_index] = new_triangles_indexes[0];
            adjList2[(point_index+1)%3] = current_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3);
            adjList2[(point_index+2)%3] = new_triangles_indexes[3];
            updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),other_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3),new_triangles_indexes[1]);
            triangulation.addTriangle(Triangulation_member(current_new4,adjList4));
            current_node->appendChild(new_triangles_indexes[3]);
        }
    }
}
