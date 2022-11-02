//  Actividad 3.2
//  Implementación de "Dijkstra and Floyd"
//  Alfonso Pineda Cedillo   |   A01660394
//  Abiel Moisés Borja García    |   A01654937

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
            edges.push_back(new Edge(nodes[i], nodes[j], weights[i]*-1));
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

    cout << "Ingresa la capacidad máxima de la mochila: ";
    cin >> w;
    // Creación de los vectores de nodos y edges.
    vector<Node *> nodes = buildNodes(n + 1);
    vector<Edge *> edges = buildEdges(weihgts, nodes);
    // Creación del grafo con los vectores de nodos y conexiones (edges)
    // previamente creados.
    Graph *graph = new Graph(nodes, edges);
    vector<Node*> diamons;
    for (int i = 0; i < n; i++)
    {
        graph->runDijkstra(nodes[i]);
        graph->pushNodes(diamons);
        // cout << "----" << endl;
        // graph->print();
        // cout << "----";
        graph->resetNodes();
    }
    graph->daBest(diamons, w);

    return 0;
}