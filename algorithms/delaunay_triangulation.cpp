#include "delaunay_triangulation.h"

namespace Delaunay {

    /**
     * @brief changes the value in the adjList of a neighbour that points to a triangle,to a new one
     * @param triangle_index the index of the triangle that,in the adjList of his neighbour,will be the one of an other triangle
     * @param neighbour_index the index of the triangle whose adjList will be updated
     * @param new_index the new value in the adjList of the neighbour
     */

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

    /**
     * @brief finds the index of a triangle in the adjList of his neighbour
     * @param triangle_index the index of the triangle whose index in the adjList will be searched
     * @param neighbour_index the index of the neighbour
     * @return the index of the triangle in the adjList of his neighbour
     */

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

    /**
     * @brief computes the operation of edge flipping defined in the randomized incremental delaunay algorithm
     * @param triangulation the triangulation
     * @param triangle_index the index of the triangle whose edge will be legalized
     * @param point_index the index of the point(in the triangle) opposite to the edge to legalize
     */


    void flipEdge(Triangulation& triangulation,const size_t triangle_index,const size_t point_index){

        //get the triangle in the triangulation through the index
        Triangulation_member triangle = triangulation.getTriangle(triangle_index);
        //check if the triangle has a neighbour on the edge to legalize
        if(triangle.getNeighbour((point_index+1)%3) != 0){
            //gets the adjacent triangle
            Triangulation_member adjTriangle = triangulation.getTriangle(triangle.getNeighbour((point_index+1)%3));
            //gets the index of the point opposite to the edge in the adjacent triangle
            size_t adj_point_index = ((Delaunay::findIndexInNeighbour(triangulation,triangle_index,triangle.getNeighbour((point_index+1)%3))+2)%3);
            //check if the edge is legal
            if (DelaunayTriangulation::Checker::isPointLyingInCircle(triangle.getPoint(0),triangle.getPoint(1),triangle.getPoint(2),adjTriangle.getPoint(adj_point_index),false)) {

                //deactivates the two old triangles adjacents to the illegal edge
                triangulation.setTriangleInactive(triangle_index);
                triangulation.setTriangleInactive(triangle.getNeighbour((point_index+1)%3));
                size_t current_index = triangulation.size();
                size_t newTriangleIndex1 = current_index;
                size_t newTriangleIndex2 = current_index+1;

                //create the first new triangle with the edge flipped

                Triangle2d new_triangle1 = Triangle2d(triangle.getPoint(point_index),triangle.getPoint((point_index+1)%3),adjTriangle.getPoint(adj_point_index));
                std::array<size_t,3> adjList1;

                //creates adjList
                adjList1[0] = triangle.getNeighbour(point_index);
                adjList1[1] = adjTriangle.getNeighbour((adj_point_index+2)%3);
                adjList1[2] = newTriangleIndex2;

                //updates the adjLists of the triangles adjacent to the old ones
                Delaunay::updateIndexInNeighbour(triangulation,triangle_index,triangle.getNeighbour(point_index),newTriangleIndex1);
                Delaunay::updateIndexInNeighbour(triangulation,triangle.getNeighbour((point_index+1)%3),adjTriangle.getNeighbour((adj_point_index+2)%3),newTriangleIndex1);

                //creates a new dag node for the triangle
                Dag_node* dag1 = new Dag_node(newTriangleIndex1);
                triangulation.addTriangle(Triangulation_member(new_triangle1,adjList1,dag1));

                //appends the new node to the nodes of the dag representing the old triangles
                triangle.getDagNode()->appendChild(dag1);
                adjTriangle.getDagNode()->appendChild(dag1);

                //creates the second new triangle with the edge flipped

                Triangle2d new_triangle2 = Triangle2d(triangle.getPoint(point_index),adjTriangle.getPoint(adj_point_index),triangle.getPoint((point_index+2)%3));
                std::array<size_t,3> adjList2;

                //creates adjList
                adjList2[0] = newTriangleIndex1;
                adjList2[1] = adjTriangle.getNeighbour(adj_point_index);
                adjList2[2] = triangle.getNeighbour((point_index+2)%3);

                //updates the adjLists of the triangles adjacent to the old ones
                Delaunay::updateIndexInNeighbour(triangulation,triangle_index,triangle.getNeighbour((point_index+2)%3),newTriangleIndex2);
                Delaunay::updateIndexInNeighbour(triangulation,triangle.getNeighbour((point_index+1)%3),adjTriangle.getNeighbour(adj_point_index),newTriangleIndex2);

                //creates a new dag node for the triangle
                Dag_node* dag2 = new Dag_node(newTriangleIndex2);
                //adds the triangle in the triangulation
                triangulation.addTriangle(Triangulation_member(new_triangle2,adjList2,dag2));

                //appends the new node to the nodes of the dag representing the old triangles
                adjTriangle.getDagNode()->appendChild(dag2);
                triangle.getDagNode()->appendChild(dag2);


                //check the edges of the new triangles created
                Delaunay::flipEdge(triangulation,newTriangleIndex1,0);
                Delaunay::flipEdge(triangulation,newTriangleIndex2,0);
            }
        }
    }

    /**
     * @brief adds a point to the triangulation which is completely inside a triangle and splits it in 3 new ones
     * @param current_triangle the triangle in which the point lies
     * @param point the point
     */

    void insertPointInsideAndFlip(Triangulation& triangulation,const Triangulation_member& current_triangle, const cg3::Point2Dd& point)
    {
        Dag_node* current_node = current_triangle.getDagNode();
        size_t current_index = triangulation.size();

        //the indexes that the new triangles will have in the triangulation once inserted
        std::array<size_t,3> new_triangles_indexes;
        new_triangles_indexes[0] = current_index;
        new_triangles_indexes[1] = current_index+1;
        new_triangles_indexes[2] = current_index+2;

        //the adj list
        std::array<size_t,3> adjList;

        //splits the triangle in the 3 new ones,for each:
        for (size_t i = 0;i<3;i++) {
            //creates the adjList
            adjList[0] = new_triangles_indexes[(i+2)%3];
            adjList[1] = current_triangle.getNeighbour(i);
            adjList[2] = new_triangles_indexes[(i+1)%3];

            //updates the adjLists of the triangles adjacent to the old one
            Delaunay::updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(i),new_triangles_indexes[i]);
            //creates a new dag node for the triangle
            Dag_node* dag = new Dag_node(new_triangles_indexes[i]);
            //adds the triangle in the triangulation
            triangulation.addTriangle(Triangulation_member(Triangle2d(point,current_triangle.getPoint(i),current_triangle.getPoint((i+1)%3)),adjList,dag));
            //appends the new node to the node of the dag representing the old triangle
            current_node->appendChild(dag);

        }
        for (size_t i = 0;i < 3;i++) {
            //performs edge flipping on the edges opposite to the point in the new triangles if necessary
            Delaunay::flipEdge(triangulation,new_triangles_indexes[i],0);
        }
    }

    /**
     * @brief adds a point to the triangulation which lies on a edge of two triangles and split each in 2
     * @param current_triangle the triangle in which the point lies(on one of his edges)
     * @param edge_index the index of the edge on which the point lies in the triangle
     * @param point the point
     */

    void insertPointOnEdgeAndFlip(Triangulation& triangulation,const Triangulation_member& current_triangle,const size_t edge_index,const cg3::Point2Dd& point)
    {
        //gets the node in the dag corrisponding to the current_triangle
        Dag_node* current_node = current_triangle.getDagNode();

        //gets the triangle adjacent on the edge in which the point lies
        Triangulation_member other_triangle = triangulation.getTriangle(current_triangle.getNeighbour(edge_index));

        //sets it inactive
        triangulation.setTriangleInactive(current_triangle.getNeighbour(edge_index));

        //finds the index of the edge on which the point lies in the new triangle
        size_t currentIndexInOtherTriangle = Delaunay::findIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour(edge_index));


        size_t current_index = triangulation.size();

        //the indexes that the new triangles will have in the triangulation once inserted
        std::array<size_t,4> new_triangles_indexes;
        new_triangles_indexes[0] = current_index;
        new_triangles_indexes[1] = current_index+1;
        new_triangles_indexes[2] = current_index+2;
        new_triangles_indexes[3] = current_index+3;

        //creates the new triangles:the first two are obtained splitting the current_triangle

        //the first

        Triangle2d current_new1 = Triangle2d(point,current_triangle.getPoint((edge_index+2)%3),current_triangle.getPoint(edge_index));
        std::array<size_t,3> adjList1;
        //creates the adjList
        adjList1[0] = new_triangles_indexes[1];
        adjList1[1] = current_triangle.getNeighbour((edge_index+2)%3);
        adjList1[2] = new_triangles_indexes[3];
        //updates the adjLists of the triangles adjacent to the old one
        Delaunay::updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour((edge_index+2)%3),new_triangles_indexes[0]);
        //creates a new dag node for the triangle
        Dag_node* dag1 = new Dag_node(new_triangles_indexes[0]);
        //adds the triangle in the triangulation
        triangulation.addTriangle(Triangulation_member(current_new1,adjList1,dag1));
        //appends the new node to the node of the dag representing the current_triangle
        current_node->appendChild(dag1);

        //the second
        Triangle2d current_new2 = Triangle2d(point,current_triangle.getPoint((edge_index+1)%3),current_triangle.getPoint((edge_index+2)%3));
        std::array<size_t,3> adjList2;
        //creates the adjList
        adjList2[0] = new_triangles_indexes[2];
        adjList2[1] = current_triangle.getNeighbour((edge_index+1)%3);
        adjList2[2] = new_triangles_indexes[0];
        //updates the adjLists of the triangles adjacent to the old one
        Delaunay::updateIndexInNeighbour(triangulation,current_node->getIndex(),current_triangle.getNeighbour((edge_index+1)%3),new_triangles_indexes[1]);
        //creates a new dag node for the triangle
        Dag_node* dag2 = new Dag_node(new_triangles_indexes[1]);
        //adds the triangle in the triangulation
        triangulation.addTriangle(Triangulation_member(current_new2,adjList2,dag2));
        //appends the new node to the node of the dag representing the current_triangle
        current_node->appendChild(dag2);


        //creates the new triangles:the second two are obtained splitting the other_triangle

        //gets the node in the dag corrisponding to the other_triangle
        Dag_node* current_node2 = other_triangle.getDagNode();

        //the third
        Triangle2d current_new3 = Triangle2d(point,other_triangle.getPoint((currentIndexInOtherTriangle+2)%3),other_triangle.getPoint(currentIndexInOtherTriangle));
        std::array<size_t,3> adjList3;
        //creates the adjList
        adjList3[0] = new_triangles_indexes[3];
        adjList3[1] = other_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3);
        adjList3[2] = new_triangles_indexes[1];
        Delaunay::updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),other_triangle.getNeighbour((currentIndexInOtherTriangle+2)%3),new_triangles_indexes[2]);
        //creates a new dag node for the triangle
        Dag_node* dag3 = new Dag_node(new_triangles_indexes[2]);
        //adds the triangle in the triangulation
        triangulation.addTriangle(Triangulation_member(current_new3,adjList3,dag3));
        //appends the new node to the node of the dag representing the other_triangle
        current_node2->appendChild(dag3);


        //the fourth
        Triangle2d current_new4 = Triangle2d(point,other_triangle.getPoint((currentIndexInOtherTriangle+1)%3),other_triangle.getPoint((currentIndexInOtherTriangle+2)%3));
        std::array<size_t,3> adjList4;
        //creates the adjList
        adjList4[0] = new_triangles_indexes[0];
        adjList4[1] = other_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3);
        adjList4[2] = new_triangles_indexes[2];
        Delaunay::updateIndexInNeighbour(triangulation,current_triangle.getNeighbour(edge_index),other_triangle.getNeighbour((currentIndexInOtherTriangle+1)%3),new_triangles_indexes[3]);
        //creates a new dag node for the triangle
        Dag_node* dag4 = new Dag_node(new_triangles_indexes[3]);
        //adds the triangle in the triangulation
        triangulation.addTriangle(Triangulation_member(current_new4,adjList4,dag4));
        //appends the new node to the node of the dag representing the other_triangle
        current_node2->appendChild(dag4);

        //performs edge flipping on the edges opposite to the point in the new triangles if necessary
        Delaunay::flipEdge(triangulation,new_triangles_indexes[0],0);
        Delaunay::flipEdge(triangulation,new_triangles_indexes[1],0);
        Delaunay::flipEdge(triangulation,new_triangles_indexes[2],0);
        Delaunay::flipEdge(triangulation,new_triangles_indexes[3],0);
    }


    /**
     * @brief performs the operation associated to the insertion of one point in the triangulation
     * @param triangulation the triangulation
     * @param dag the dag associated to the triangulation
     * @param the point to be inserted
     */

    void incrementalStep(Triangulation& triangulation, Dag_node* dag,const cg3::Point2Dd& point){

        //searches a triangle in the triangulation containing the point
        Dag_node* current_node = Dag::searchTriangle(triangulation,dag,point);

        //sets it inactive
        triangulation.setTriangleInactive(current_node->getIndex());

        Triangulation_member current_triangle = triangulation.getTriangle(current_node->getIndex());

        //if the point is already inserted do nothing
        if(point == current_triangle.getPoint(0) || point == current_triangle.getPoint(1) || point == current_triangle.getPoint(2))
        {}
        else {
            //check if the point lies on the edges of the triangle
            bool isPointOnEdge1 = positionOfPointWithRespectToSegment(current_triangle.getPoint(0),current_triangle.getPoint(1),point) == 0.0;
            bool isPointOnEdge2 = positionOfPointWithRespectToSegment(current_triangle.getPoint(1),current_triangle.getPoint(2),point) == 0.0;
            bool isPointOnEdge3 = positionOfPointWithRespectToSegment(current_triangle.getPoint(2),current_triangle.getPoint(0),point) == 0.0;
            if((!isPointOnEdge1) && (!isPointOnEdge2) && (!isPointOnEdge3))
            {
                //it doesnt
                Delaunay::insertPointInsideAndFlip(triangulation,current_triangle,point);
            }

            else {
                //it does,determines the index of the edge on which it lies
                size_t edge_index;
                if(isPointOnEdge1){edge_index = 0;}
                else if (isPointOnEdge2){edge_index = 1;}
                else {edge_index = 2;}

                Delaunay::insertPointOnEdgeAndFlip(triangulation,current_triangle,edge_index,point);
            }
        }
    }

    /**
     * @brief discards the points of the bounding box and their adjacent triangles
     * @param triangulation the triangulation
     */

    void discardBoundingVertexes(Triangulation& triangulation){
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


    /**
     * @brief performs the randomized incremental delaunay algorithm on a list of points
     * @param triangulation the triangulation contaning the bounding triangle
     * @param dag the dag containing the node associated to the bounding triangle
     */

    void getTriangulation(Triangulation& triangulation, Dag_node* dag,const std::vector<cg3::Point2Dd>& points){
        std::vector<cg3::Point2Dd> shuffled_points = points;

        //random shuffle the points
        std::random_shuffle(shuffled_points.begin(),shuffled_points.end());

        //insert the points one by one
        for (size_t i = 0; i< shuffled_points.size();i++) {
            Delaunay::incrementalStep(triangulation,dag,shuffled_points[i]);
        }

        //discards the points of the bounding box and their adjacent triangles
        Delaunay::discardBoundingVertexes(triangulation);
    }
}


