#include "DisjoinSets.h"

DisjoinSets::DisjoinSets()
{
}

void DisjoinSets::makeSet(Node* u)
{
    vector<Node*> set;
    set.push_back(u);
    sets.push_back(set);
}

vector<Node*> DisjoinSets::findSet(Node* u)
{
    vector<vector<Node*>>::iterator si;
    for (si = sets.begin(); si != sets.end(); si++)
    {
        /* code */
    }
    
}