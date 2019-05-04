#ifndef DRAWABLE_DELAUNAY_TRIANGULATION_H
#define DRAWABLE_DELAUNAY_TRIANGULATION_H

#include <cg3/viewer/interfaces/drawable_object.h>
#include <data_structures/triangulation.h>
#include <cg3/utilities/color.h>
class Drawable_delaunay_triangulation  : public Triangulation, public cg3::DrawableObject
{
public:
    Drawable_delaunay_triangulation(const Triangle2d& init_triangle);
};

#endif // DRAWABLE_DELAUNAY_TRIANGULATION_H
