#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "Node.h"

using namespace std;

#ifndef __GRAPH
#define __GRAPH

class Graph 
{
public:
    vector<Node*> nodes;
    vector<vector<Node*>> nodeMatrix;
    int n;
    Graph(vector<Node*> nodes);
    void print();
    void createGraph();
    vector<string> splitString(string s, string sep);
    vector<int> convertStringsToInt(vector<string> strings);


};
#endif