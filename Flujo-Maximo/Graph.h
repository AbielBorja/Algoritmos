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
    Edge* getMinCap(vector<Edge*> qs);
    void remove(vector<Node *> &qs, Node *q);
    Edge* findEdge(Node* u, Node* v);
    Node* getMinDist(vector<Node *> qs);
    void processPath(vector<Edge*> path);
    int runFordFulkerson(Node* s, Node* t);
    bool bfs(Node*s, Node* t);


};

#endif