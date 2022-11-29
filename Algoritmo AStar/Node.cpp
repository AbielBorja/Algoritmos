#include "Node.h"
#include <iostream>

using namespace std;

//El constructor de un nodo con su numero y su prev por default a NULL 
Node::Node(int number)
{
    this->number = number;
    this->wall = 0;
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->parent = nullptr;
}

//Se pone el nodo en un String para facilitar su lectura.
string Node::toString()
{
    string s = "Node " + to_string(this->number) + ", g: " + to_string(this->g);
    return s;
}