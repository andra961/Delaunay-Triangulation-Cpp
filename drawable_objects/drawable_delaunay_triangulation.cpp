#include "drawable_delaunay_triangulation.h"

Drawable_delaunay_triangulation::Drawable_delaunay_triangulation(const Triangle2d& init_triangle,Dag_node* dag,const cg3::Pointd center,const double radius) : Triangulation(init_triangle,dag)
{
    this->center = center;
    this->radius = radius;
}

void Drawable_delaunay_triangulation::draw() const {
    for (size_t i = 0;i<this->triangles.size();i++) {
        Triangulation_member triangle = this->getTriangle(i);
        if(triangle.isActive())
        {
            cg3::viewer::drawTriangle2D(triangle.getPoints(),cg3::Color(),1);
        }
    }
}

cg3::Pointd Drawable_delaunay_triangulation::sceneCenter() const {
    return this->center;
}

double Drawable_delaunay_triangulation::sceneRadius() const {
    return this->radius;
}
