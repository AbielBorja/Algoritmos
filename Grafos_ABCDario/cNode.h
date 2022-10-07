#include <iostream>
#include <vector>

using namespace std;

#ifndef __NODE
#define __NODE


class Node
{
private:

public:
    bool active;
    vector<Node*> connections;
    Node();


};

#endif