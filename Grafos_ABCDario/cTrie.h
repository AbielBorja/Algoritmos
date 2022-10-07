#include <iostream>
#include <vector>
#include "cNode.h"

using namespace std;

#ifndef __TRIE
#define __TRIE

// La complejidad del TRIE es considerada como:
// n log n
// 26 log n
// Donde 26 es el abecedario y n el tamaño del arbol
class Trie
{
private:
    
public:
    Trie();
    bool isActive(Node* nodo);
    void createNodes(Node* nodo);
    void add(Node* raiz, string key);
    bool Activate(Node* nodo);
    void print(Node* raiz);
    bool Query(Node* nodo, int ckey, string key);

};

#endif