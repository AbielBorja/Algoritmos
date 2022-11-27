#include <iostream>
#include <vector>
#include "Node.h"
#include "Edge.h"
#include "math.h"
#include <algorithm>

using namespace std;

#ifndef __GRAPH
#define __GRAPH

class Graph
{
private:
    
public:
    Graph(vector<Node*> _nodes, vector<Edge*> _edges);
    vector<Node*> nodes;
    vector<Edge*> edges;

    vector<Node*> getNeighbors(Node* n);
    void print();
    void runAStar(Node* source, Node* goal, int numNodes);
    Node* getMinDist(vector<Node*> qs);
    void remove(vector<Node*> &qs, Node* q);
    int getLegth(Node* u, Node* v);
    float calculateHeuristic(Node* source, Node* goal, int numNodes);

};

#endif