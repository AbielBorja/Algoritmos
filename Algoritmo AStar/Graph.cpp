#include "Graph.h"


//Este es el constructor de un grafo que se le da un vector de nodos y un vector de aristas.
Graph::Graph(vector<Node*> nodes) {
    this->nodes = nodes;
}


//Imprime el grafo para hacer más fácil su visualización, tiene una complejidad de O(N*M)
//donde N es el número de nodos en el vector y M el número de aristas.
void Graph::print() {
    cout << "Nodes:" << endl;
    for (int i = 0; i < this->nodes.size(); i++) {
        cout << this->nodes.at(i)->toString() << endl;
    }

    cout << "----------------------------------------------" << endl;


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
    this->n = n;
    vector<vector<int>> helpMatrix;
    vector<vector<Node*>> nodeMatrix;
    int nodeNum = 1;
    for (int i = 0; i < n; i++)
    {
        vector<int> tempVec;
        vector<Node*> nodeTemp;
        for (int j = 0; j < n; j++)
        {
            Node* temp = new Node(nodeNum);
            tempVec.push_back(nodeNum);
            nodeNum++;
            this->nodes.push_back(temp);
            nodeTemp.push_back(temp);
            
            
        }
        helpMatrix.push_back(tempVec);
        nodeMatrix.push_back(nodeTemp);
    }
    this->nodeMatrix = nodeMatrix;
    cout << endl;
    // vector<vector<int>>::iterator ei;
    // vector<int>::iterator it;

    // for(ei = helpMatrix.begin(); ei != helpMatrix.end(); ei++)
    // {
    //     for(it = (*ei).begin(); it != (*ei).end(); it++)
    //     {
    //         cout << (*it) << " ";
    //     }
    //     cout << endl;
    // }

    
    nodeNum = 0;
    for (int i = 0; i < n; i++)
    {

        string row;
        cin >> row;
        string sep = ",";
        vector<string> numbers = splitString(row, sep);
        vector<int> ints = convertStringsToInt(numbers);
        
        for (int j = 0; j < ints.size(); j++)
        {
            this->nodes.at(nodeNum)->wall = ints.at(j);
            nodeNum++;
        }
        
    }

    int realSize = n - 1;
    for (int i = 0; i < helpMatrix.size(); i++)
    {
        for(int j = 0; j < helpMatrix.at(0).size(); j++)
        {
            int curr = helpMatrix.at(i).at(j);
            if(this->nodes.at(curr - 1)->wall == 1)
            {
                //UL
                if(i - 1 >= 0 && j - 1 >= 0 && i - 1 <= realSize && j - 1 <= realSize)
                {
                    if(this->nodes.at(helpMatrix.at(i-1).at(j-1)-1)->wall == 1)
                    {
                        this->nodes.at(curr - 1)->neighbors.push_back(this->nodes.at(helpMatrix.at(i-1).at(j-1)-1));
                        this->nodes.at(curr - 1)->diagonals.push_back(this->nodes.at(helpMatrix.at(i-1).at(j-1)-1));
                    }
                }

                //U
                if(i - 1 >= 0 && j >= 0 && i - 1 <= realSize && j <= realSize)
                {
                    if(this->nodes.at(helpMatrix.at(i-1).at(j)-1)->wall == 1)
                    {
                        this->nodes.at(curr - 1)->neighbors.push_back(this->nodes.at(helpMatrix.at(i-1).at(j)-1));
                    }
                }

                //UR
                if(i - 1 >= 0 && j + 1 >= 0 && i - 1 <= realSize && j + 1 <= realSize)
                {
                    if(this->nodes.at(helpMatrix.at(i-1).at(j+1)-1)->wall == 1)
                    {
                        this->nodes.at(curr - 1)->neighbors.push_back(this->nodes.at(helpMatrix.at(i-1).at(j+1)-1));
                        this->nodes.at(curr - 1)->diagonals.push_back(this->nodes.at(helpMatrix.at(i-1).at(j+1)-1));
                    }
                }

                //L
                if(i >= 0 && j - 1 >= 0 && i <= realSize && j - 1 <= realSize)
                {
                    if(this->nodes.at(helpMatrix.at(i).at(j-1)-1)->wall == 1)
                    {
                        this->nodes.at(curr - 1)->neighbors.push_back(this->nodes.at(helpMatrix.at(i).at(j-1)-1));
                    }
                }

                //R
                if(i >= 0 && j + 1 >= 0 && i <= realSize && j + 1 <= realSize)
                {
                    if(this->nodes.at(helpMatrix.at(i).at(j+1)-1)->wall == 1)
                    {
                        this->nodes.at(curr - 1)->neighbors.push_back(this->nodes.at(helpMatrix.at(i).at(j+1)-1));
                    }
                }

                //DL
                if(i + 1 >= 0 && j - 1 >= 0 && i + 1 <= realSize && j - 1 <= realSize)
                {
                    
                    if(this->nodes.at(helpMatrix.at(i+1).at(j-1)-1)->wall == 1)
                    {
                        this->nodes.at(curr - 1)->neighbors.push_back(this->nodes.at(helpMatrix.at(i+1).at(j-1)-1));
                        this->nodes.at(curr - 1)->diagonals.push_back(this->nodes.at(helpMatrix.at(i+1).at(j-1)-1));
                    }
                }

                //D
                if(i + 1 >= 0 && j >= 0 && i + 1 <= realSize && j <= realSize)
                {
                    
                    if(this->nodes.at(helpMatrix.at(i+1).at(j)-1)->wall == 1)
                    {
                        this->nodes.at(curr - 1)->neighbors.push_back(this->nodes.at(helpMatrix.at(i+1).at(j)-1));
                    }
                }

                //DR
                if(i + 1 >= 0 && j + 1 >= 0 && i + 1 <= realSize && j + 1 <= realSize)
                {
                    if(this->nodes.at(helpMatrix.at(i+1).at(j+1)-1)->wall == 1)
                    {
                        this->nodes.at(curr - 1)->neighbors.push_back(this->nodes.at(helpMatrix.at(i+1).at(j+1)-1));
                        this->nodes.at(curr - 1)->diagonals.push_back(this->nodes.at(helpMatrix.at(i+1).at(j+1)-1));
                    }
                }


            }

        }
    }
    
}