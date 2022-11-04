// Daniel Alejandro Martinez Rosete A01654093

#include <iostream>
#include <random>
#include <vector>
#include "Coord.h"

using namespace std;



int main()
{
    int pointsGen = 10;
    vector<Coord> coordList;
    for (int i = 0; i < pointsGen; i++)
    {
        Coord c1 = Coord(0, 50, 0, 50);
        cout << c1.toString() << endl;
        coordList.push_back(c1);
    }

    std::sort(coordList.begin(), coordList.end(),
            [](const Coord &x, const Coord &y) {
                return x.x < y.x;
            });

    cout << endl;
    cout << endl;

    for (int i = 0; i < pointsGen; i++)
    {
        cout << coordList.at(i).toString() << endl;
    }

    cout << endl;
    cout << endl;

    size_t const half_size = coordList.size() / 2;
    vector half1(coordList.begin(), coordList.begin() + half_size);
    vector half2(coordList.begin() + half_size, coordList.end());

    vector<float> fhd;
    vector<float> shd;

    vector<Coord>::iterator iter1;

    for(iter1 = half1.begin(); iter1 != half1.end(); iter1++)
    {
        vector<Coord>::iterator iter2;
        for(iter2 = half1.begin(); iter2 != half1.end(); iter2++)
        {
            if((*iter1) != (*iter2))
            {
                float dist = (*iter1).getDist((*iter2));
                fhd.push_back(dist);
            }
        }
    }

    vector<Coord>::iterator iter3;

    for(iter3 = half2.begin(); iter3 != half2.end(); iter3++)
    {
        vector<Coord>::iterator iter4;
        for(iter4 = half2.begin(); iter4 != half2.end(); iter4++)
        {
            if((*iter3) != (*iter4))
            {
                float dist = (*iter3).getDist((*iter4));
                shd.push_back(dist);
            }
        }
    }

    vector<float>::iterator

    return 0;

}
