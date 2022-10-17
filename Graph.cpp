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
        if ((*ei)->first == n) neighbors.push_back((*ei)->second);
    }
    return neighbors;
}

// Complejidad O(n)
// Donde n es el tamaño de mi Q
Edge* Graph::getMinCap(vector<Edge *> qs)
{
    Edge* temp;
    int cap = 10000;
    for (auto x : qs)
    {
        if (x->capacity < cap)
        {
            temp = x;
            cap = x->capacity;
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

Edge* Graph::findEdge(Node* u, Node* v) {
    Edge* result = NULL;
    for (int i = 0; i < this->edges.size(); i++) {
        if (this->edges.at(i)->first == u) {

            if (this->edges.at(i)->second == v) {
                return this->edges.at(i);
            }

        }
    }
    return result;
}

void Graph::processPath(vector<Edge*> path)
{
    vector<Edge*>::iterator it;
    for(it = path.begin(); it != path.end(); it++)
    {
        if((*it)->capacity > 0)
        {
            return;
        }
    }

    Edge* minEdge = getMinCap(path);

    vector<Edge*>::iterator is;
    for(is = path.begin(); is != path.end(); is++)
    {
        (*is)->capacity += minEdge->capacity;
        Edge* temp = NULL;
        temp = findEdge((*is)->second, (*is)->first);
        if(temp != NULL)
        {
            (*is)->capacity -= minEdge->capacity;
        }
    }

    
}

int Graph::runFordFulkerson(Node* s, Node* t)
{
    vector<Node*> q;
    vector<Node*>::iterator ni;

    for (ni = nodes.begin(); ni != nodes.end(); ni++)
    {
        (*ni)->distance = -1;
        (*ni)->prev = NULL;
        q.push_back(*ni);

    }

    while(!q.empty())
    {
        Node* u = q[0];
        remove(q, u);
        vector<Node*> neigh = getNeighbors(u);
        vector<Node*>::iterator v;
        for (v = neigh.begin(); v != neigh.end(); v++)
        {
            (*v)->prev = u;
            if((*v) == t)
            {
                vector<Edge*> path;
                Node* current = t;
                while(current != s)
                {
                    Edge* e = findEdge(current->prev, current);
                    path.push_back(e);
                    current = current->prev;
                }
                processPath(path);
            }
        }
        
    }
    
}