#include "dag_utilities.h"

namespace Dag {

    /**
     * @brief searches a triangle containing a point
     * @param triangulation the triangulation in which the research is computed
     * @param dag the node from which the search begins
     * @param point the point
     */

    Dag_node* searchTriangle(Triangulation& triangulation,Dag_node* dag,const cg3::Point2Dd& point)
    {
        for(size_t i = 0; i < dag->getChildren().size(); i++)
            {
                Triangle2d current_triangle = triangulation.getTriangle(dag->getChildren()[i]->getIndex());
                if(isPointLyingInTriangle(current_triangle.getPoint(0),current_triangle.getPoint(1),current_triangle.getPoint(2),point,true))
                {
                    return Dag::searchTriangle(triangulation,dag->getChildren()[i],point);
                }
            }

        return dag;
    }

    /**
     * @brief deallocates the dag starting from the root
     * @param dag the node to delete
     */

    void deleteDag(Dag_node* dag){
        //a set in which we add only one pointer to each unique node of the dag,in order to deallocate them only once
        std::set<Dag_node*> allNodes;
        std::set<Dag_node*>::iterator it;
        //fill the set
        Dag::addNodeToDeleteRec(dag,allNodes);
        //deallocating the nodes of the set
        for (it = allNodes.begin(); it != allNodes.end(); ++it) {
            delete *it;
        }

    }

    /**
     * @brief iterate the dag and add to the set only one pointer to each unique node
     * @param dag the node
     */

    void addNodeToDeleteRec(Dag_node* dag,std::set<Dag_node*>& allNodes){

        if(dag != nullptr){
            std::vector<Dag_node*> children = dag->getChildren();
            //if the pointer wasn't already in the set:
            if (allNodes.insert(dag).second == true){
                for (size_t i = 0;i<children.size();i++) {
                    //call the function for each child
                    Dag::addNodeToDeleteRec(children[i],allNodes);
                }
            }
        }
    }
}

