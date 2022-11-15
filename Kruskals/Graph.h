#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "Node.h"
#include "Edge.h"
#include "DisjointSets.h"

using namespace std;

#ifndef __GRAPH
#define __GRAPH

class Graph 
{
public:
    vector<Node*> nodes;
    vector<Edge*> edges;
    DisjointSets* ds;
    Graph(vector<Node*> nodes, vector<Edge*> edges);

    void print();
    void printDs();
    void createGraph();
    vector<string> splitString(string s, string sep);
    vector<int> convertStringsToInt(vector<string> strings);
    Edge* getEdge(Node* u, Node* v);
    vector<Edge*> runKruskal();

};
#endif