#include "Edge.h"

Edge::Edge(Node* _first, Node* _second, int _weigth, int _capacity)
{
    first = _first;
    second = _second;
    weight = _weigth;
    capacity = _capacity;
}