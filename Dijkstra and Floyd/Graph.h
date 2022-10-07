#include <iostream>
#include <vector>
#include "Node.h"
#include "Edge.h"
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
    void printFloyd(vector<vector<int>> matrix);
    void runDijkstra(Node* source);
    void runFloyd();
    Node* getMinDist(vector<Node*> qs);
    void remove(vector<Node*> &qs, Node* q);
    int getLegth(Node* u, Node* v);

};

#endif