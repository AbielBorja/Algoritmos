#include "Node.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

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

        // DEBUG
        //cout << "CICLO ----> " << ciclo << endl;
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

    for (int i = 0; i < numNodes; i++)
    {
        vector<Node *> nodes = createNodes(numNodes);
        vector<Edge *> edges = createEdges(matrix, nodes);
        Graph *graph = new Graph(nodes, edges);
        graph->runDijkstra(nodes[i]);
        cout << "\nEl source es: " << nodes.at(i)->number << endl;
        graph->print();
        cout << "-------";
    }

    cout << endl << "\nFloyd: " << endl;
    vector <Node*> nodes = createNodes(numNodes);
    vector <Edge*> edges = createEdges(matrix, nodes);
    Graph* graph = new Graph(nodes, edges);
    graph->runFloyd();

    return 0;
}
