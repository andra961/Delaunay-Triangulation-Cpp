#include "dag_node.h"

Dag_node::Dag_node()
{

}

Dag_node::Dag_node(const size_t triangle)
{
    this->triangle = triangle;
}

void Dag_node::appendChild(const size_t triangle)
{
    this->children.push_back(new Dag_node(triangle));
}

void Dag_node::setTriangle(const size_t triangle)
{
    this->triangle = triangle;
}

size_t Dag_node::getIndex() const{
    return this->triangle;
}

Dag_node* Dag_node::searchTriangle(const Triangulation& triangulation,const cg3::Point2Dd point)
{
    for(size_t i = 0; i < this->children.size(); i++)
        {
            Triangle2d current_triangle = triangulation.getTriangle(this->children[i]->getIndex());
            if(isPointLyingInTriangle(current_triangle.getPoints()[0],current_triangle.getPoints()[1],current_triangle.getPoints()[2],point,true))
            {
                return this->children[i]->searchTriangle(triangulation,point);
            }
        }

    return this;
}
