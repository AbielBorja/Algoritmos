#include "Point.h"

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

double Point::findDistance(Point* b)
{
    double X = pow((b->x - this->x), 2);
    double Y = pow((b->y - this->y), 2);
    
    double distance = sqrt(X + Y);
    return distance;
}