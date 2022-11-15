#include <iostream>
#include "Node.h"

using namespace std;

#ifndef __EDGE
#define __EDGE

class Edge 
{
public:
    Node* first;
    Node* second;
    int weight;
    Edge(Node* first, Node* second, int weight);
    string toString();

};
#endif