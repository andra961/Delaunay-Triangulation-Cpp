#include "drawable_delaunay_triangulation.h"


/**
 * @brief constructor initialises the drawable triangulation with a triangle representing the bounding space and the center and radius of the scene
 * @param init_triangle the bounding triangle,MUST be sorted in anti-clockwise order
 * @param dag_node the node of the dag which will point to the bounding triangle(the root of the dag)
 * @param center the center of the scene
 * @param radius the radius of the scene
 */
Drawable_delaunay_triangulation::Drawable_delaunay_triangulation(const Triangle2d& init_triangle,Dag_node* dag,const cg3::Pointd center,const double radius) : Triangulation(init_triangle,dag)
{
    this->center = center;
    this->radius = radius;
}

/**
 * @brief draws the triangulation
 */

void Drawable_delaunay_triangulation::draw() const {
    //draw each active triangle and his points
    for (size_t i = 0;i<this->triangles.size();i++) {
        Triangulation_member triangle = this->triangles[i];
        if(triangle.isActive())
        {
            cg3::viewer::drawTriangle2D(triangle.getPoints(),cg3::Color(),2);
            cg3::viewer::drawPoint2D(triangle.getPoint(0),cg3::Color(),3);
            cg3::viewer::drawPoint2D(triangle.getPoint(1),cg3::Color(),3);
            cg3::viewer::drawPoint2D(triangle.getPoint(2),cg3::Color(),3);
        }       
    }
}

/**
 * @brief gets the scene center
 * @return the scene center
 */

cg3::Pointd Drawable_delaunay_triangulation::sceneCenter() const {
    return this->center;
}

/**
 * @brief gets the scene radius
 * @return the scene radius
 */

double Drawable_delaunay_triangulation::sceneRadius() const {
    return this->radius;
}
