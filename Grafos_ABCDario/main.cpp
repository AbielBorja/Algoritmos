#include <iostream>
#include "cNode.h"
#include "cTrie.h"
using namespace std;

int main()
{
    Node* r = new Node();
    Trie* t = new Trie();

    string a = "ABA";
    string b = "ABC";
    string c = "ABD";
    string d = "AD";
    string e = "BAD";
    string f = "BAG";
    t->createNodes(r);
    t->add(r, a);
    t->add(r, b);
    t->add(r, c);
    t->add(r, d);
    t->add(r, e);
    t->add(r, f);

    t->print(r); // imprime    A|B|A|C|D|D|B|A||G|

    cout << endl;

    cout << t->Query(r, 0, "AC") << endl;
    cout << t->Query(r, 0, "ABG") << endl;
    cout << t->Query(r, 0, "ABAD") << endl;
    cout << t->Query(r, 0, "ABC") << endl;
    cout << t->Query(r, 0, "BGA") << endl;
    cout << t->Query(r, 0, "BAG") << endl;
    
    return 0;
}