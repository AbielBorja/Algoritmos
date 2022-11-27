#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "Node.h"
#include "Edge.h"
#include "DisjointSets.h"
#include "HeldKarp.h"
#include <algorithm>

using namespace std;

#ifndef __GRAPH
#define __GRAPH

class Graph
{
private:
public:
    Graph(vector<Node *> _nodes, vector<Edge *> _edges);
    vector<Node *> nodes;
    vector<Edge *> edges;
    vector<Node *> getNeighbors(Node *n);
    void print();
    Node *getMinDist(vector<Node *> qs);
    Edge *findEdge(Node *u, Node *v);


    // --------- Dijktra & Floyd 
    void printFloyd(vector<vector<int>> matrix);
    void runDijkstra(Node *source);
    void runFloyd();
    void remove(vector<Node *> &qs, Node *q);
    int getLegth(Node *u, Node *v);

    // ---------- Kruskal
    DisjointSets* ds;
    vector<Edge*> runKruskal();
    void printDs();

    // --------- Flujo Maximo
    void processPath(vector<Edge *> path);
    int runFordFulkerson(Node *s, Node *t);
    bool bfs(Node *s, Node *t);
    

    // -------- Knapsack
    void resetNodes();
    void pushNodes(int capacity);
    void daBest();

    // ------- Heldkarp
    Edge *findEdgeInt(int u, int v);
};

#endif