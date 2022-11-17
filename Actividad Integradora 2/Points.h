#pragma once
#include "Point.h"

#include <iostream>
#include <vector>

using namespace std;

#ifndef __POINTS
#define __POINTS

class Points
{
private:
    
public:
    Points(vector<Point*> points);
    vector<Point*> points;
    Point* last;

    void findClosest();

};


#endif


