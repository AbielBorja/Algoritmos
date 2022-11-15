#include "Graph.h"

Graph::Graph(vector<Node *> _nodes, vector<Edge *> _edges)
{
    nodes = _nodes;
    edges = _edges;
    this->ds = new DisjointSets();

}

bool comparator(const Edge* s1, const Edge* s2) {
    return s1->weight < s2->weight;
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


void Graph::resetNodes()
{

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
void Graph::runDijkstra(Node *source)
{
    // Iniciamos el source con distancia 0
    source->distance = 0;
    vector<Node *> Q = nodes;

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

// Complejidad O(n^3)
// Donde n es el tamaño de los vectores de los nodos;
// Complejidad alternativa O(n^3) + 2O(n)
// Donde n es el tamaño de los vectores de los nodos se agrega '2O(n) por el agregar de generar la matriz y los edges
void Graph::runFloyd()
{
    vector<vector<int>> matrix;
    for (int i = 0; i < nodes.size(); i++)
    {
        vector<int> row(nodes.size(), 10000);
        row[i] = 0;
        matrix.push_back(row);
    }

    for (auto ei : edges)
    {
        int row = ei->first->number-1;
        int column = ei->second->number-1;
        int value = ei->weight;

        matrix[row][column] = value;
    }
    for (int k = 0; k < nodes.size(); k++)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            for (int j = 0; j < nodes.size(); j++)
            {
                if (matrix[i][j] > (matrix[i][k] + matrix[k][j]))
                {
                    matrix[i][j] = (matrix[i][k] + matrix[k][j]);
                }
                
            }
            
        }
        
    }

    printFloyd(matrix);
}

// O(n^2)
// Print elemento de la matriz de Floyd
void Graph::printFloyd(vector<vector<int>> matrix)
{
    for (auto col : matrix)
    {
        for (auto rows : col)
        {
            cout << rows << " ";
        }
        cout << "\n";
    }
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

vector<Edge*> Graph::runKruskal()
{
    vector<Edge*> F;
    sort(edges.begin(), edges.end(), *comparator);
    
    
    vector<Node*>::iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        ds->MakeSet((*it));
    }

    vector<Edge*>::iterator et;
    for (et = edges.begin(); et != edges.end(); et++)
    {
        Node* u = (*et)->first;
        Node* v = (*et)->second;
        if(ds->findSet(u) != ds->findSet(v))
        {
            Edge* temp = findEdge(u, v);
            F.push_back(temp);
            vector<Node*> uSet = ds->findSet(u);
            vector<Node*> vSet = ds->findSet(v);
            ds->makeUnion(uSet, vSet);
        }
    }

    return F;
    
}