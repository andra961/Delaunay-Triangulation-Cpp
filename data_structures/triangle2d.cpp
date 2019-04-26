#include "triangle2d.h"

Triangle2d::Triangle2d()
{

}

Triangle2d::Triangle2d(std::array<cg3::Point2Dd,3>& points,bool clockWiseOrAntiClockWise){

    if (clockWiseOrAntiClockWise){
        sortClockWiseOrder(points);
    }
    else {
        sortAntiClockWiseOrder(points);
    }

    this->vertexes=points;
}
