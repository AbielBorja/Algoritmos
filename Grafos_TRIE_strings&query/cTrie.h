#include "cNode.h"
using namespace std;

#ifndef __TRIE
#define __TRIE

class Trie
{
private:
    Node* raiz;
public:
    Trie(Node* raiz1);
    void print();
    void add(Node* raiz, string key);
    
};

Trie::Trie(Node* raiz1)
{
    raiz = raiz1;
}

void Trie::add(Node* raiz, string key)
{
    if(key.length() > 0)
    {
        for (int i = 0; i < raiz->connections.size(); i++)
        {
            if (raiz->connections[i]->getPayload() == key[0])
            {
                add(raiz->connections[i], key.substr(1, key.length()-1));
                return;
            }
            
        }
        
        Node* r = new Node(key[0]);
        raiz->connections.push_back(r);
        add(r, key.substr(1, key.length()-1));
    }
}


#endif