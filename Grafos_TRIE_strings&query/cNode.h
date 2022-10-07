#include <iostream>
#include <vector>

using namespace std;

#ifndef __NODE
#define __NODE

class Node
{
private:
    char payload;
public:
    Node(char c);
    vector<Node*> connections;
    char getPayload();
    string toString();
};

Node::Node(char c)
{
    payload = c;
}

char Node::getPayload()
{
    return payload;
}

string Node::toString()
{
    string s;
    s += payload;
    s += "|";
    
    for(int c =0; c<connections.size(); c++)
    {
        s += connections[c]->toString() + "";
    }
    return s;
}
#endif