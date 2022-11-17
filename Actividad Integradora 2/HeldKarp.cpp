#include "HeldKarp.h"

HeldKarp::HeldKarp(Graph *_g) { g = _g; }

vector<int> HeldKarp::findHamilton(Node *start)
{
    // Llama a findHamilton(start, size_i) donde size_i va de 0 a N-1
    // Guarda functionP para el tamaño size_i y agrega a un vector de functionP
    // Construye el path final usando el vector de functionP
    for (int s = 0; s < g->nodes.size() - 1; s++)
    {
        findHamilton(start, s);
    }

    vector<int> finalSet;
    vector<Node *>::iterator ni;
    for (ni = g->nodes.begin(); ni != g->nodes.end(); ++ni)
    {
        finalSet.push_back((*ni)->number);
    }
    finalSet = values_without(finalSet, start->number);

    FunctionG *fg = new FunctionG(start->number, finalSet);
    fg->result = findResultG(fg);
    vector<FunctionG *> finalLevel;
    finalLevel.push_back(fg);
    prev_results.push_back(finalLevel);

    // cout << "Functions G: {" << endl;
    vector<vector<FunctionG *>>::iterator ri;

    // Encontrar los valores P:
    vector<int> valuesP;
    for (ri = prev_results.begin(); ri != prev_results.end(); ++ri)
    {
        int p = findResultP(*ri, start);
        valuesP.push_back(p);
    }
    valuesP.push_back(start->number); // Salir del inicio

    // Opcional. Mostrar el recorrido TSP obtenido:
    cout << endl << "Recorrido Hamilton: ";
    cout << "Ruta a seguir por el personal que reparte correspondencia, considerando inicio y fin en al misma colonia: " << endl;
    vector<int>::reverse_iterator pi;
    for (pi = valuesP.rbegin(); pi != valuesP.rend(); ++pi)
    {
        if (pi + 1 != valuesP.rend())
        {
            cout << to_string(*pi) << " camina a -> ";
        }
        else
        {
            cout << to_string(*pi) << endl;
        }
    }
    return valuesP;
}

void HeldKarp::findHamilton(Node *start, int set_size)
{
    if (set_size == 0)
    {
        vector<FunctionG *> prev; // prev es nuevo porque estamos en tamaño O.
        // Tomar los nodos que llegan a start y construir conjuntos vacíos +
        // FunctionG.
        vector<Edge *>::iterator ei;
        for (ei = g->edges.begin(); ei != g->edges.end(); ++ei)
        {
            if ((*ei)->second == start)
            {                   // llega a start...
                vector<int> vi; // Conjunto de tamaño O
                FunctionG *fg = new FunctionG((*ei)->first->number, vi);
                fg->result = (*ei)->weight;
                // Lo anterior es: gCvecino de start, {})
                prev.push_back(fg);
            }
        }
        prev_results.push_back(prev);
    }
    else
    {
        vector<FunctionG *> curr;
        vector<FunctionG *> prev =
            prev_results[set_size - 1]; // prev es el vector anterior.
        // Ahora, los conjuntos salen de la combinación de la iteración anterior.
        vector<FunctionG *>::iterator gi;
        vector<int> values;
        // A. Toma los valores (únicos) de salida anteriores.
        for (gi = prev.begin(); gi != prev.end(); ++gi)
        {
            if (std::find(values.begin(), values.end(), (*gi)->exit_val) ==
                values.end())
            {                                      // Si no se encuentra
                values.push_back((*gi)->exit_val); // Agregarlo, para que sea único
            }
        }
        // B. Combínalos con conjuntos creados a partir de los demás valores, sin
        // pasar del tamaño del conjunto. Si es necesario, hacer más conjuntos.
        vector<int>::iterator vi;
        for (vi = values.begin(); vi != values.end(); ++vi)
        {
            vector<int> superset = values_without(values, *vi);
            vector<vector<int>> subsets;
            vector<int> d(set_size, 0);
            findCombinations(superset, superset.size(), set_size, 0, d, 0, subsets);
            vector<vector<int>>::iterator si;
            for (si = subsets.begin(); si != subsets.end(); ++si)
            {
                FunctionG *fg = new FunctionG(*vi, *si);
                fg->result = findResultG(fg);
                curr.push_back(fg);
            }
        }
        prev_results.push_back(curr);
    }
}

// Regresa un vector de enteros con todos los valores excepto "to_remove"
vector<int> HeldKarp::values_without(vector<int> &v, int to_remove)
{
    vector<int> result;
    vector<int>::iterator vi;
    for (vi = v.begin(); vi != v.end(); ++vi)
    {
        if ((*vi) != to_remove)
        {
            result.push_back(*vi);
        }
    }
    return result;
}
// Encuentra los posibles subconjuntos de arr (arr de tamaño n).
// Almacena estos subconjuntos en "combos".
// Los subconjuntos son de tamaño r.
// Original de: https://www.geeksforgeeks.org/print-subsets-given-size-set/
void HeldKarp::findCombinations(vector<int> &arr, int n, int r, int index,
                                vector<int> &data, int i,
                                vector<vector<int>> &combos)
{
    // Current combination is ready, print it
    if (index == r)
    {
        // Un subconjunto está listo Cde data[0] a data[r]). Lo guardamos en combos:
        vector<int> subset;
        for (int j = 0; j < r; ++j)
        {
            subset.push_back(data[j]);
        }
        combos.push_back(subset);
        return;
    }
    if (i >= n)
    {
        return;
    }
    data[index] = arr[i];
    findCombinations(arr, n, r, index + 1, data, i + 1, combos);
    findCombinations(arr, n, r, index, data, i + 1, combos);
}

// Determina si dos vectores de enteros contienen los mismos elementos.
// Los elementos pueden estar en diferente orden.
bool HeldKarp::compareSets(vector<int> a, vector<int> b)
{
    if (a.size() == b.size())
    {
        vector<int>::iterator ia;
        for (ia = a.begin(); ia != a.end(); ++ia)
        {
            if (std::find(b.begin(), b.end(), *ia) == b.end())
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
// Encuentra el resultado de la función g(e, s) en prev_results. // Si no
// encuentra dicha función gCe,$), regresa -1.
int HeldKarp::findPrevValueG(int e, vector<int> s)
{
    int sizeToFind = s.size();
    vector<FunctionG *> search_space = prev_results[sizeToFind];
    vector<FunctionG *>::iterator gi;
    for (gi = search_space.begin(); gi != search_space.end(); ++gi)
    {
        if ((*gi)->exit_val == e && compareSets(s, (*gi)->set))
        {
            return (*gi)->result;
        }
    }
    FunctionG *fg = new FunctionG(e, s);
    cout << "Warning: Previous FunctionG not found: " << endl;
    return -1;
}

// Para encontrar el valor de fg:
// g(exit, S) = ruin{ Edge(Si,exit) + g(Si, S-{Si} } para toda Si en el conjunto
// S. Es decir, g(exit, S) = mili{ peso del arco de Si hasta exit + g(Si, S
// menos el elemento Si) }

int HeldKarp::findResultG(FunctionG *fg)
{
    vector<int>::iterator si;
    vector<int> candidates;
    for (si = fg->set.begin(); si != fg->set.end(); ++si)
    {
        vector<int> subset = values_without(fg->set, *si);
        HeldKarp *ne = new HeldKarp(g);
        Edge *e = g->findEdgeInt(fg->exit_val, *si);
        if (e != nullptr)
        {
            int c = e->weight + findPrevValueG(*si, subset);
            candidates.push_back(c); // weightC5i,exit) + g(Si, S-{Si}
        }
        else
        {
            cout << "Warning: can't find edge from " << fg->exit_val
                 << " to " << to_string(*si) << "." << endl;
        }
    }
    if (candidates.size() == 0)
    {
        cout << "Warning: candidates for findWeightG is empty: " << endl;
        return -1;
    }
    int minC = *std::min_element(candidates.begin(), candidates.end());
    return minC;
}
// Para encontrar el valor de P:
// 1. Encontrar el mínimo valor de fg para este tamaño de conjunto.
// 2. El valor de p será el penúltimo nodo en el conjunto S, hacia la salida.
// 2.1 Si S == {} entonces P = salida.

// 2.2 Si ISI < 2 entonces no tiene penúltimo elemento y se toma el único disponible.
int HeldKarp::findResultP(vector<FunctionG *> vfg, Node *start)
{
    int minIndex = -1;
    int currIndex = 0;
    int minF = INT16_MAX;
    vector<FunctionG *>::iterator fgi;
    for (fgi = vfg.begin(); fgi != vfg.end(); ++fgi)
    {
        if ((*fgi)->result < minF)
        {
            minF = (*fgi)->result;
            minIndex = currIndex;
        }
        currIndex++;
    }
    if (minIndex == -1)
    {
        cout << "Warning: P function failed." << endl;
        return -1;
    }
    int sizeS = vfg[minIndex]->set.size(); // 2.1
    if (sizeS == 0)
        return start->number; // 2.2
    if (sizeS < 2)
        return vfg[minIndex]->set[0]; // 2
    else
        return vfg[minIndex]->set[1];
}