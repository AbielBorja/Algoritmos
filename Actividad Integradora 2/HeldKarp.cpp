#include "HeldKarp.h"

HeldKarp::HeldKarp(Graph *_g) { g = _g; }

// O(n^n+2n * n^2 + 2n)
// Donde n es el tamaño de los vectores de ejes del grafo
// Donde se busca hacer iteraciones de los diferentes caminos que puede recorrer el grafo
// Al tener funciones internas con diferentes complejdiades la funcion aumenta su tiempo de ejecución

/* Observación */

/* La implementación de este algoritmo de Hamilton hace un recorrido ciclico, con la funcionalidad de comparar distancias entre nodos para poder iniciar 
en un nodo y poder terminar nuevamente en el mismo nodo de inicio. Aunque para esta implementación se utilizo un metodo de programación dinamica 
para utilizar valores de caminos que previamente se habian visitado. El camino de un path que cumpla con poder iniciar de un nodo y terminar en el mismo no siempre puede 
que sea la más eficiente

Para poder mejorar este algoritmo, lo primero que se me ocurre es poder diferentes restricciones que me permitan visitar otros caminos para poder identificar 
un nuevo path que mejore el peso. Otra manera aunque más pesada, visitar todo aquel camino posible que cumpla con el recorrido y comparar el más eficiente, en cuestion de distancias*/
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
    valuesP = findResultP(start);

    // for (ri = prev_results.begin(); ri != prev_results.end(); ++ri)
    // {

    // }

    // Opcional. Mostrar el recorrido TSP obtenido:
    cout << endl
         << "Recorrido Hamilton: ";
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

// Complejidad
// O(n+2n)
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
        vector<FunctionG *> prev = prev_results[set_size - 1]; // prev es el vector anterior.
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
// Complejidad
// O(n)
// donde n es el tamaño de vectores de int
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
// Complejidad
// O(m)
// Donde m es el tamaño del subconjunto del arr
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
// Complejidad
// O(n)
// Donde n es el tamaño del vector de int
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
// Complejidad 
// O(n)
// Donde n es el tamaño del vector de Funtion G
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
// Complejidad
// O(n)
// Donde n es el tamaño del vector de functionG
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

// Complejidad
// O(n^2)
// Donde n es el tamaño del vector de 
vector<int> HeldKarp::findResultP(Node *start)
{
    vector<int> tsp = {start->number};
    vector<int> tempSet;
    int counter = 1;
    for (int r = prev_results.size() - 1; r >= 0; r--)
    {
        vector<FunctionG *> gs = prev_results[r];
        if (r == prev_results.size() - 1)
        {
            int step = -1;
            if (gs[0]->set.size() > 1)
                step = gs[0]->set[1];
            else
                step = gs[0]->set[0];
            tempSet = values_without(gs[0]->set, step);
            tsp.push_back(step);
        }
        else
        {
            int step = -1;
            vector<FunctionG *>::iterator gi;
            for (gi = gs.begin(); gi != gs.end(); ++gi)
            {
                if ((*gi)->exit_val == tsp[counter - 1] && compareSets(tempSet, (*gi)->set))
                {
                    if ((*gi)->set.size() > 1)
                        step = (*gi)->set[1];
                    else if ((*gi)->set.size() == 1)
                        step = (*gi)->set[0];
                    else
                        step = start->number;

                    tempSet = values_without((*gi)->set, step);
                    tsp.push_back(step);
                }
            }
        }
        counter++;
    }
    // cout << "Esto tiene TSP" << endl;
    // for (auto x : tsp)
    // {
    //     cout << x << endl;
    // }
    return tsp;
}