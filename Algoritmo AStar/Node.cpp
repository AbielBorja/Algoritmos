#include "Node.h"
#include "math.h"

Node::Node(int _number)
{
    number = _number;
    prev = nullptr;
    distance = 10000;
    heuristic = 0;
    g = 0;
    f = 0;
}

