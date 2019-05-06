#include "delaunay_triangulation.h"




std::array<Triangle2d,3> splitTriangleIn3(Triangle2d& triangle,const cg3::Point2Dd& point){

    std::array<Triangle2d,3> new_triangles;

    for (size_t i = 0;i < 3;i++) {
        new_triangles[i] = Triangle2d(triangle.getPoint(i),triangle.getPoint((i+1)%3),point);
    }

    return new_triangles;
}

size_t findPointIndex(Triangle2d& triangle,const cg3::Point2Dd& point){
    for (size_t i = 0;i < 3;i++) {
        if(triangle.getPoint(i) == point)
        {
            return i;
        }
    }
}

void updateIndexInNeighbour(Triangulation& triangulation,size_t triangle_index,size_t neighbour_index,size_t new_index)
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

size_t findIndexInNeighbour(Triangulation& triangulation,size_t triangle_index,size_t neighbour_index)
{
     for (size_t i = 0;i < 3;i++) {
         if(triangulation.getTriangle(neighbour_index).getNeighbour(i) == triangle_index)
         {
            return i;
         }
     }
}


void incrementalStep(Triangulation& triangulation, Dag_node* dag,const cg3::Point2Dd& point){
    Dag_node* current_node = searchTriangle(triangulation,dag,point);
    triangulation.setTriangleInactive(current_node->getIndex());

    //std::cout << current_node->getIndex();

    Triangulation_member current_triangle = triangulation.getTriangle(current_node->getIndex());

    if(point == current_triangle.getPoint(0) || point == current_triangle.getPoint(1) || point == current_triangle.getPoint(2))
    {}
    else {
        /*std::cout << "triangolo trovato : ("<<current_triangle.getPoint(0).x()<<" , "<<current_triangle.getPoint(0).y()<<") "
                  <<"("<<current_triangle.getPoint(1).x()<<" , "<<current_triangle.getPoint(1).y()<<") "
                <<"("<<current_triangle.getPoint(2).x()<<" , "<<current_triangle.getPoint(2).y()<<") ";*/

        size_t current_index = triangulation.size();

        bool isPointOnEdge1 = positionOfPointWithRespectToSegment(current_triangle.getPoint(0),current_triangle.getPoint(1),point) == 0.0;
        bool isPointOnEdge2 = positionOfPointWithRespectToSegment(current_triangle.getPoint(1),current_triangle.getPoint(2),point) == 0.0;
        bool isPointOnEdge3 = positionOfPointWithRespectToSegment(current_triangle.getPoint(2),current_triangle.getPoint(0),point) == 0.0;
        if((!isPointOnEdge1) && (!isPointOnEdge2) && (!isPointOnEdge3))
        {

            //std::array<Triangle2d,3> new_triangles = splitTriangleIn3(current_triangle,point);
            std::array<Triangle2d,3> new_triangles;

            for (size_t i = 0;i < 3;i++) {
                new_triangles[i] = Triangle2d(current_triangle.getPoint(i),current_triangle.getPoint((i+1)%3),point);
            }


            std::array<size_t,3> new_triangles_indexes;
            new_triangles_indexes[0] = current_index;
            new_triangles_indexes[1] = current_index+1;
            new_triangles_indexes[2] = current_index+2;

            for (size_t t = 0;t<3;t++) {
                size_t reference_index = findPointIndex(new_triangles[t],point);
                std::array<size_t,3> adjList;
                adjList[reference_index] = new_triangles_indexes[(t+1)%3];
                adjList[(reference_index+1)%3] = current_triangle.getNeighbour(t);
                adjList[(reference_index+2)%3] = new_triangles_indexes[(t+2)%3];
                updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(t),new_triangles_indexes[t]);
                triangulation.addTriangle(Triangulation_member(new_triangles[t],adjList,current_node->appendChild(new_triangles_indexes[t])));

                /*std::cout << "  triangolo creato n "  << new_triangles_indexes[t] <<" "<< reference_index << " : ("<<new1.getPoint(0).x()<<" , "<<new1.getPoint(0).y()<<") "
                          <<"("<<new1.getPoint(1).x()<<" , "<<new1.getPoint(1).y()<<") "
                        <<"("<<new1.getPoint(2).x()<<" , "<<new1.getPoint(2).y()<<") lista adiacenza " << adjList[0] << "  " << adjList[1] << "  " << adjList[2];*/
            }

        }

        else {
            size_t edge_index;
            if(isPointOnEdge1){edge_index = 0;}
            else if (isPointOnEdge2){edge_index = 1;}
            else {edge_index = 2;}

            //std::cout << edge_index;

            Triangulation_member other_triangle = triangulation.getTriangle(current_triangle.getNeighbour(edge_index));

            /*std::cout << "triangolo trovato : ("<<other_triangle.getPoint(0).x()<<" , "<<other_triangle.getPoint(0).y()<<") "
                      <<"("<<other_triangle.getPoint(1).x()<<" , "<<other_triangle.getPoint(1).y()<<") "
                    <<"("<<other_triangle.getPoint(2).x()<<" , "<<other_triangle.getPoint(2).y()<<") ";*/
            triangulation.setTriangleInactive(current_triangle.getNeighbour(edge_index));
            size_t currentIndexInOtherTriangle = findIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),current_node->getIndex());
            //std::cout << currentIndexInOtherTriangle;

            std::array<size_t,4> new_triangles_indexes;
            new_triangles_indexes[0] = current_index;
            new_triangles_indexes[1] = current_index+1;
            new_triangles_indexes[2] = current_index+2;
            new_triangles_indexes[3] = current_index+3;

            Triangle2d current_new1 = Triangle2d(point,current_triangle.getPoint(edge_index),current_triangle.getPoint((edge_index+2)%3));
            size_t point_index = findPointIndex(current_new1,point);
            std::array<size_t,3> adjList1;
            adjList1[point_index] = new_triangles_indexes[1];
            adjList1[(point_index+1)%3] = current_triangle.getNeighbour((edge_index+2)%3);
            adjList1[(point_index+2)%3] = new_triangles_indexes[3];
            updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour((edge_index+2)%3),new_triangles_indexes[0]);
            triangulation.addTriangle(Triangulation_member(current_new1,adjList1,current_node->appendChild(new_triangles_indexes[0])));

            /*std::cout << "triangolo 1 : ("<<current_new1.getPoint(0).x()<<" , "<<current_new1.getPoint(0).y()<<") "
                              <<"("<<current_new1.getPoint(1).x()<<" , "<<current_new1.getPoint(1).y()<<") "
                            <<"("<<current_new1.getPoint(2).x()<<" , "<<current_new1.getPoint(2).y()<<") ";*/

            Triangle2d current_new2 = Triangle2d(point,current_triangle.getPoint((edge_index+1)%3),current_triangle.getPoint((edge_index+2)%3));
            point_index = findPointIndex(current_new2,point);
            std::array<size_t,3> adjList2;
            adjList2[point_index] = new_triangles_indexes[2];
            adjList2[(point_index+1)%3] = current_triangle.getNeighbour((edge_index+1)%3);
            adjList2[(point_index+2)%3] = new_triangles_indexes[0];
            updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour((edge_index+1)%3),new_triangles_indexes[1]);
            triangulation.addTriangle(Triangulation_member(current_new2,adjList2,current_node->appendChild(new_triangles_indexes[1])));

            Dag_node* current_node2 = other_triangle.getDagNode();

            /*std::cout << "triangolo 2 : ("<<current_new2.getPoint(0).x()<<" , "<<current_new2.getPoint(0).y()<<") "
                              <<"("<<current_new2.getPoint(1).x()<<" , "<<current_new2.getPoint(1).y()<<") "
                            <<"("<<current_new2.getPoint(2).x()<<" , "<<current_new2.getPoint(2).y()<<") ";*/

            Triangle2d current_new3 = Triangle2d(point,other_triangle.getPoint(currentIndexInOtherTriangle),other_triangle.getPoint((currentIndexInOtherTriangle+1)%3));
            point_index = findPointIndex(current_new3,point);
            std::array<size_t,3> adjList3;
            adjList1[point_index] = new_triangles_indexes[3];
            adjList1[(point_index+1)%3] = current_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3);
            adjList1[(point_index+2)%3] = new_triangles_indexes[1];
            updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),current_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3),new_triangles_indexes[0]);
            triangulation.addTriangle(Triangulation_member(current_new3,adjList3,current_node2->appendChild(new_triangles_indexes[2])));

            /*std::cout << "triangolo 3 : ("<<current_new3.getPoint(0).x()<<" , "<<current_new3.getPoint(0).y()<<") "
                              <<"("<<current_new3.getPoint(1).x()<<" , "<<current_new3.getPoint(1).y()<<") "
                            <<"("<<current_new3.getPoint(2).x()<<" , "<<current_new3.getPoint(2).y()<<") ";*/


            Triangle2d current_new4 = Triangle2d(point,other_triangle.getPoint((currentIndexInOtherTriangle+1)%3),other_triangle.getPoint((currentIndexInOtherTriangle+2)%3));
            point_index = findPointIndex(current_new4,point);
            std::array<size_t,3> adjList4;
            adjList2[point_index] = new_triangles_indexes[0];
            adjList2[(point_index+1)%3] = current_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3);
            adjList2[(point_index+2)%3] = new_triangles_indexes[3];
            updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),other_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3),new_triangles_indexes[1]);
            triangulation.addTriangle(Triangulation_member(current_new4,adjList4,current_node2->appendChild(new_triangles_indexes[3])));

            /*std::cout << "triangolo 4 : ("<<current_new4.getPoint(0).x()<<" , "<<current_new4.getPoint(0).y()<<") "
                              <<"("<<current_new4.getPoint(1).x()<<" , "<<current_new4.getPoint(1).y()<<") "
                            <<"("<<current_new4.getPoint(2).x()<<" , "<<current_new4.getPoint(2).y()<<") ";*/
        }
    }
}


void getTriangulation(Triangulation& triangulation, Dag_node* dag,const std::vector<cg3::Point2Dd>& points){
    for (size_t i = 0; i< points.size();i++) {
        incrementalStep(triangulation,dag,points[i]);
    }
}
