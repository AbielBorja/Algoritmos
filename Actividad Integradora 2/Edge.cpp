#include "Edge.h"

Edge::Edge(Node* _first, Node* _second, int _weigth)
{
    first = _first;
    second = _second;
    weight = _weigth;
}

Edge::Edge(Node* _first, Node* _second, int _capacity, int _residual_flow)
{
    first = _first;
    second = _second;
    residual_flow = _residual_flow;
    capacity = _capacity;
}