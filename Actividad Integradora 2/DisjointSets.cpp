#include "DisjointSets.h"
#include <algorithm>

DisjointSets::DisjointSets()
{}

void DisjointSets::MakeSet(Node* x)
{
    vector<Node* > set;
    set.push_back(x);
    sets.push_back(set);
}

// O(n^2)
// Donde n el tamaño de los vectores de nodos
void DisjointSets::makeUnion(vector<Node*> a, vector<Node*> b)
{
    vector<Node*> unionVec(a.size() + b.size());
    vector<Node*>::iterator it;
    it = set_union(a.begin(), a.end(),b.begin(),b.end(),unionVec.begin());
    unionVec.resize(it - unionVec.begin());
    vector<vector<Node*> >::iterator is;
    for(is = sets.begin(); is != sets.end(); is++)
    {
        vector<Node*> set = *is;
        vector<Node*>::iterator ni;
        for(ni = set.begin(); ni != set.end(); ni++)
        {
            if((*ni) == a.at(0))
                (*is) = unionVec;
            if((*ni) == b.at(0))
                (*is).clear();   
        }
    }
}

// O(n^2)
// Donde n el tamaño de los vectores de nodos
vector<Node* > DisjointSets::findSet(Node* n)
{
    vector<vector<Node*> >::iterator it;
    for (it = sets.begin(); it != sets.end(); it++)
    {
        vector<Node*> set = *it;
        vector<Node*>::iterator vn;
        for (vn = set.begin(); vn != set.end(); vn++)
        {
            if((*vn) == n)
            {
                return set;
            }
        }
        
    }

    vector<Node*> emptyVec;
    return emptyVec;
}

