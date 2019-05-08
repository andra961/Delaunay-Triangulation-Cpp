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
        Triangulation_member neighbour = triangulation.getTriangle(neighbour_index);
        for (size_t i = 0;i < 3;i++) {
            if(neighbour.getNeighbour(i) == triangle_index)
            {
                triangulation.setTriangleNeighbour(neighbour_index,i,new_index);
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

void flipEdge(Triangulation& triangulation,size_t triangle_index,size_t point_index){

    Triangulation_member triangle = triangulation.getTriangle(triangle_index);
    if(triangle.getNeighbour((point_index+1)%3) != 0){
        Triangulation_member adjTriangle = triangulation.getTriangle(triangle.getNeighbour((point_index+1)%3));
        /*std::cout << "triangolo trovato : ("<<triangle.getPoint(0).x()<<" , "<<triangle.getPoint(0).y()<<") "
                  <<"("<<triangle.getPoint(1).x()<<" , "<<triangle.getPoint(1).y()<<") "
                <<"("<<triangle.getPoint(2).x()<<" , "<<triangle.getPoint(2).y()<<") " << triangle.getPoint(point_index);
        std::cout << "triangolo adiacente trovato : ("<<adjTriangle.getPoint(0).x()<<" , "<<adjTriangle.getPoint(0).y()<<") "
                  <<"("<<adjTriangle.getPoint(1).x()<<" , "<<adjTriangle.getPoint(1).y()<<") "
                <<"("<<adjTriangle.getPoint(2).x()<<" , "<<adjTriangle.getPoint(2).y()<<") ";*/
        
        
        size_t adj_point_index = ((findIndexInNeighbour(triangulation,triangle_index,triangle.getNeighbour((point_index+1)%3))+2)%3);
        if (isPointLyingInCircle(triangle.getPoint(0),triangle.getPoint(1),triangle.getPoint(2),adjTriangle.getPoint(adj_point_index),false)) {

            //std::cout << "iniziato";
            triangulation.setTriangleInactive(triangle_index);
            triangulation.setTriangleInactive(triangle.getNeighbour((point_index+1)%3));
            size_t current_index = triangulation.size();
            size_t newTriangleIndex1 = current_index;
            size_t newTriangleIndex2 = current_index+1;

            Triangle2d new_triangle1 = Triangle2d(triangle.getPoint(point_index),triangle.getPoint((point_index+1)%3),adjTriangle.getPoint(adj_point_index));
            std::array<size_t,3> adjList1;
            size_t pointInTriangle1 = findPointIndex(new_triangle1,triangle.getPoint(point_index));
            adjList1[pointInTriangle1] = triangle.getNeighbour(point_index);
            adjList1[(pointInTriangle1+1)%3] = adjTriangle.getNeighbour((adj_point_index+2)%3);
            adjList1[(pointInTriangle1+2)%3] = newTriangleIndex2;
            updateIndexInNeighbour(triangulation,triangle_index,triangle.getNeighbour(point_index),newTriangleIndex1);
            updateIndexInNeighbour(triangulation,triangle.getNeighbour((point_index+1)%3),adjTriangle.getNeighbour((adj_point_index+2)%3),newTriangleIndex1);
            Dag_node* dag1 = new Dag_node(newTriangleIndex1);
            triangulation.addTriangle(Triangulation_member(new_triangle1,adjList1,dag1));
            triangle.getDagNode()->appendChild(dag1);
            adjTriangle.getDagNode()->appendChild(dag1);



            Triangle2d new_triangle2 = Triangle2d(triangle.getPoint(point_index),adjTriangle.getPoint(adj_point_index),triangle.getPoint((point_index+2)%3));
            std::array<size_t,3> adjList2;
            size_t pointInTriangle2 = findPointIndex(new_triangle2,triangle.getPoint(point_index));
            adjList2[pointInTriangle2] = newTriangleIndex1;
            adjList2[(pointInTriangle1+1)%3] = adjTriangle.getNeighbour(adj_point_index);
            adjList2[(pointInTriangle1+2)%3] = triangle.getNeighbour((point_index+2)%3);
            updateIndexInNeighbour(triangulation,triangle_index,triangle.getNeighbour((point_index+2)%3),newTriangleIndex2);
            updateIndexInNeighbour(triangulation,triangle.getNeighbour((point_index+1)%3),adjTriangle.getNeighbour(adj_point_index),newTriangleIndex2);
            Dag_node* dag2 = new Dag_node(newTriangleIndex2);
            triangulation.addTriangle(Triangulation_member(new_triangle2,adjList2,dag2));
            adjTriangle.getDagNode()->appendChild(dag2);
            triangle.getDagNode()->appendChild(dag2);

            //std::cout << "finito";

            flipEdge(triangulation,newTriangleIndex1,pointInTriangle1);
            flipEdge(triangulation,newTriangleIndex2,pointInTriangle2);
        }
    }
}


void incrementalStep(Triangulation& triangulation, Dag_node* dag,const cg3::Point2Dd& point){
    //dag->print();
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
                adjList[reference_index] = new_triangles_indexes[(t+2)%3];
                adjList[(reference_index+1)%3] = current_triangle.getNeighbour(t);
                adjList[(reference_index+2)%3] = new_triangles_indexes[(t+1)%3];
                updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(t),new_triangles_indexes[t]);
                Dag_node* dag = new Dag_node(new_triangles_indexes[t]);
                triangulation.addTriangle(Triangulation_member(new_triangles[t],adjList,dag));
                current_node->appendChild(dag);             
                /*std::cout << "  triangolo creato n "  << new_triangles_indexes[t] <<" "<< reference_index << " : ("<<new1.getPoint(0).x()<<" , "<<new1.getPoint(0).y()<<") "
                          <<"("<<new1.getPoint(1).x()<<" , "<<new1.getPoint(1).y()<<") "
                        <<"("<<new1.getPoint(2).x()<<" , "<<new1.getPoint(2).y()<<") lista adiacenza " << adjList[0] << "  " << adjList[1] << "  " << adjList[2];*/
            }
            for (size_t x = 0;x < 3;x++) {
                flipEdge(triangulation,new_triangles_indexes[x],2);
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
            size_t currentIndexInOtherTriangle = findIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(edge_index));
            //std::cout << currentIndexInOtherTriangle;

            std::array<size_t,4> new_triangles_indexes;
            new_triangles_indexes[0] = current_index;
            new_triangles_indexes[1] = current_index+1;
            new_triangles_indexes[2] = current_index+2;
            new_triangles_indexes[3] = current_index+3;

            Triangle2d current_new1 = Triangle2d(point,current_triangle.getPoint((edge_index+2)%3),current_triangle.getPoint(edge_index));
            size_t point_index = findPointIndex(current_new1,point);
            std::array<size_t,3> adjList1;
            adjList1[point_index] = new_triangles_indexes[1];
            adjList1[(point_index+1)%3] = current_triangle.getNeighbour((edge_index+2)%3);
            adjList1[(point_index+2)%3] = new_triangles_indexes[3];
            updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour((edge_index+2)%3),new_triangles_indexes[0]);
            Dag_node* dag1 = new Dag_node(new_triangles_indexes[0]);
            triangulation.addTriangle(Triangulation_member(current_new1,adjList1,dag1));
            current_node->appendChild(dag1);

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
            Dag_node* dag2 = new Dag_node(new_triangles_indexes[1]);
            triangulation.addTriangle(Triangulation_member(current_new2,adjList2,dag2));
            current_node->appendChild(dag2);

            //triangulation.addTriangle(Triangulation_member(current_new2,adjList2,current_node->appendChild(new_triangles_indexes[1])));

            Dag_node* current_node2 = other_triangle.getDagNode();

            /*std::cout << "triangolo 2 : ("<<current_new2.getPoint(0).x()<<" , "<<current_new2.getPoint(0).y()<<") "
                              <<"("<<current_new2.getPoint(1).x()<<" , "<<current_new2.getPoint(1).y()<<") "
                            <<"("<<current_new2.getPoint(2).x()<<" , "<<current_new2.getPoint(2).y()<<") ";*/

            Triangle2d current_new3 = Triangle2d(point,other_triangle.getPoint((currentIndexInOtherTriangle+2)%3),other_triangle.getPoint(currentIndexInOtherTriangle));
            point_index = findPointIndex(current_new3,point);
            std::array<size_t,3> adjList3;
            adjList3[point_index] = new_triangles_indexes[3];
            adjList3[(point_index+1)%3] = other_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3);
            adjList3[(point_index+2)%3] = new_triangles_indexes[1];
            updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),other_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3),new_triangles_indexes[2]);
            Dag_node* dag3 = new Dag_node(new_triangles_indexes[2]);
            triangulation.addTriangle(Triangulation_member(current_new3,adjList3,dag3));
            current_node2->appendChild(dag3);

            //triangulation.addTriangle(Triangulation_member(current_new3,adjList3,current_node2->appendChild(new_triangles_indexes[2])));

            /*std::cout << "triangolo 3 : ("<<current_new3.getPoint(0).x()<<" , "<<current_new3.getPoint(0).y()<<") "
                              <<"("<<current_new3.getPoint(1).x()<<" , "<<current_new3.getPoint(1).y()<<") "
                            <<"("<<current_new3.getPoint(2).x()<<" , "<<current_new3.getPoint(2).y()<<") ";*/


            Triangle2d current_new4 = Triangle2d(point,other_triangle.getPoint((currentIndexInOtherTriangle+1)%3),other_triangle.getPoint((currentIndexInOtherTriangle+2)%3));
            point_index = findPointIndex(current_new4,point);
            std::array<size_t,3> adjList4;
            adjList4[point_index] = new_triangles_indexes[0];
            adjList4[(point_index+1)%3] = other_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3);
            adjList4[(point_index+2)%3] = new_triangles_indexes[2];
            updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),other_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3),new_triangles_indexes[3]);
            Dag_node* dag4 = new Dag_node(new_triangles_indexes[3]);
            triangulation.addTriangle(Triangulation_member(current_new4,adjList4,dag4));
            current_node2->appendChild(dag4);
            flipEdge(triangulation,new_triangles_indexes[0],0);
            flipEdge(triangulation,new_triangles_indexes[1],0);
            flipEdge(triangulation,new_triangles_indexes[2],0);
            flipEdge(triangulation,new_triangles_indexes[3],0);
            //triangulation.addTriangle(Triangulation_member(current_new4,adjList4,current_node2->appendChild(new_triangles_indexes[3])));

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
