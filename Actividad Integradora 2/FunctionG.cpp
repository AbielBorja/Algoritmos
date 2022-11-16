#include "FunctionG.h"

// O(n)
// Donde n es el tamano del vector
FunctionG::FunctionG(int exit, vector<int> set)
{
    vector<int>::iterator it;
    for (it = set.begin(); it != set.end(); it++)
    {
        this->set.push_back(*it);
    }
    exit = exit;
    result = 0;
}
