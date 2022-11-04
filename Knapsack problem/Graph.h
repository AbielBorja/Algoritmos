#pragma once
#include "Edge.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Graph
{

public:
    vector<Node *> nodes;
    vector<Edge *> edges;
    int valueMax = 0;
    int valueCapacity = 0;

    Graph(vector<Node *> _nodes, vector<Edge *> _edges);

    Node *src;
    vector<Node *> getNeighbours(Node *n);
    void print();
    void runDijkstra(Node *source);
    void runFloyd();
    Node *getMinDist(vector<Node *> qs);
    void remove(vector<Node *> &qs, Node *q);
    int getLength(Node *u, Node *v);
    void resetNodes();
    void pushNodes(int capacity);
    void daBest();
};