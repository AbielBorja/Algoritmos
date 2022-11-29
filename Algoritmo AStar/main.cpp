// Daniel Alejandro Martinez Rosete A01654093
// Abiel Moisés Borja García A01654937

#include "AStar.h"
#include "Graph.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main(){

    vector<Node*> nodes;

    Graph* g = new Graph(nodes);
    
    //Pide los inputs y llena los vectores antes dados dependiendo de los inputs
    g->createGraph();

    //g->print();

    /*
    1,0,0,0
    1,1,0,1
    1,1,0,0
    0,1,1,1*/

    AStar* a = new AStar(g);
    a->pathfind(a->g->nodes.at(0), a->g->nodes.at(15), 4);


    



    return 0;
}