#pragma once
#include <iostream>
#include <vector>
using namespace std;

class FunctionG
{
public:
    vector <int> set;   // COnjunto que va a la derecha en p
    int exit;           // Número que va a la izquierda en P
    int result;         // resultado de evaluar P
    FunctionG(int _exit_val, vector<int> set);

    vector<vector<int>> find_permutations();
};
