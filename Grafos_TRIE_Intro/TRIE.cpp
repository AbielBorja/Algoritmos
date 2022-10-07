#include <stdio.h>
#include "cNode.h"

using namespace std;

int main()
{
    Node* ast = new Node(' ');

    Node* a = new Node('a');
    Node* a2 = new Node('a');
    Node* b = new Node('b');
    Node* d = new Node('d');
    Node* c = new Node('c');

    Node* b2 = new Node('b');
    Node* a3 = new Node('a');
    Node* d2 = new Node('d');
    Node* g = new Node('g');

    ast->connections.push_back(a);
    a->connections.push_back(b);
    b->connections.push_back(a2);
    b->connections.push_back(c);
    b->connections.push_back(d);
    a->connections.push_back(d);

    ast->connections.push_back(b2);
    b2->connections.push_back(a3);
    a3->connections.push_back(d2);
    a3->connections.push_back(g);

    cout << ast->toString() << endl;

    return 0;

}