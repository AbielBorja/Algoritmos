#include "Node.h"
#include <iostream>

using namespace std;

//El constructor de un nodo con su numero y su prev por default a NULL 
Node::Node(int number)
{
    this->number = number;
    this->prev = NULL;
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