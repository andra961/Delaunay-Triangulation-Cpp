#ifndef DRAWABLE_DELAUNAY_TRIANGULATION_H
#define DRAWABLE_DELAUNAY_TRIANGULATION_H

#include <cg3/viewer/interfaces/drawable_object.h>
#include <data_structures/triangulation.h>
#include <cg3/utilities/color.h>
#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

class Drawable_delaunay_triangulation  : public Triangulation, public cg3::DrawableObject
{
public:
    Drawable_delaunay_triangulation(const Triangle2d& init_triangle,Dag_node* dag,const cg3::Pointd center,const double radius);
    void draw() const;
    cg3::Pointd sceneCenter() const;
    double sceneRadius() const;
protected:
    cg3::Pointd center;
    double radius;
};

#endif // DRAWABLE_DELAUNAY_TRIANGULATION_H
