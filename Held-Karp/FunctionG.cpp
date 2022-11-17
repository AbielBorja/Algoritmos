#include <iostream>
#include "FunctionG.h"

FunctionG::FunctionG(int _exit_val, vector<int> _set)
{
    vector<int>::iterator it;
    for (it = _set.begin(); it != _set.end(); ++it)
    {
        set.push_back(*it);
    }
    exit_val = _exit_val;
    result = 0;
}
