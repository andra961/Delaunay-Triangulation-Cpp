#include "dag_node.h"

Dag_node::Dag_node()
{

}

Dag_node::Dag_node(const size_t triangle)
{
    this->triangle = triangle;
}

void Dag_node::appendChild(Dag_node* newNode)
{
    this->children.push_back(newNode);

}

void Dag_node::setTriangle(const size_t triangle)
{
    this->triangle = triangle;
}

size_t Dag_node::getIndex() const{
    return this->triangle;
}

std::vector<Dag_node *>& Dag_node::getChildren(){
    return this->children;
}

void Dag_node::print() const{
    std::cout << this->triangle << "  ";
    for (size_t var = 0; var < children.size(); var++) {
        if(children[var] != NULL){
            children[var]->print();
        }
    }
}


