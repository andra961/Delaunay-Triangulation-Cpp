#include "triangle_utilities.h"

Dag_node* searchTriangle(Triangulation& triangulation,Dag_node* dag,const cg3::Point2Dd& point)
{
    for(size_t i = 0; i < dag->getChildren().size(); i++)
        {
            Triangle2d current_triangle = triangulation.getTriangle(dag->getChildren()[i]->getIndex());
            if(isPointLyingInTriangle(current_triangle.getPoint(0),current_triangle.getPoint(1),current_triangle.getPoint(2),point,true))
            {
                return searchTriangle(triangulation,dag->getChildren()[i],point);
            }
        }

    return dag;
}

void deleteDag(Dag_node* dag){
    std::set<Dag_node*> allNodes;
    std::set<Dag_node*>::iterator it;
    deleteDagRec(dag,allNodes);
    for (it = allNodes.begin(); it != allNodes.end(); ++it) {
        delete *it;
    }

}

void deleteDagRec(Dag_node* dag,std::set<Dag_node*>& allNodes){

    if(dag != NULL){
        std::vector<Dag_node*> children = dag->getChildren();
        if (allNodes.insert(dag).second == true){
            for (size_t i = 0;i<children.size();i++) {
                deleteDagRec(children[i],allNodes);
            }
        }
    }
}


