// Daniel Alejandro Martinez Rosete A01654093

#include <iostream>
#include <vector>
#include "Node.h"
#include "Edge.h"
#include "Graph.h"


using namespace std;


int main()
{
    //Inicializamos ambos vectores vacios y se los ponemos al inicializador de un grafo
    vector<Node*> nodes;
    vector<Edge*> edges;

    Graph* g = new Graph(nodes, edges);
    
    //Pide los inputs y llena los vectores antes dados dependiendo de los inputs
    g->createGraph();

    /*
    7
    0,7,-1,5,-1,-1,-1
    7,0,8,9,7,-1,-1
    -1,8,0,-1,5,-1,-1
    5,9,-1,0,15,6,-1
    -1,7,5,15,0,8,9
    -1,-1,-1,6,8,0,11
    -1,-1,-1,-1,9,11,0
    */
    
    cout << endl;
    cout << endl;

    
    vector<Edge*> ed = g->runKruskal();
    g->printDs();

    
    

    vector<Edge*>::iterator it;
    for (it = ed.begin(); it != ed.end(); it++)
    {
        cout << (*it)->toString() << endl;
    }


    

    //g->print();
    

    return 0;
}