
#include <iostream>

using namespace std;

/* Graph                    - Constructor del grafo
   @ _nodes                 - Vector de nodos del grafo
   @ _edges                 - Vector de aristas que unen los nodos
  Complejidad O(1)
*/
Graph::Graph(vector<Node *> _nodes, vector<Edge *> _edges)
{
    nodes = _nodes;
    edges = _edges;
}

/* getNeighbours            - Obtiene los vecinos de un nodo
   @ node                   - Nodo del cual se obtendran los vecinos
  Complejidad O(n)
*/
vector<Node *> Graph::getNeighbours(Node *node)
{
    // Vector para guardar los vecinos
    vector<Node *> neighbours;

    // Iterador de Edge
    vector<Edge *>::iterator ei;

    // Recorrer los edges
    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        // Si el nodo es el origen del edge
        if ((*ei)->first == node)
        {
            // Agregar el destino del edge al vector de vecinos
            neighbours.push_back((*ei)->second);
        }

        // SOLO SI ES NO DIRIGIDO
        // Si el segundo nodo del edge es el nodo que se pasa por parametro
        // else if ((*ei)->second == node)
        // {
        //     // Agregar el primer nodo del edge al vector de vecinos
        //     neighbours.push_back((*ei)->first);
        // }
    }

    return neighbours;
}

/* getMinDistanceNode       - Obtiene el nodo con la menor distancia
   @ qs                     - Vector de nodos a los que se les calculara la distancia
  Complejidad O(n)
*/
Node *Graph::getMinDistanceNode(vector<Node *> qs)
{
    // Inicializar el nodo con la menor distancia con el primer nodo del vector
    Node *min = qs[0];

    // Iterador de Node
    vector<Node *>::iterator ni;

    // Recorrer el vector de nodos
    for (ni = qs.begin(); ni != qs.end(); ++ni)
    {
        // Si la distancia del nodo actual es menor a la del nodo con la menor distancia
        if ((*ni)->distance < min->distance)
        {
            // Actualizar el nodo con la menor distancia
            min = *ni;
        }
    }

    return min;
}

/* removeNode               - Elimina un nodo de un vector de nodos
   @ qs                     - Vector de nodos del cual se eliminara el nodo
   @ q                      - Nodo que se eliminara del vector
  Complejidad O(n)
*/
void Graph::removeNode(vector<Node *> &qs, Node *q)
{
    // Iterador de Node
    vector<Node *>::iterator ni;

    // Recorrer el vector de nodos
    for (ni = qs.begin(); ni != qs.end(); ++ni)
    {
        // Si el nodo actual es el nodo que se quiere eliminar
        if (*ni == q)
        {
            // Eliminar el nodo del vector
            qs.erase(ni);
            break;
        }
    }
}

/* getDistance              - Obtiene la distancia entre dos nodos
   @ source                 - Nodo fuente
   @ target                 - Nodo destino
  Complejidad O(n)
*/
int Graph::getDistance(Node *source, Node *target)
{
    // Iterador de Edge
    vector<Edge *>::iterator ei;

    // Recorrer los edges
    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        // Si el primer nodo del edge es el nodo fuente y el segundo nodo es el nodo destino
        if ((*ei)->first == source && (*ei)->second == target)
        {
            // Retornar la distancia del edge
            return (*ei)->weight;
        }

        // SI SI ES UN GRAFO NO DIRIGIDO
        // Si el primer nodo del edge es el nodo destino y el segundo nodo del edge es el nodo fuente
        // else if ((*ei)->first == target && (*ei)->second == source)
        // {
        //     // Retornar el peso del edge
        //     return (*ei)->getDistance();
        // }
    }

    return 100000;
}

/* dijkstra                 - Algoritmo de Dijkstra
   @ source                 - Nodo fuente
  Complejidad O(n^2)
*/
void Graph::dijkstra(Node *source)
{
    // Nodo referencia al source
    initialNode = source;

    // Vector para guardar los nodos que no han sido visitados
    vector<Node *> qs;

    // Poner la distancia y el prev de todos los nodos
    for (int v = 0; v < nodes.size(); v++)
    {
        // nodes[v]->distance = 1000;
        // nodes[v]->prev = nullptr;

        qs.push_back(nodes[v]);
    }
    // Inicializar el nodo fuente
    source->distance = 0;

    // Mientras qs no este vacio
    while (!qs.empty())
    {
        // Obtener el nodo con la menor distancia
        Node *u = getMinDistanceNode(qs);

        // Remover el nodo con la menor distancia del vector de nodos que no han sido visitados
        removeNode(qs, u);

        // Obtener los vecinos del nodo con la menor distancia
        vector<Node *> neighbours = getNeighbours(u);

        // Recorrer los vecinos
        for (int i = 0; i < neighbours.size(); i++)
        {
            // Obtener la distancia entre el nodo con la menor distancia y el vecino
            int alt = u->distance + getDistance(u, neighbours[i]);

            // Si la distancia entre el nodo con la menor distancia y el vecino es menor a la distancia del vecino
            if (alt < neighbours[i]->distance)
            {
                // Actualizar la distancia del vecino
                neighbours[i]->distance = alt;

                // Actualizar el nodo previo del vecino
                neighbours[i]->prev = u;
            }
        }
    }
}

/* print                    - Imprime el grafo mostrando los nodos y sus distancia
  Complejidad O(n)
*/
void Graph::print()
{
    // cout << "Nodes:" << endl;
    // for (int i = 0; i < nodes.size(); i++)
    // {
    //     for (int j = 0; j < nodes.size(); j++)
    //     {
    //         cout << "node " << nodes[i]->number << " to node " << nodes[j]->number
    //              << " distance: " << getDistance(nodes[i], nodes[j]) << endl;
    //     }
    //     cout << endl;

    // Iterador de Node
    vector<Node *>::iterator ni;

    // Recorrer los nodos
    for (ni = nodes.begin(); ni != nodes.end(); ++ni)
    {
        if ((*ni)->prev != nullptr || (*ni)->distance != 0)
        {
            cout << "Node: " << initialNode->number << " to Node: " << (*ni)->number << " distance: " << (*ni)->distance << endl;
        }
    }
}

/* floydWarshall            - Algoritmo de Floyd-Warshall
  Complejidad O(n^3)
*/
void Graph::floydWarshall()
{
    int n = nodes.size();
    vector<vector<int>> dist;
    int i, j, k;

    // Inicializar la matriz de distancias
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            vector<int> row(n, 1000);
            dist.push_back(row);
        }
    }

    // Poner la distancia entre un nodo y si mismo en 0
    for (i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }

    // Poner la distancia entre los nodos que estan conectados
    for (i = 0; i < edges.size(); i++)
    {
        dist[edges[i]->first->number - 1][edges[i]->second->number - 1] = edges[i]->weight;
    }

    // Recorrer los nodos
    for (k = 0; k < n; k++)
    {
        // Recorrer los nodos (renglones)
        for (i = 0; i < n; i++)
        {
            // Recorrer los nodos (columnas)
            for (j = 0; j < n; j++)
            {
                // Si la distancia entre el nodo i y el nodo k mas la distancia entre el nodo k y el nodo j es menor a la distancia entre el nodo i y el nodo j
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    // Actualizar la distancia entre el nodo i y el nodo j
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Imprimir la matriz de distancias
    cout << "\nFloyd Warshall: " << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

Edge *Graph::getEdge(Node *source, Node *target)
{
    // Iterador de Edge
    vector<Edge *>::iterator ei;

    // Recorrer los edges
    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        // Si el primer nodo del edge es el nodo fuente y el segundo nodo del edge es el nodo destino
        if ((*ei)->first == source && (*ei)->second == target)
        {
            // Retornar el edge
            return (*ei);
        }

        // SI SI ES UN GRAFO NO DIRIGIDO
        // Si el primer nodo del edge es el nodo destino y el segundo nodo del edge es el nodo fuente
        // else if ((*ei)->first == target && (*ei)->second == source)
        // {
        //     // Retornar el edge
        //     return (*ei);
        // }
    }

    return nullptr;
}

/*
vector<Node *> Graph::bfs(Node *source, Node *target)
{
    cout << "BFS: " << endl;

    // Vector de nodos visitados
    vector<Node *> visited;

    // Vector de nodos a visitar
    vector<Node *> toVisit;

    // Agregar el nodo fuente al vector de nodos a visitar
    toVisit.push_back(source);

    // Mientras el vector de nodos a visitar no este vacio
    while (!toVisit.empty())
    {
        // Obtener el primer nodo del vector de nodos a visitar
        Node *current = toVisit.front();

        // Remover el primer nodo del vector de nodos a visitar
        toVisit.erase(toVisit.begin());

        // Agregar el nodo actual al vector de nodos visitados
        visited.push_back(current);

        // Si el nodo actual es el nodo destino
        if (current == target)
        {
            cout << "Found" << endl;

            // Retornar el vector de nodos visitados
            return visited;
        }

        // Obtener los vecinos del nodo actual
        vector<Node *> neighbours = getNeighbours(current);

        // Iterador de Node
        vector<Node *>::iterator ni;

        // Recorrer los vecinos
        for (ni = neighbours.begin(); ni != neighbours.end(); ++ni)
        {
            // Si el vecino no ha sido visitado
            if (!isVisited(visited, (*ni)))
            {
                // Agregar el vecino al vector de nodos a visitar
                toVisit.push_back((*ni));
            }
        }
    }

    cout << "No path found" << endl;

    return visited;
}
*/

/* removeEdge               - Elimina un edge del grafo
  Complejidad O(n)
 */
void Graph::removeEdge(Edge *edge)
{
    // Iterador de Edge
    vector<Edge *>::iterator ei;

    // Recorrer los edges
    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        // Si el edge es igual al edge a eliminar
        if ((*ei) == edge)
        {
            // Eliminar el edge
            edges.erase(ei);
            break;
        }
    }
}

/* addEdge                  - Agrega un edge al grafo
  Complejidad O(1)
 */
void Graph::addEdge(Edge *edge)
{
    // Agregar el edge al vector de edges
    edges.push_back(edge);
}

int Graph::fordFulkerson(Node *source, Node *target)
{
    // Vector de nodos visitados
    vector<Node *> queue;

    vector<Node *>::iterator ni;
    // Iterador que apunta al primer elemento del vector de edges
    for (ni = nodes.begin(); ni != nodes.end(); ++ni)
    {
        (*ni)->distance = -1;
        (*ni)->prev = nullptr;

        queue.push_back((*ni));
    }

    // Mientras el vector de nodos a visitar no este vacio
    while (!queue.empty())
    {
        // Obtener el primer nodo del vector de nodos a visitar
        Node *current = queue.front();

        // Remover el primer nodo del vector de nodos a visitar
        queue.erase(queue.begin());

        // Obtener los vecinos del nodo actual
        vector<Node *> neighbours = getNeighbours(current);

        // Iterador de Node
        vector<Node *>::iterator v;

        // Recorrer los vecinos
        for (v = neighbours.begin(); v != neighbours.end(); ++v)
        {
            //
            (*v)->prev = current;

            if ((*v) == target)
            {
                vector<Edge *> path;

                Node *current = target;

                while (current != source)
                {
                    Edge *edge = getEdge(current->prev, current);

                    path.push_back(edge);

                    current = current->prev;
                }

                int min = 0;

                vector<Edge *>::iterator e;

                for (e = path.begin(); e != path.end(); ++e)
                {
                    if ((*e)->capacity > min)
                    {
                        cout << "->From " << (*e)->first->number << " to " << (*e)->second->number << endl;
                        cout << "Min: " << min << endl;
                        cout << "Capacity: " << (*e)->capacity << endl;

                        min += (*e)->capacity;
                    }
                }

                for (e = path.begin(); e != path.end(); ++e)
                {
                    cout << "->From " << (*e)->first->number << " to " << (*e)->second->number << endl;
                    cout << "Min: " << min << endl;
                    cout << "Capacity: " << (*e)->capacity << endl;

                    (*e)->capacity += min;
                }

                return min;
            }

            if ((*v)->distance == -1)
            {
                cout << "->From " << current->number << " to " << (*v)->number << endl;
                cout << "Distance: " << (*v)->distance << endl;

                (*v)->distance = current->distance + 1;

                queue.push_back((*v));
            }
        }
    }

    return 0;
}
