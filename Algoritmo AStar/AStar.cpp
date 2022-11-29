#include "AStar.h"
#include "algorithm"

AStar::AStar(Graph *g)
{
    this->g = g;
}

//Complejidad O(N) donde N es el tamaño de qs
bool AStar::findNode(vector<Node*> &qs, Node* q)
{
    vector<Node*>::iterator iter;
    for (iter = qs.begin(); iter != qs.end(); iter++) {
        if ((*iter) == q) {
            return true;
        }
    }
    return false;
}

//Complejidad: O(n) (n = vector)
 //Recorre la fila buscando la "f" mínima
Node* AStar::lowestCost(vector<Node*> qs){
    Node* lowNode = qs[0];
    vector<Node*> :: iterator i;
    for(i = qs.begin() +1; i != qs.end(); ++i){
        if((*i)->f < lowNode->f ){
            //low = (*i)->f;
            lowNode = *i;
        } 
    }
    return lowNode;

}

//Esta función remueve un Nodo q de un vector qs, que tiene una complejidad de O(N)
//donde N es el número de elementos en el vector.
void AStar::remove(vector <Node*> & qs, Node * q) {
    vector<Node*>::iterator iter;
    for (iter = qs.begin(); iter != qs.end(); iter++) {
        if ((*iter) == q) {
            qs.erase(iter);
            break;
        }

    }

}

//Complejidad:  O(1)
float AStar::heuristic(Node *start, Node *goal, int n){
	float x1 = start->number % n;
	float y1 = floor(start->number / n);
	float x2 = goal->number % n;
	float y2 = floor( goal->number / n);
	float dx = x2 -x1 ;
	float dy = y2 -y1 ;
	float h = sqrt((dx * dx) + (dy* dy));
	return h;

}

//Complejidad:  O(1)
float AStar::diagonal_cost(Node *start, Node *end, int n){
	float x1 =start->number % n ;
	float x2 =end->number % n ;
	float dx = abs(x2-x1);
	float y1 = floor(start->number / n);
	float y2 = floor(end->number / n);
	float dy = abs(y2-y1);
	float minimo, maximo;
	if (dx < dy) {
    minimo = dx;
    maximo = dy;
  } else {
    minimo = dy;
    maximo = dx;
  }
	float diagonal = minimo;
    float straight = maximo - minimo;
	float cost = sqrt(2) * diagonal + straight;

  return cost;
}

//Complejidad O(N) donde N es el tamaño de neighbors de n
vector<Node*> AStar::neighbors(Node* n)
{
    
    vector<Node*> nei = n->neighbors;
    vector<Node*> dia = n->diagonals;




    vector<Node*>::iterator it;
    for(it = nei.begin(); it != nei.end(); it++)
    {
        if(findNode(dia, (*it)))
        {
            (*it)->g = n->g + diagonal_cost(n,(*it), this->g->n);
        }else
        {
            (*it)->g = n->g + 1;
        }
        if((*it)->number > n->number)
        {
            (*it)->parent = n;
        }
        
    }

    return nei;
}


// Complejidad de O(2n^2+m)
// Donde m es el tamaño de neighbors de n
// Donde n es el numero de vectores a recorrer
vector<Node*> AStar::pathfind(Node* start, Node* end, int n)
{
    vector<Node*> openList;
    vector<Node*> path;
    bool path_exist = false;
    openList.push_back(start);
    
    vector<Node*> closedList;

    start->g = 0;
    start->f = start->g + heuristic(start, end, n);
    
    while(openList.size() > 0)
    {
        
        vector<Node*>::iterator it;
        Node* current = lowestCost(openList);
        if(current == end){
            path_exist = true;
		}
        if (path_exist) {
            cout << "Path encontrado:" << endl;
            path.push_back(current);
            while(current->parent)
            {
                path.push_back(current->parent);
                current = current->parent;
            }
            reverse(path.begin(),path.end());
            printMoves(path, start, this->g->n);
            break;
        }

        remove(openList, current);
        closedList.push_back(current);

        vector<Node*> nei = neighbors(current);


        for(it = nei.begin(); it != nei.end(); it++)
        {
            if(!findNode(closedList, (*it)))
            {
                (*it)->f = (*it)->g + heuristic((*it), end, this->g->n);
                if(!findNode(openList, (*it)))
                {
                    openList.push_back((*it));
                }else
                {
                    Node* openNei = (*it);
                    if(openNei->g < (*it)->g)
                    {
                        openNei->g = (*it)->g;
                        openNei->parent = (*it)->parent;
                    }
                }
            }
            
        }

    }


    
    return path;

}

//Complejidad O(N) donde N es el tamaño de path
void AStar::printMoves(vector<Node*> path, Node* start, int n){
    
    vector<string> result;
    for (int i = 0; i < path.size(); i++) {
        int x = (start->number - 1) % n;
        int y = floor((start->number - 1) / n);
        int xNext = (path[i]->number - 1) % n;
        int yNext = floor((path[i]->number - 1) / n);
        if (xNext == x && yNext == y) {
            result.push_back("Start");
        } 
        else if (xNext == x && yNext == y + 1) {
            result.push_back("D");
        } 
        else if (xNext == x && yNext== y - 1) {
            result.push_back("U");
        } 
        else if (xNext == x + 1 && yNext == y) {
            result.push_back("R");
        } 
        else if (xNext== x - 1 && yNext == y) {
            result.push_back("L");
        }
        else if (xNext== x + 1 && yNext == y - 1){
            result.push_back("UR");
        }
        else if (xNext== x- 1 && yNext == y-1){
            result.push_back("UL");
        }
        else if (xNext== x- 1 && yNext == y+1){
            result.push_back("DL");
        }
        else if (xNext== x+ 1 && yNext == y+1){
            result.push_back("DR");
        }
        start = path[i];
    }

    for (int i = 0; i < result.size(); i++) {
        if(i == result.size()-1){
            cout << result[i];
        }
        else{
            cout << result[i] << ", ";
        }
    }
    cout << endl;
}
