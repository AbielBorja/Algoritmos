#include "Edge.h"

Edge::Edge(Node* _first, Node* _second, int _weight, int _residual_flow)
{
    first = _first;
    second = _second;
    residual_flow = _residual_flow;
    capacity = _weight;
    weight = _weight;
}

//Esta función imprime una arista
string Edge::toString()
{
    string s;
    s += "Num de colonia A: " + to_string(this->first->number) + " a ";
    s += "Num de colonia B: " + to_string(this->second->number) + " ";
    s += "con distancia de: " + to_string(this->weight);

    return s;
}