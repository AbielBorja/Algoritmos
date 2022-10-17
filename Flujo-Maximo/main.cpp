// Daniel Alejandro Martinez Rosete A01654093
// Abiel Moisès Borja Garcìa A01654937
#include "Node.h"
#include "Edge.h"
#include "Graph.h"

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

// Complejidad O(n)
// Donde n es el numero de nodos que queremos crear
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
    vector<vector<int> > matrix = createMatrix(numNodes);

    /*
    6
    0 11 12 -1 -1 -1
    -1 0 -1 12 -1 -1
    -1 1 0 -1 11 -1 
    -1 -1 -1 0 -1 19
    -1 -1 -1 7 0 4
    -1 -1 -1 -1 -1 0
    */

    vector<Node *> nodes = createNodes(numNodes);
    vector<Edge *> edges = createEdges(matrix, nodes);
    Graph *graph = new Graph(nodes, edges);

    int maxFlow = graph->runFordFulkerson(nodes.at(0),nodes.at(5));
    cout << endl;
    cout << endl;
    cout << to_string(maxFlow) << endl;

    return 0;

    return 0;
}