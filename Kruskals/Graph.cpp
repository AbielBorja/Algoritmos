#include "Graph.h"
#include <algorithm>

bool comparator(const Edge* s1, const Edge* s2) {
    return s1->weight < s2->weight;
}

//Este es el constructor de un grafo que se le da un vector de nodos y un vector de aristas.
Graph::Graph(vector<Node*> nodes, vector<Edge*> edges) {
    this->nodes = nodes;
    this->edges = edges;
    this->ds = new DisjointSets();
}

//Imprime el grafo para hacer más fácil su visualización, tiene una complejidad de O(N*M)
//donde N es el número de nodos en el vector y M el número de aristas.
void Graph::print() {
    cout << "Nodes:" << endl;
    for (int i = 0; i < this->nodes.size(); i++) {
        cout << this->nodes.at(i)->toString() << endl;
    }

    cout << endl;
    cout << "Edges:" << endl;
    for (int i = 0; i < this->edges.size(); i++) {
        cout << this->edges.at(i)->toString() << endl;
    }

    cout << "----------------------------------------------" << endl;


}

void Graph::printDs()
{
    vector<vector<Node*> >::iterator it;
    for (it = ds->sets.begin(); it != ds->sets.end(); it++)
    {
        vector<Node*>::iterator is;
        for(is = (*it).begin(); is != (*it).end(); is++)
        {
            cout << (*is)->toString() << endl;
        }
        cout << endl;
    }
    
}

//Función que convierte un vector de strings a un vector de Ints, que tiene una complejidad O(N) donde N es el tamaño del vector de strings.
vector<int> Graph::convertStringsToInt(vector<string> strings)
{
    vector<int> ints;
    vector<string>::iterator it;
    for (it = strings.begin(); it != strings.end(); it++)
    {
        int i;
        string str = *it;
        std::istringstream(str) >> i;
        ints.push_back(i);
    }
    return ints;
    
}

//Función que parte l string con un separador con complejidad O(N) donde N es el tamaño del string.
vector<string> Graph::splitString(string s, string sep)
{
    vector<string> tokens;
    size_t pos = 0;
    string token;
    while((pos = s.find(sep)) != string::npos)
    {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + sep.length());
    }
    tokens.push_back(s);
    return tokens;
}

//Se acepta el input del número de nodos y luego las conexiones de cada uno, tiene una complejidad O(N + N^2) ya que primero se crean los nodos
//Luego la lista de aristas que se tiene que recorrer de nuevo N veces y además creando cada arista otras N veces.
void Graph::createGraph()
{
    int n;
    cout << "El número de nodos en el grafo: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        Node* temp = new Node(i+1);
        this->nodes.push_back(temp);
    }

    for (int i = 0; i < n; i++)
    {

        string row;
        cin >> row;
        string sep = ",";
        vector<string> numbers = splitString(row, sep);
        vector<int> ints = convertStringsToInt(numbers);
        for (int j = 0; j < ints.size(); j++)
        {
            if(ints.at(j) != -1 && ints.at(j) != 0){
                Edge* temp = new Edge(this->nodes.at(i), this->nodes.at(j),ints.at(j));
                this->edges.push_back(temp);
            }
        }
        
    }

}

Edge* Graph::getEdge(Node* u, Node* v) {
    Edge* result = new Edge(new Node(-1), new Node(-1), -1);
    for (int i = 0; i < this->edges.size(); i++) {
        if (this->edges.at(i)->first == u) {

            if (this->edges.at(i)->second == v) {
                return this->edges.at(i);
            }

        } else if (this->edges.at(i)->first == v) {

            if (this->edges.at(i)->second == u) {
                return this->edges.at(i);
            }

        }
    }
    return result;
}

vector<Edge*> Graph::runKruskal()
{
    vector<Edge*> F;
    sort(edges.begin(), edges.end(), *comparator);
    
    
    vector<Node*>::iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        ds->MakeSet((*it));
    }

    vector<Edge*>::iterator et;
    for (et = edges.begin(); et != edges.end(); et++)
    {
        Node* u = (*et)->first;
        Node* v = (*et)->second;
        if(ds->findSet(u) != ds->findSet(v))
        {
            Edge* temp = getEdge(u, v);
            F.push_back(temp);
            vector<Node*> uSet = ds->findSet(u);
            vector<Node*> vSet = ds->findSet(v);
            ds->makeUnion(uSet, vSet);
        }
    }

    return F;
    
}