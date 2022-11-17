#pragma once
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#ifndef __POINT
#define __POINT

class Point
{
private:
    
public:
    Point(int x, int y);
    int x;
    int y;
    double findDistance(Point* b);

};


#endif


