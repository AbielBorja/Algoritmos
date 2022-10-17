#include "Node.h"

Node::Node(int _number)
{
    number = _number;
    prev = nullptr;
    distance = 10000;
    visited = false;
}