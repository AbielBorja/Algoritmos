#include "FunctionG.h"

// O(n)
// Donde n es el tamano del vector
FunctionG::FunctionG(int _exit_val, vector<int> set)
{
    vector<int>::iterator it;
    for (it = set.begin(); it != set.end(); it++)
    {
        this->set.push_back(*it);
    }
    exit_val = _exit_val;
    result = 0;
}
