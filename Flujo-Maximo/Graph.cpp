#include "Graph.h"

Graph::Graph(vector<Node *> _nodes, vector<Edge *> _edges)
{
    nodes = _nodes;
    edges = _edges;
}

// Complejidad O(n)
//  Donde n es el tamaño de las conexiones
vector<Node *> Graph::getNeighbors(Node *n)
{
    // Creamos vectores vecinos y
    vector<Node *> neighbors;
    vector<Edge *>::iterator ei;

    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        if ((*ei)->first == n)
            neighbors.push_back((*ei)->second);
    }
    return neighbors;
}

// Complejidad O(n)
// Donde n es el tamaño de mi Q
Edge *Graph::getMinCap(vector<Edge *> qs)
{
    Edge *temp;
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

// Complejidad O(n)
// Donde n es el tamaño del vector de edges
Edge *Graph::findEdge(Node *u, Node *v)
{
    Edge *result = NULL;
    for (int i = 0; i < this->edges.size(); i++)
    {
        if (this->edges.at(i)->first == u)
        {

            if (this->edges.at(i)->second == v)
            {
                return this->edges.at(i);
            }
        }
    }
    return result;
}

// Complejidad O(x^2*log(n+n*n-1+m*t)+3z)
// Donde x es el tamaño de la cantidad de edges que se envian
// Donde n es el tamaño de vectores de nodos
// Donde m es el tamaño de vectores de vecinos
// Donde t es el tamaño de vectores de edges
// DOnde z es el tamaño del vector de los los nodos del path
int Graph::runFordFulkerson(Node *source, Node *sink)
{
    // Iniciamos el source con distancia 0
    int max_flow = 0;
    vector<Node *> Q;
    vector<Node *>::iterator ni;
    vector<Edge *>::iterator ei;
    for (ei = edges.begin(); ei != edges.end(); ++ei)
    {
        (*ei)->residual_flow = (*ei)->capacity;
        while (bfs(source, sink))
        {
            int path_flow = 10000;
            Node *curr = sink;
            while (curr != source)
            {
                Edge *e1 = findEdge(curr->prev, curr);
                path_flow = min(path_flow, e1->residual_flow);

                curr = curr->prev;
            }
            curr = sink;
            while (curr != source)
            {
                Edge *e1 = findEdge(curr->prev, curr);
                e1->residual_flow -= path_flow;

                Edge *e2 = findEdge(curr, curr->prev);
                if (e2 != nullptr) e2->residual_flow += path_flow;
                curr = curr->prev;
            }
            max_flow += path_flow;
        }
    }
    return max_flow;
}

// Complejidad de O(n+n*n-1+m*t)
// Donde n es el tamaño de vectores de nodos
// Donde m es el tamaño de vectores de vecinos
// Donde t es el tamaño de vectores de edges
bool Graph::bfs(Node *s, Node *t)
{
    vector<Node *>::iterator ni;
    for (ni = nodes.begin(); ni != nodes.end(); ++ni)
    {
        (*ni)->visited = false;
    }

    vector<Node *> q;
    q.push_back(s);
    s->prev = nullptr;
    s->visited = true;

    while (q.size() > 0)
    {
        Node *u = q[0];
        remove(q, u);
        vector<Node *>::iterator v;
        vector<Node *> neighbors = getNeighbors(u);
        for (v = neighbors.begin(); v != neighbors.end(); ++v)
        {
            Edge *e = findEdge(u, *v);
            if (e != nullptr)
            {
                if ((*v)->visited == false && e->residual_flow > 0)
                {
                    q.push_back(*v);
                    (*v)->prev = u;
                    (*v)->visited = true;
                }
            }
        }
    }
    return t->visited == true;
}