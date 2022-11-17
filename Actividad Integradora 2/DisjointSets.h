#pragma once
#include <iostream>
#include "Node.h"


using namespace std;

#ifndef __DISJOINTSETS
#define __DISJOINTSETS

class DisjointSets 
{
public:
    vector<vector<Node*> > sets;

    DisjointSets();
    void MakeSet(Node* x);
    void makeUnion(vector<Node*> a, vector<Node*> b);
    vector<Node* > findSet(Node* n);
};
#endif