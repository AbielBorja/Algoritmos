#include <iostream>
#include <vector>

using namespace std;

#ifndef __NODE
#define __NODE

class Node 
{
public:
    int number;
    Node* prev;
    int distance;
    Node(int number);
    string toString();

};
#endif