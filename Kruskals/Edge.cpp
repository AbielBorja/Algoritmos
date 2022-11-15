#include "Edge.h"

//Este es el constructor de un arista que toma el primer nodo, el segundo y el peso de la misma.
Edge::Edge(Node* first, Node* second, int weight)
{
    this->first = first;
    this->second = second;
    this->weight = weight;
}

//Esta función imprime una arista
string Edge::toString()
{
    string s;
    s += to_string(this->first->number) + " ";
    s += to_string(this->second->number) + " ";
    s += to_string(this->weight);


    return s;
}