#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include "Point.h"
#include "Points.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

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
//  COmplejidad O(numNodes^2) por cuestion de trabajar con una matrix de input
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
    vector<vector<int>> matrix;
    vector<vector<int>> matrix2;
    vector<Point> puntos;
    // leer el archivo
    ifstream file("test.txt");

    if (file.is_open())
    {
        string line;
        getline(file, line);
        numNodes = atoi(line.c_str());
        for (int i = 0; i < numNodes + 1; i++)
        {
            getline(file, line);
            vector<int> row;
            string l = line.c_str();

            if (l.size() != 0)
            {
                stringstream lineStream(l);
                vector<int> numbers(istream_iterator<int>(lineStream),
                                    {});
                for (int k = 0; k < numbers.size(); k++)
                {
                    int num = numbers[k];
                    row.push_back(num);
                }
                matrix.push_back(row);
            }
        }

        for (int i = 0; i < numNodes + 1; i++)
        {
            getline(file, line);
            vector<int> row;
            string l = line.c_str();
            if (l.size() != 0)
            {
                stringstream lineStream(l);
                vector<int> numbers(istream_iterator<int>(lineStream),
                                     {});
                for (int k = 0; k < numbers.size(); k++)
                {
                    int num = numbers[k];
                    // cout << num << " ";
                    row.push_back(num);
                }
                matrix2.push_back(row);
            }
        }

        for (int i = 0; i < numNodes + 1; i++)
        {
            getline(file, line);
            string l = line.c_str();
            string token;
            l.erase(remove(l.begin(), l.end(), '('), l.end());
            l.erase(remove(l.begin(), l.end(), ')'), l.end());
            int pos = 0;
            string delimitador = ",";
            pos = l.find(delimitador);
            string t = l.substr(0, pos);

            string left = l.substr(pos + 1, l.size());
            if (l.size() != 0)
            {
                float a = stod(t);
                float b = stod(left);
                Point punto(a, b);
                puntos.push_back(punto);
            }
        }

        file.close();
    }
    cout << numNodes << endl;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < matrix2.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    vector<Node *> nodes = createNodes(numNodes);
    vector<Edge *> edges = createEdges(matrix, nodes);

    // ------ Kruskal
    Graph *graph1 = new Graph(nodes, edges);
    vector<Edge *> ed = graph1->runKruskal();
    cout << "Recorrido Kruskal: " << endl;
    cout << "Forma de cablear las colonias con fibra. (lista de arcos de la forma (A,B)): " << endl;
    vector<Edge *>::iterator it;
    for (it = ed.begin(); it != ed.end(); it++)
    {
        cout << (*it)->toString() << endl;
    }

    // ------- Hamilton
    HeldKarp *hamilton = new HeldKarp(graph1);
    hamilton->findHamilton(nodes[0]);
    cout << endl;
    cout << endl;

    // Flujo Maximo
    vector<Node *> nodes2 = createNodes(numNodes);
    vector<Edge *> edges2 = createEdges(matrix2, nodes2);
    Graph *graph3 = new Graph(nodes2, edges2);
    int maxFlow = graph3->runFordFulkerson(nodes2.at(0), nodes2.at(numNodes - 1));
    cout << "Valor de flujo maximo de informacion del nodo inicial al nodo final: " << to_string(maxFlow) << endl;
    cout << endl;

    // Puntos
    Point *a = new Point(200, 500);
    Point *b = new Point(300, 100);
    Point *c = new Point(450, 150);
    Point *d = new Point(520, 480);

    vector<Point *> points;
    points.push_back(a);
    points.push_back(b);
    points.push_back(c);
    points.push_back(d);

    Points *p = new Points(points);
    p->findClosest();

    return 0;
}
