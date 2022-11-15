#include <iostream>
#include "FunctionG.h"

FunctionG::FunctionG(int _exit_val, vector<int> _set)
{
    vector<int>::iterator it;
    for (it = _set.begin(); it != _set.end(); ++it)
    {
        set.push_back(*it);
    }
    exit = _exit_val;
    result = 0;
}

vector<vector<int>> FunctionG::find_permutations()
{

}