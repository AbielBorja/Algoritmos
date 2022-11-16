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
                edges.push_back(new Edge(nodes.at(nodo1), nodes.at(nodo2), nodeInt, 0));
            }
            nodo2 += 1;
        }

        // DEBUG
        // cout << "CICLO ----> " << ciclo << endl;
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
    // Hamilton
    Graph *graph = new Graph(nodes, edges);

    // Kruskal
    Graph *graph2 = new Graph(nodes, edges);
    vector<Edge *> ed = graph2->runKruskal();
    cout << "\nKruskal: " << endl;
    vector<Edge *>::iterator it;
    for (it = ed.begin(); it != ed.end(); it++)
    {
        cout << (*it)->toString() << endl;
    }

    cout << endl;
    cout << endl;
    
    // Flujo Maximo
    vector<vector<int>> matrix2 = createMatrix(numNodes);
    vector<Node *> nodes2 = createNodes(numNodes);
    vector<Edge *> edges2 = createEdges(matrix2, nodes2);
    Graph *graph3 = new Graph(nodes2, edges2);
    int maxFlow = graph3->runFordFulkerson(nodes2.at(0), nodes2.at(numNodes - 1));
    cout << "Flujo Maximo de informacion del nodo inicial al nodo final. : " << to_string(maxFlow) << endl;

    return 0;
}
