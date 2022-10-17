#include <iostream>
#include "Node.h"

using namespace std;

#ifndef __EDGE
#define __EDGE

class Edge
{
private:
    
public:
    Edge(Node* _first, Node* _second, int _weigth, int _capacity);
    Node* first;
    Node* second;
    int weight;
    int capacity;

};


#endif