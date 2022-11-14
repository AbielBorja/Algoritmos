#include "HeldKarp.h"

HeldKarp::HeldKarp(Graph *_g)
{
    g = _g;
}

vector<Node *> HeldKarp::findHamilton(Node *start)
{
    // Llama a findHamilton(start, size_i) donde size_i va de 0 a N-1
    // Guarda functionP para el tamaño de size_i
    /*
    vector<Node *>::iterator ni;
    for (ni = g->nodes.begin(); ni != g->nodes.end(); ni++)
    {
        if (*ni != start)
        {
            vector<int> set;
            FunctionG *fg = new FunctionG(start->number, set);
            Edge *e = g->findEdge((*ni), start);
            fg->result = e->weight;
            prev_results.push_back(fg);
        }
    }

    for (ni = g->nodes.begin(); ni != g->nodes.end(); ni++)
    {
        if (*ni != start)
        {
            vector<Node *>::iterator ni2;
            int set_element = (*ni)->number;
            for (ni2 = g->nodes.begin(); ni2 != g->nodes.end(); ni2++)
            {
                if (*ni2 != start && *ni2 != *ni && g->findEdge(*ni2, *ni) != nullptr)
                {
                    vector<int> set;
                    set.push_back(set_element);
                    FunctionG *fg = new FunctionG((*ni2)->number, set);
                    Edge *e = g->findEdge((*ni), start);
                    fg->result = e->weight;
                    prev_results.push_back(fg);
                }
            }
        }
    }
    */
}

void HeldKarp::findHamilton(Node* start, int size)
{

}