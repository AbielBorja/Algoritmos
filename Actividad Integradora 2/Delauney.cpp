#include "Delauney.h"

Delauney::Delauney(vector<Coord> coordList)
{
    this->coordList = coordList;
}


//Complejidad O(Nlog^2(N) + N^2/4 + N^2/4 + N + N + Nlog^2(N) + M^2 + K + 2 + N + N)
//Complejidad O(Nlog^2(N) + N^2/4 + N^2/4 + Nlog^2(N) + 4N + K + 2 + M^2)
//N es el tamaño de coordList
//M es el tamaño de strip
//K es el tamaño de candidates
float Delauney::findMin()
{
    //Complejidad(Nlog^2(N))
    stable_sort(coordList.begin(), coordList.end(),
         [](const Coord &x, const Coord &y)
         {
             return x.x < y.x;
         });


    int half_size = coordList.size() / 2;
    vector<Coord> half1(coordList.begin(), coordList.begin() + half_size);
    vector<Coord> half2(coordList.begin() + half_size, coordList.end());


    



    vector<float> fhd;
    vector<float> shd;

    //Complejidad total O(N^2/4)
    vector<Coord>::iterator iter1;
    //Complejidad O(N/2)
    for (iter1 = half1.begin(); iter1 != half1.end(); iter1++)
    {
        //Complejidad O(N/2)
        vector<Coord>::iterator iter2;
        for (iter2 = half1.begin(); iter2 != half1.end(); iter2++)
        {
            if ((*iter1).x != (*iter2).x || (*iter1).y != (*iter2).y)
            {
                float dist = (*iter1).getDist((*iter2));
                fhd.push_back(dist);
            }
        }
    }

    //Complejidad total O(N^2/4)
    vector<Coord>::iterator iter3;

    for (iter3 = half2.begin(); iter3 != half2.end(); iter3++)
    {
        vector<Coord>::iterator iter4;
        for (iter4 = half2.begin(); iter4 != half2.end(); iter4++)
        {
            if ((*iter3).x != (*iter4).x || (*iter3).y != (*iter4).y)
            {
                float dist = (*iter3).getDist((*iter4));
                shd.push_back(dist);
            }
        }
    }

    // Complejidad O(N)
    float minfh = *min_element(fhd.begin(), fhd.end());
    // Complejidad O(N)
    float minsh = *min_element(shd.begin(), shd.end());

    float midd = half2.at(0).x;

    float d;
    if (minfh < minsh)
    {
        d = minsh;
    }
    else
    {
        d = minfh;
    }


    float middmd = midd - d;
    float middpd = midd + d;

    //Complejidad O(N)
    vector<Coord>::iterator ei;
    vector<Coord> strip;
    for (ei = coordList.begin(); ei != coordList.end(); ei++)
    {
        if ((*ei).x >= middmd && (*ei).x <= middpd)
        {
            strip.push_back((*ei));
        }
    }

    //Complejidad(Nlog^2(N))
    stable_sort(strip.begin(), strip.end(),
         [](const Coord &x, const Coord &y)
         {
             return x.y < y.y;
         });

    //Complejidad O(M^2)
    vector<vector<Coord>> targetMatrix;
    vector<Coord>::iterator iter5;
    vector<float> candidates;
    for (iter5 = strip.begin(); iter5 != strip.end(); iter5++)
    {
        vector<Coord>::iterator iter6;
        for (iter6 = strip.begin(); iter6 != strip.end(); iter6++)
        {
            if ((*iter5).x != (*iter6).x || (*iter5).y != (*iter6).y)
            {
                float dist = (*iter5).getDist((*iter6));
                candidates.push_back(dist);
                vector<Coord> pair;
                pair.push_back(*iter5);
                pair.push_back(*iter6);
                targetMatrix.push_back(pair);
            }
            
        }
    }

    float minDist = 10000;
    vector<Coord> currentPair;
    
    //Complejidad O(K)
    for (int i = 0; i < candidates.size(); i++)   
    {
        if(candidates.at(i) < minDist)
        {
            minDist = candidates.at(i);
            currentPair = targetMatrix.at(i);
        }
    }


    Coord last = coordList.at(coordList.size()-1);

    Coord closest(0,0);

    //Complejidad O(2) por que siempre es 2
    vector<Coord>::iterator it;
    cout << "El mas cercano a: " << endl;
    for(it = currentPair.begin(); it != currentPair.end(); it++)
    {
        cout << (*it).toString() << endl;
        if(last.x != (*it).x || last.y != (*it).y)
        {
            closest = (*it);
        }
        cout << "es: " << endl;
    }
    //Complejidad O(N)
    vector<Coord> newList;
    for(it = this->coordList.begin(); it != this->coordList.end(); it++)
    {
        if((*it).x == closest.x && (*it).y == closest.y)
        {
            newList.push_back((*it));
            newList.push_back(last);
        }else
        {
            if(last.x != (*it).x && last.y != (*it).y)
            {
                newList.push_back((*it));
            }
        }
    }

    //Complejidad O(N)
    for(it = newList.begin(); it != newList.end(); it++)
    {
        cout << "(" << (*it).x << ", " << (*it).y << ")" << endl;
    }

    return minDist;
}