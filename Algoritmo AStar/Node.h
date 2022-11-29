#include <iostream>
#include <vector>

using namespace std;

#ifndef __NODE
#define __NODE

class Node 
{
public:
    int number;
    float f; 	
	float g;	
	float h;	
	Node* parent;
	vector<Node*> neighbors; 
	vector<Node*> diagonals; 
    int wall;
    Node(int number);
    string toString();

};
#endif