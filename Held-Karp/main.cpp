#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include <iostream>
#include <vector>
using namespace std;

// Complejodad O(n^2) por trabajar con una matriz de vectores
vector<vector<int>> createMatrix(int numNodes)
{
    vector<vector<int>> matrix;
    string inputs;
    for (int i = 0; i < numNodes; i++)
    {
        vector<int> row;
        for (int x = 0; x < numNodes; x++)
        {
            cin >> inputs;
            row.push_back(stoi(inputs));
        }
        matrix.push_back(row);
    }
    return matrix;
}

vector<Node *> createNodes(int numNodes)
{
    vector<Node *> nodes;
    for (int i = 1; i <= numNodes; i++)
    {
        Node *temp = new Node(i);
        nodes.push_back(temp);
    }

    return nodes;
}

// Creacion de nuevos con los nodos agregado
//  COmplejidad O(n^2) por cuestion de trabajar con una matrix de input
vector<Edge *> createEdges(vector<vector<int>> matrix, vector<Node *> nodes)
{
    vector<Edge *> edges;
    int nodo1 = -1;
    int nodo2;
    int ciclo = 0;
    for (auto ni : matrix)
    {
        nodo1 += 1;
        nodo2 = 0;
        ciclo += 1;
        for (auto nodeInt : ni)
        {
            // DEBUG
            // cout << "Nodo 1: " << nodes.at(nodo1)->number << " Nodo 2: " << nodes.at(nodo2)->number << " Distancia: " << nodeInt << endl;
            if (nodeInt != -1 && nodeInt != 0)
            {
                // DEBUG
                // cout << "Nodo 1: " << nodes.at(nodo1)->number << " Nodo 2: " << nodes.at(nodo2)->number << " Distancia: " << nodeInt << endl;
                edges.push_back(new Edge(nodes.at(nodo1), nodes.at(nodo2), nodeInt));
            }
            nodo2 += 1;
        }
    }
    return edges;
}

int main()
{
    int numNodes;
    cout << "Numero de nodos ";
    cin >> numNodes;
    cout << "Ingresa matriz de nodos: " << endl;
    vector<vector<int>> matrix = createMatrix(numNodes);
    vector<Node *> nodes = createNodes(numNodes);
    vector<Edge *> edges = createEdges(matrix, nodes);
    Graph *graph = new Graph(nodes, edges);

    for (int i = 0; i < numNodes; i++)
    {
        graph->runDijkstra(nodes[i]);
        cout << "----" << endl;
        graph->print();
        cout << "----";
        graph->resetNodes();
    }
}
