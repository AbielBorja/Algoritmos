//  Actividad 3.3
//  Implementación de "Knapsack problem"
//  Alfonso Pineda Cedillo   |   A01660394
//  Abiel Moisés Borja García    |   A01654937

/* ------------------- EXPLICACIÓN   ------------------

Para darle solución a este problema de Knapsack problem, hicimos uso del algoritmo de Dijkstra, por lo que unicamente analiza
el path con mayor valor por cada uno de los nodos, y los compara entre sí. Debido a lo anterior, no recorremos el grafo completo, por lo que en algunos casos, nuestro algoritmo no devuelve la opción más óptima. Para el tiempo con el que contamos, damos solución al problema, sin embargo, podría mejorarse.

Para solucionar dicha situación, la implementación de un algorimto que considere flujos (como Floyd) podría darnos mejores resultados debido a que considera más paths por cada nodo, sin embargo, no recorre el grafo en su totalidad. Para poder encontrar la solución mejor, necesitaríamos recorrer todo el grafo mediante bfs, haciendo una comparación de los paths encontrados y seleccionando el que nos devuelva un mayor valor a un menor costo (peso)

*/

#include "Graph.h"
#include <iostream>
#include <vector>

using namespace std;

/*
readMatrix | O(n^2)
Nos permite ingresar los valores individuales de una matriz (vector de vectores)
cuadrada (n^2).
*/
vector<int> readMatrix(int n)
{
    vector<int> row;
    for (int r = 0; r < n; r++)
    {
        int a = 0;
        cin >> a;
        row.push_back(a);
    }
    return row;
}

/*
buildNodes | O(n)
Dado un entero "n", la función buildNodes nos permite crear n nodos, empezando
por el ínidice 1 hasta n.
*/
vector<Node *> buildNodes(int n)
{
    vector<Node *> nodes;
    for (int i = 0; i < n; i++)
    {
        Node *N = new Node(i + 1);
        nodes.push_back(N);
    }
    return nodes;
}

/*
buildEdges | O(n^2)
Dada una matriz y un vector de nodos, la función buildEdges nos permite crear
las conexiones de dichos nodos con los valores ingresados dentro de la matriz.
*/
vector<Edge *> buildEdges(vector<int> weights, vector<Node *> nodes)
{
    vector<Edge *> edges;
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = i + 1; j < nodes.size(); j++)
        {
            edges.push_back(new Edge(nodes[i], nodes[j], weights[i] * -1));
        }
    }
    return edges;
}

int main()
{
    int n, w;

    cout << "Ingresa el número de elementos posibles disponibles: ";
    cin >> n;

    cout << "\nIntroduce el valor de cada uno de esos elementos:" << endl;
    vector<int> val = readMatrix(n);

    cout << "\nIntroduce el peso de cada uno de los elementos:" << endl;
    vector<int> weihgts = readMatrix(n);

    cout << "\nIngresa la capacidad máxima de la mochila: ";
    cin >> w;
    // Creación de los vectores de nodos y edges.
    vector<Node *> nodes = buildNodes(n + 1);
    vector<Edge *> edges = buildEdges(weihgts, nodes);
    // Creación del grafo con los vectores de nodos y conexiones (edges)
    // previamente creados.
    Graph *graph = new Graph(nodes, edges);
    vector<Node *> diamons;

    // vector<Node *> diamons;
    for (int i = 0; i < n; i++)
    {
        graph->runDijkstra(nodes[i]);
        cout << "----" << endl;
        graph->print();
        cout << "----";
        graph->pushNodes(w);
        graph->resetNodes();
    }

    graph->daBest();

    return 0;
}