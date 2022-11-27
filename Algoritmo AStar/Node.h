#include <iostream>
#include <vector>
#pragma once

using namespace std;

#ifndef __NODE
#define __NODE

class Node
{
private:
    
public:
    Node(int number);
    int number;
    Node* prev;
    int distance;
    float heuristic;
    float g;
    float f;
    Node* parent;
    vector<Node*> neighbors;

};


#endif


