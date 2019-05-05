#include "dag_node.h"

Dag_node::Dag_node()
{

}

Dag_node::Dag_node(const size_t triangle)
{
    this->triangle = triangle;
}

Dag_node* Dag_node::appendChild(const size_t triangle)
{
    Dag_node* newNode = new Dag_node(triangle);
    this->children.push_back(newNode);

    return newNode;
}

void Dag_node::setTriangle(const size_t triangle)
{
    this->triangle = triangle;
}

size_t Dag_node::getIndex() const{
    return this->triangle;
}

std::vector<Dag_node *> Dag_node::getChildren() const{
    return this->children;
}


