#include "Graph.h"
#include <iostream>

/*
Graph | O(1)
Constructor Graph, inicializa el vector de nodos y el vector de aristas (edges, conexiones entre nodos)
*/
Graph::Graph(vector<Node *> _nodes, vector<Edge *> _edges)
{
    nodes = _nodes;
    edges = _edges;
}

// Complejidad  O(n)
// Donde n es el tamaño del vector de nodos
void Graph::print()
{
    for (auto node : nodes)
    {

        if (node->prev != nullptr)
        {
            if (src->number == node->number)
            {
                continue;
            }
            cout << "Node: " << src->number;
            cout << " to node " << nodes[nodes.size() - 1]->number;
            cout << " : " << node->distance << endl;
        }
    }
}

// resetNodes | O(n)
// Donde n es el tamño del vector de los nodos
void Graph::resetNodes()
{
    // DEBUG
    // cout << "RESET" << endl;
    // cout << "Nodes 2" << endl;

    for (auto node : nodes)
    {
        node->distance = 10000;
        node->prev = nullptr;
    }

    // DEBUG
    // for (auto node : nodes)
    // {
    //     cout << "Num: " << node->number << " Distancia: " << node->distance << endl;
    // }
}

/*
daBest
Imprime el resultado del algoritmo, devolviendo el mejor valor obtenido, permitido por la capacidad máxima de la mochila.
*/
void Graph::daBest()
{
    cout << "\nMejor valor: " << valueMax << " Con un peso de: " << valueCapacity * -1;
}

/*
pushNodes | O(n)
Su complejidad es O(n) ya que recorre el vector de nodos, obteniendo la suma total de los nodos (valor acumulado)
*/
void Graph::pushNodes(int capacity)
{
    Node *curr = nodes[nodes.size() - 1];
    int sum = 0;

    while (curr->prev != nullptr)
    {
        curr = curr->prev;
        sum += curr->number;
    }

    curr->distance = nodes[nodes.size() - 1]->distance;
    curr->number = sum;

    if (curr->distance * -1 <= capacity)
    {
        if (curr->number > valueMax)
        {
            valueMax = curr->number;
            valueCapacity = curr->distance;
        }
    }
}
/*
getLength | O(n)
Recibe dos nodos y nos devuelve la distancia entre ellos.
*/
int Graph::getLength(Node *u, Node *v)
{
    vector<Edge *>::iterator ei;

    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        if ((*ei)->first == u && (*ei)->second == v)
        {
            return (*ei)->weight;
            //   } else if ((*ei) -> first == v && (*ei) -> second == u){
            //     return (*ei) -> weight;
        }
    }
    return 0;
}

/*
getNeighbours | O(n)
Recibe un nodo, devuelve los vecinos que tiene dicho nodo en un vector de nodos.
Para obtener los vecinos, recorremos todas las aristas (edges), buscando el nodo "n". En las aritstas en las que participa "n", hay vecinos de "n".
*/
vector<Node *> Graph::getNeighbours(Node *n)
{
    vector<Node *> neighbours;
    vector<Edge *>::iterator ei;

    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        if ((*ei)->first == n)
            neighbours.push_back((*ei)->second);
        // if((*ei) -> second == n) neighbours.push_back((*ei) -> first);
    }

    return neighbours;
}

/*
remove | O(n)
Nos permite retirar nodos específicos de un vector de nodos dado. La función recibe el vector de nodos del cual se desea retirar, así como el nodo que se desea retirar.
*/
void Graph::remove(vector<Node *> &qs, Node *q)
{
    vector<Node *>::iterator ei;
    for (ei = qs.begin(); ei != qs.end(); ++ei)
    {
        if (*ei == q)
        {
            qs.erase(ei);
            break;
        }
    }
}

/*
getMinDist | O(n)
Nos permite obtener el nodo con la menor distancia; recibe el vector de nodos a los que se les calcula la distancia.
Inicializamos nuestra variable minDist en donde se guardará el valor de el nodo con la menor distancia, recorremos todo el vector de nodos, si la distancia del nodo (dentro de nuestro iterador) es menor a la que tenemos definida, actualizamos el dato.
*/
Node *Graph::getMinDist(vector<Node *> qs)
{
    Node *minDist = qs[0];
    vector<Node *>::iterator ei;

    for (ei = qs.begin(); ei != qs.end(); ++ei)
    {
        if ((*ei)->distance < minDist->distance)
        {
            minDist = *ei;
        }
    }
    return minDist;
}

// runDijkstra | O(n + m log(n))
// Donde n son los nodos del grafo
// DOnde m son las coneciones que tiene el graph
// Logaritmo por la cantidad de recurisividad que se tiene que hacer dentro de la función
void Graph::runDijkstra(Node *source)
{
    src = source;
    cout << "\n----Soy el source: " << src->number;
    // Iniciamos el source con distancia 0
    source->distance = 0;
    vector<Node *> Q = nodes;

    // Mientras Q no este vacio seguimos con el calulo de peso
    while (!Q.empty())
    {
        Node *u = getMinDist(Q);
        vector<Node *> neighbors = getNeighbours(u);
        remove(Q, u);

        // DEBUGS
        // cout << "\nNodo con menor distancia ahora es: " << u->number << endl;

        // DEBUGS
        // cout << "Asi anda Q ";
        // for (auto x : Q)
        //     cout << x->number << " ";
        // cout << endl;

        // // DEBUGS
        // for (auto neig : neighbors)
        //     cout << "Somos los vecinos " << neig->number << endl;

        vector<Node *>::iterator it;
        for (auto ni : neighbors)
        {
            it = std::find(Q.begin(), Q.end(), ni);
            if (it != Q.end())
            {
                int alt = u->distance + getLength(u, ni);

                if (alt < ni->distance)
                {
                    // DEBUG
                    // cout << "Distancia actual del nodo " << ni->number << ": " << ni->distance << endl;
                    // cout << "Distancia alternativa= " << alt << " De nodo " << u->number << " y " << ni->number << endl;
                    ni->distance = alt;
                    ni->prev = u;
                }
            }
        }
    }
}

/*
runFloyd | O(|V|^3)
*/
void Graph::runFloyd()
{
    vector<vector<int>> matrix;

    for (int i = 0; i < nodes.size(); i++)
    {
        // Crea un vector de tamaño 6, con cada valor infinito
        vector<int> row(nodes.size(), 10000);
        row[i] = 0; // La diagonal queda en 0's
        matrix.push_back(row);
    }

    vector<Edge *>::iterator ei;
    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        int row = (*ei)->first->number - 1;
        int column = (*ei)->second->number - 1;
        int value = (*ei)->weight;
        matrix[row][column] = value;
    }

    for (int k = 0; k < nodes.size(); k++)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            for (int j = 0; j < nodes.size(); j++)
            {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j])
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }

    // Impresión de matriz resultante | O(n^2)
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = 0; j < nodes.size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
