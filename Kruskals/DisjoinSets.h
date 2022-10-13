#include "Node.h"
#include <vector>

using namespace std;

class DisjoinSets
{
private:
    /* data */
public:
    vector<vector<Node*>> sets;
    DisjoinSets();
    void makeSet(Node* u);
    vector<Node*> findSet(Node* u);
    void do_union(vector<Node*> a, vector<Node*> b);
    string toString();
    
};
