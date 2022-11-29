#pragma once
#include "Graph.h"
#include <cmath>
using namespace std;

class AStar
{
public:
    Graph *g;
    AStar(Graph *g);
    vector<Node*> pathfind(Node* start, Node* end, int n);
    bool findNode(vector<Node*> &qs, Node* q);
    void remove(vector<Node*> &qs, Node* q);
    vector<Node*> neighbors(Node* n);
    void printMoves(vector<Node*> path, Node* start, int n);
    Node* lowestCost(vector<Node*> qs);
    vector<Node*> getNeighbors(Node* nodo, int n);
    float heuristic(Node *start, Node *goal, int n);
    float diagonal_cost(Node *start, Node *end, int n);

};
