#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Coord.h"


using namespace std;

#ifndef __DELAUNEY
#define __DELAUNEY

class Delauney 
{
public:
    vector<Coord> coordList;
    Delauney(vector<Coord> coordList);


    float findMin();

    
};
#endif