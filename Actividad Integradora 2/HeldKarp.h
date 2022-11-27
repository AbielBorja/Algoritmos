#pragma once
#include "Graph.h"
#include "FunctionG.h"
using namespace std;

class HeldKarp
{
public:
    Graph *g;
    HeldKarp(Graph *g);
    vector<int> findHamilton(Node *start);
    void findHamilton(Node *start, int set_size);
    vector<int> values_without(vector<int> &v, int to_remove);
    void findCombinations(vector<int> &arr, int n, int r, int index, vector<int> &data, int i, vector<vector<int>> &combos);
    bool compareSets(vector<int> a, vector<int> b);
    int findPrevValueG(int e, vector<int> s);
    int findResultG(FunctionG *fg);
    vector<int> findResultP(Node *start);
    vector<vector<FunctionG *>> prev_results;
};
