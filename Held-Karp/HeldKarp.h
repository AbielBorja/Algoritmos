#pragma once
#include "Graph.h"
#include "FunctionG.h"
using namespace std;

class HeldKarp
{
public:
    vector<FunctionG*> prev_results;
    Graph* g;
    HeldKarp(Graph* _g);
    vector<Node*> findHamilton(Node* start);
    void findHamilton(Node* start, int size);
};
