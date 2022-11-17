#include <iostream>
#include <vector>

using namespace std;

#ifndef __NODE
#define __NODE

class Node
{
private:
public:
    Node(int number);
    int number;
    Node *prev;
    int distance;
    bool visited;
    string toString();
};

#endif
