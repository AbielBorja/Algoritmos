#include <iostream>
#include "Node.h"

using namespace std;

#ifndef __EDGE
#define __EDGE

class Edge
{
private:
    
public:
    Edge(Node* _first, Node* _second, int _capacity, int _residual_flow);
    Node* first;
    Node* second;
    int weight;
    int residual_flow;
    int capacity;
    string toString();
    
};


#endif