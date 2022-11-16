#include "Node.h"

Node::Node(int _number)
{
    number = _number;
    prev = nullptr;
    distance = 10000;
    visited = false;
}

//Se pone el nodo en un String para facilitar su lectura.
string Node::toString()
{
    if (this->prev != NULL)
    {
        string s = "Node " + to_string(this->number) + ". Distance: " + to_string(this->distance) + ". Prev num: " + to_string(this->prev->number) + ".";
        return s;
    }else{
        string s = "Node " + to_string(this->number) + ". Distance: " + to_string(this->distance) + ". Prev num: " + "NULL" + ".";
        return s;
    }
    
    
}