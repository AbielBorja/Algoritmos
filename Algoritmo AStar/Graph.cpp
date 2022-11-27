#include "Graph.h"

Graph::Graph(vector<Node *> _nodes, vector<Edge *> _edges)
{
    nodes = _nodes;
    edges = _edges;
}

//Complejidad O(n)
// Donde n es el tamaño de las conexiones
vector<Node *> Graph::getNeighbors(Node *n)
{
    // Creamos vectores vecinos y 
    vector<Node *> neighbors;
    vector<Edge *>::iterator ei;
    
    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        if ();
    }
    return neighbors;
}

// Complejidad O(n)
// Donde n es el tamaño de mi Q
Node *Graph::getMinDist(vector<Node *> qs)
{
    Node *temp;
    int d = 1000;
    for (auto x : qs)
    {
        if (x->distance < d)
        {
            temp = x;
            d = x->distance;
        }
            
    }

    return temp;
}

// Complejidad O(n)
// Donde n es el tamaño de la q
void Graph::remove(vector<Node *> &qs, Node *q)
{
    for (int i = 0; i < qs.size(); i++)
    {
        if (qs.at(i) == q)
        {
            qs.erase(qs.begin() + i);
            break;
        }
    }
}

// Complejidad O(n)
// Donde n es el tamaño de las conexiones
int Graph::getLegth(Node* u, Node* v)
{
    vector<Edge *>::iterator ei;
    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        if ((*ei)->first == u && (*ei)->second == v) return ((*ei)->weight);
        if ((*ei)->first == v && (*ei)->second == u) return ((*ei)->weight);
        
    }
    return 0;
}

// Complejidad O(n + m log(n))
// Donde n son los nodos del grafo
// DOnde m son las coneciones que tiene el graph
// Logaritmo por la cantidad de recurisividad que se tiene que hacer dentro de la función
void Graph::runAStar(Node *source, Node* goal, int numNodes)
{
    // Iniciamos el source con distancia 0
    source->distance = 0;
    vector<Node *> Q = nodes;
    source->g = 0;
    source->f = source->g + calculateHeuristic(source, goal, numNodes);
    
    //Mientras Q no este vacio seguimos con el calulo de peso
    while (!Q.empty())
    {
        Node *u = getMinDist(Q);
        vector<Node *> neighbors = getNeighbors(u);
        remove(Q, u);

        // DEBUGS
        //cout << "\nNodo con menor distancia ahora es: " << u->number << endl;

        // DEBUGS
        //cout << "Asi anda Q ";
        //for(auto x : Q) cout << x->number << " ";
        //cout << endl;

        //DEBUGS
        //for (auto neig : neighbors) cout << "Somos los vecinos " << neig->number << endl;

        vector<Node *>::iterator it;
        for (auto ni : neighbors)
        {
            it = std::find(Q.begin(), Q.end(), ni);
            if (it != Q.end())
            {
                int alt = u->distance + getLegth(u, ni);

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

// Complejidad  O(n)
// Donde n es el tamaño del vector de nodos
void Graph::print()
{
    for(auto node : nodes){
        
        if(node->prev != nullptr)
        {
            cout << "Node: " << node->number;
            cout << " to node " << node->number;
            cout << " : " << node->distance << endl;
        }
        
    }
    
}


float Graph::calculateHeuristic(Node* source, Node* goal, int numNodes)
{
    int x1 = source->number % numNodes;
    int y1 = source->number / numNodes;
    int x2 = goal->number % numNodes;
    int y2 = goal->number / numNodes;

    return sqrt(pow((x2 - x1),2) + pow((y2 - y1), 2));

}