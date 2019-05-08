#include "delaunay_triangulation.h"

void updateIndexInNeighbour(Triangulation& triangulation,const size_t triangle_index,const size_t neighbour_index,const size_t new_index)
{
    if(neighbour_index != 0){
        Triangulation_member neighbour = triangulation.getTriangle(neighbour_index);
        for (size_t i = 0;i < 3;i++) {
            if(neighbour.getNeighbour(i) == triangle_index)
            {
                triangulation.setTriangleNeighbour(neighbour_index,i,new_index);
            }
        }
    }

}

size_t findIndexInNeighbour(Triangulation& triangulation,const size_t triangle_index,const size_t neighbour_index)
{
     for (size_t i = 0;i < 3;i++) {
         if(triangulation.getTriangle(neighbour_index).getNeighbour(i) == triangle_index)
         {
            return i;
         }
     }
     return 3;
}

void flipEdge(Triangulation& triangulation,const size_t triangle_index,const size_t point_index){

    Triangulation_member triangle = triangulation.getTriangle(triangle_index);
    if(triangle.getNeighbour((point_index+1)%3) != 0){
        Triangulation_member adjTriangle = triangulation.getTriangle(triangle.getNeighbour((point_index+1)%3));

        size_t adj_point_index = ((findIndexInNeighbour(triangulation,triangle_index,triangle.getNeighbour((point_index+1)%3))+2)%3);
        if (isPointLyingInCircle(triangle.getPoint(0),triangle.getPoint(1),triangle.getPoint(2),adjTriangle.getPoint(adj_point_index),false)) {

            triangulation.setTriangleInactive(triangle_index);
            triangulation.setTriangleInactive(triangle.getNeighbour((point_index+1)%3));
            size_t current_index = triangulation.size();
            size_t newTriangleIndex1 = current_index;
            size_t newTriangleIndex2 = current_index+1;

            Triangle2d new_triangle1 = Triangle2d(triangle.getPoint(point_index),triangle.getPoint((point_index+1)%3),adjTriangle.getPoint(adj_point_index));
            std::array<size_t,3> adjList1;
            adjList1[0] = triangle.getNeighbour(point_index);
            adjList1[1] = adjTriangle.getNeighbour((adj_point_index+2)%3);
            adjList1[2] = newTriangleIndex2;
            updateIndexInNeighbour(triangulation,triangle_index,triangle.getNeighbour(point_index),newTriangleIndex1);
            updateIndexInNeighbour(triangulation,triangle.getNeighbour((point_index+1)%3),adjTriangle.getNeighbour((adj_point_index+2)%3),newTriangleIndex1);
            Dag_node* dag1 = new Dag_node(newTriangleIndex1);
            triangulation.addTriangle(Triangulation_member(new_triangle1,adjList1,dag1));
            triangle.getDagNode()->appendChild(dag1);
            adjTriangle.getDagNode()->appendChild(dag1);



            Triangle2d new_triangle2 = Triangle2d(triangle.getPoint(point_index),adjTriangle.getPoint(adj_point_index),triangle.getPoint((point_index+2)%3));
            std::array<size_t,3> adjList2;
            adjList2[0] = newTriangleIndex1;
            adjList2[1] = adjTriangle.getNeighbour(adj_point_index);
            adjList2[2] = triangle.getNeighbour((point_index+2)%3);
            updateIndexInNeighbour(triangulation,triangle_index,triangle.getNeighbour((point_index+2)%3),newTriangleIndex2);
            updateIndexInNeighbour(triangulation,triangle.getNeighbour((point_index+1)%3),adjTriangle.getNeighbour(adj_point_index),newTriangleIndex2);
            Dag_node* dag2 = new Dag_node(newTriangleIndex2);
            triangulation.addTriangle(Triangulation_member(new_triangle2,adjList2,dag2));
            adjTriangle.getDagNode()->appendChild(dag2);
            triangle.getDagNode()->appendChild(dag2);

            flipEdge(triangulation,newTriangleIndex1,0);
            flipEdge(triangulation,newTriangleIndex2,0);
        }
    }
}


void incrementalStep(Triangulation& triangulation, Dag_node* dag,const cg3::Point2Dd& point){
    Dag_node* current_node = searchTriangle(triangulation,dag,point);
    triangulation.setTriangleInactive(current_node->getIndex());



    Triangulation_member current_triangle = triangulation.getTriangle(current_node->getIndex());

    if(point == current_triangle.getPoint(0) || point == current_triangle.getPoint(1) || point == current_triangle.getPoint(2))
    {}
    else {


        size_t current_index = triangulation.size();

        bool isPointOnEdge1 = positionOfPointWithRespectToSegment(current_triangle.getPoint(0),current_triangle.getPoint(1),point) == 0.0;
        bool isPointOnEdge2 = positionOfPointWithRespectToSegment(current_triangle.getPoint(1),current_triangle.getPoint(2),point) == 0.0;
        bool isPointOnEdge3 = positionOfPointWithRespectToSegment(current_triangle.getPoint(2),current_triangle.getPoint(0),point) == 0.0;
        if((!isPointOnEdge1) && (!isPointOnEdge2) && (!isPointOnEdge3))
        {

            std::array<size_t,3> new_triangles_indexes;
            new_triangles_indexes[0] = current_index;
            new_triangles_indexes[1] = current_index+1;
            new_triangles_indexes[2] = current_index+2;
            std::array<size_t,3> adjList;

            for (size_t i = 0;i<3;i++) {
                adjList[0] = new_triangles_indexes[(i+2)%3];
                adjList[1] = current_triangle.getNeighbour(i);
                adjList[2] = new_triangles_indexes[(i+1)%3];
                updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(i),new_triangles_indexes[i]);
                Dag_node* dag = new Dag_node(new_triangles_indexes[i]);
                triangulation.addTriangle(Triangulation_member(Triangle2d(point,current_triangle.getPoint(i),current_triangle.getPoint((i+1)%3)),adjList,dag));
                current_node->appendChild(dag);             

            }
            for (size_t i = 0;i < 3;i++) {
                flipEdge(triangulation,new_triangles_indexes[i],0);
            }

        }

        else {
            size_t edge_index;
            if(isPointOnEdge1){edge_index = 0;}
            else if (isPointOnEdge2){edge_index = 1;}
            else {edge_index = 2;}

            Triangulation_member other_triangle = triangulation.getTriangle(current_triangle.getNeighbour(edge_index));


            triangulation.setTriangleInactive(current_triangle.getNeighbour(edge_index));
            size_t currentIndexInOtherTriangle = findIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(edge_index));

            std::array<size_t,4> new_triangles_indexes;
            new_triangles_indexes[0] = current_index;
            new_triangles_indexes[1] = current_index+1;
            new_triangles_indexes[2] = current_index+2;
            new_triangles_indexes[3] = current_index+3;

            Triangle2d current_new1 = Triangle2d(point,current_triangle.getPoint((edge_index+2)%3),current_triangle.getPoint(edge_index));
            std::array<size_t,3> adjList1;
            adjList1[0] = new_triangles_indexes[1];
            adjList1[1] = current_triangle.getNeighbour((edge_index+2)%3);
            adjList1[2] = new_triangles_indexes[3];
            updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour((edge_index+2)%3),new_triangles_indexes[0]);
            Dag_node* dag1 = new Dag_node(new_triangles_indexes[0]);
            triangulation.addTriangle(Triangulation_member(current_new1,adjList1,dag1));
            current_node->appendChild(dag1);




            Triangle2d current_new2 = Triangle2d(point,current_triangle.getPoint((edge_index+1)%3),current_triangle.getPoint((edge_index+2)%3));
            std::array<size_t,3> adjList2;
            adjList2[0] = new_triangles_indexes[2];
            adjList2[1] = current_triangle.getNeighbour((edge_index+1)%3);
            adjList2[2] = new_triangles_indexes[0];
            updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour((edge_index+1)%3),new_triangles_indexes[1]);
            Dag_node* dag2 = new Dag_node(new_triangles_indexes[1]);
            triangulation.addTriangle(Triangulation_member(current_new2,adjList2,dag2));
            current_node->appendChild(dag2);



            Dag_node* current_node2 = other_triangle.getDagNode();


            Triangle2d current_new3 = Triangle2d(point,other_triangle.getPoint((currentIndexInOtherTriangle+2)%3),other_triangle.getPoint(currentIndexInOtherTriangle));
            std::array<size_t,3> adjList3;
            adjList3[0] = new_triangles_indexes[3];
            adjList3[1] = other_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3);
            adjList3[2] = new_triangles_indexes[1];
            updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),other_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3),new_triangles_indexes[2]);
            Dag_node* dag3 = new Dag_node(new_triangles_indexes[2]);
            triangulation.addTriangle(Triangulation_member(current_new3,adjList3,dag3));
            current_node2->appendChild(dag3);



            Triangle2d current_new4 = Triangle2d(point,other_triangle.getPoint((currentIndexInOtherTriangle+1)%3),other_triangle.getPoint((currentIndexInOtherTriangle+2)%3));
            std::array<size_t,3> adjList4;
            adjList4[0] = new_triangles_indexes[0];
            adjList4[1] = other_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3);
            adjList4[2] = new_triangles_indexes[2];
            updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),other_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3),new_triangles_indexes[3]);
            Dag_node* dag4 = new Dag_node(new_triangles_indexes[3]);
            triangulation.addTriangle(Triangulation_member(current_new4,adjList4,dag4));
            current_node2->appendChild(dag4);
            flipEdge(triangulation,new_triangles_indexes[0],0);
            flipEdge(triangulation,new_triangles_indexes[1],0);
            flipEdge(triangulation,new_triangles_indexes[2],0);
            flipEdge(triangulation,new_triangles_indexes[3],0);
        }
    }
}


void getTriangulation(Triangulation& triangulation, Dag_node* dag,const std::vector<cg3::Point2Dd>& points){
    std::vector<cg3::Point2Dd> shuffled_points = points;
    std::random_shuffle(shuffled_points.begin(),shuffled_points.end());
    for (size_t i = 0; i< points.size();i++) {
        incrementalStep(triangulation,dag,points[i]);
    }
    Triangle2d bounding_triangle = triangulation.getTriangle(0);
    for (size_t i = 0; i< triangulation.size();i++) {
        if(triangulation.getTriangle(i).isActive()){
            Triangle2d triangle = triangulation.getTriangle(i);
            for (size_t j = 0;j<3;j++) {
                if(triangle.getPoint(j) == bounding_triangle.getPoint(0) || triangle.getPoint(j) == bounding_triangle.getPoint(1) || triangle.getPoint(j) == bounding_triangle.getPoint(2)){
                    triangulation.setTriangleInactive(i);
                }
            }
        }
    }

}
