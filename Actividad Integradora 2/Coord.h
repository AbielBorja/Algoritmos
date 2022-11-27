#pragma once
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

#ifndef __COORD
#define __COORD

class Coord 
{
public:
    Coord(float minX, float maxX, float minY, float maxY);
    Coord(float x, float y);
    float x;
    float y;
    float getDist(Coord c);
    string toString();

};
#endif