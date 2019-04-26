#include "triangle_utilities.h"


double getClockWiseAngle(const cg3::Point2Dd point) {
    double angle = atan2(point.x(), point.y());
    return angle;
}

bool comparePointsClockWise(const cg3::Point2Dd point1, const cg3::Point2Dd point2) {
    return getClockWiseAngle(point1) < getClockWiseAngle(point2);
}

//template <typename Container>
void sortClockWiseOrder(std::array<cg3::Point2Dd,3>& points){
    std::sort(points.begin(),points.end(),comparePointsClockWise);
}

//template <typename Container>
void sortAntiClockWiseOrder(std::array<cg3::Point2Dd,3>& points){
    //typename Container::const_iterator first = points.begin();
    //typename Container::const_iterator last = points.end();
    std::sort(points.begin(),points.end(),comparePointsClockWise);
    std::reverse(points.begin(),points.end());
}


