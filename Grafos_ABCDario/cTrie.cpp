#include "cTrie.h"

Trie::Trie()
{
}

// Se crean los nodos del abecerio
// Complejidad:
// o(n) = o(26)
// son 26 caracteres de abecedario
void Trie::createNodes(Node *nodo)
{
    for (int i = 0; i < 26; i++)
    {
        Node *temp = new Node();
        nodo->connections.push_back(temp);
    }
}

// La complejidad del TRIE es considerada como:
// n log n
// 26 log n
// Donde 26 es el abecedario y n el tamaño del arbol
void Trie::add(Node *raiz, string key)
{

    int valueACCII = key[0] - 65;
    for (int i = 0; i < raiz->connections.size(); i++)
    {
        if (i == valueACCII && raiz->connections[i]->active == false)
        {
            // cout << key << endl;
            // cout << "| FALSE |" << endl;
            raiz->connections[i]->active = true;
            createNodes(raiz->connections[i]);
            add(raiz->connections[i], key.substr(1, key.length() - 1));
            return;
        }
        if (i == valueACCII && raiz->connections[i]->active == true)
        {
            // cout << key << endl;
            // cout << "| TRUE |" << endl;
            add(raiz->connections[i], key.substr(1, key.length() - 1));
            return;
        }
    }
}

// El tamaño de las conección definira la compejidad
// o(26)
void Trie::print(Node *raiz)
{
    for (int c = 0; c < raiz->connections.size(); c++)
    {
        char ckey = (c + 65);
        if (raiz->connections[c]->active == true)
        {
            cout << "|" << ckey;
            print(raiz->connections[c]);
        }
    }
}

// Una complejidad recursiva con respecto al los caracteres que intentan buscar
// O log(n)
bool Trie::Query(Node *nodo, int letter, string data)
{

    int c = int(data[letter] - 65);
    if (letter == data.length())
        return true;

    if (nodo->connections[c]->active == true)
    {
        return Query(nodo->connections[c], letter + 1, data);
    }
    else
    {
        return false;
    }
}