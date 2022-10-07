#include <iostream>
#include "cTrie.h"
#include "cNode.h"
using namespace std;

int main()
{
    //Tarea:
    Node* r = new Node('*');
    Trie* t = new Trie(r);

    string a = "aba";
    string b = "abc";
    string c = "abd";
    string d = "ad";
    string e = "bad";
    string f = "bag";

    t->add(r,a);
    t->add(r,b);
    t->add(r,c);
    t->add(r,d);
    t->add(r,e);
    t->add(r,f);


    cout<<r->toString()<< endl;
    

    return 0;
}