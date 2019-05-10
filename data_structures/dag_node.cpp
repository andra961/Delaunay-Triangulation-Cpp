#include "dag_node.h"


/**
 * @brief constructor of a node
 * @param triangle index of the triangle in the triangulation
 */

Dag_node::Dag_node(const size_t triangle)
{
    this->triangle = triangle;
}

/**
 * @brief append a node to the current one given a pointer to it
 * @param newNode pointer to the node to be appended
 */

void Dag_node::appendChild(Dag_node* newNode)
{
    this->children.push_back(newNode);

}

/**
 * @brief set the triangle contained in the node
 * @param triangle index of the triangle in the triangulation
 */

void Dag_node::setTriangle(const size_t triangle)
{
    this->triangle = triangle;
}

/**
 * @brief get the index of the triangle
 * @return the index of the triangle in the triangulation
 */

size_t Dag_node::getIndex() const{
    return this->triangle;
}

/**
 * @brief get the the pointers to the children of the node
 * @return the children of the node
 */

std::vector<Dag_node *>& Dag_node::getChildren(){
    return this->children;
}

/**
 * @brief get the number of the children of the node
 * @return the number of the children of the node
 */

size_t Dag_node::numChildren(){
    return this->children.size();
}



