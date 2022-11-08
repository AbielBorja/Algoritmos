// Daniel Alejandro Martinez Rosete A01654093
// Abiel Moisés Borja García A01654937
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "Coord.h"

using namespace std;

int main()
{
    int pointsGen;
    cin >> pointsGen;
    cin.ignore();
    vector<Coord> coordList;
    // Complejidad O(n^2)
    // Teniendo como n el numero de iteraciones de datos de ingreso que el usuario determina
    // Teniendo como n iteraciones de separacion de delimiter para la separación de los numeros
    while (pointsGen--)
    {
        string str;
        float a, b;
        vector<float> numbers;
        getline(cin, str);
        replace(str.begin(), str.end(), ',', ' ');

        string delimiter = " ";
        size_t pos = 0;
        string token;
        while ((pos = str.find(delimiter)) != string::npos)
        {
            token = str.substr(0, pos);
            str.erase(0, pos + delimiter.length());
            if (token != "")
            {
                numbers.push_back(stof(token));
            }
        }
        token = str.substr(0, pos);
        if (token != "")
        {
            numbers.push_back(stof(token));
        }

        a = numbers.front();
        b = numbers.back();
        Coord temp = Coord(a, b);
        coordList.push_back(temp);
    }

    // Complejidad N*log(N)
    // En promedio, es lineal en la distancia entre el primero y el último: Realiza aproximadamente N*log2(N) (donde N es esta distancia) comparaciones de elementos, y hasta ese número de intercambios (o movimientos) de elementos.
    sort(coordList.begin(), coordList.end(),
         [](const Coord &x, const Coord &y)
         {
             return x.x < y.x;
         });

    size_t const half_size = coordList.size() / 2;
    vector<Coord> half1(coordList.begin(), coordList.begin() + half_size);
    vector<Coord> half2(coordList.begin() + half_size, coordList.end());

    vector<float> fhd;
    vector<float> shd;

    vector<Coord>::iterator iter1;

    // Complejidad O(n^2)
    // Donde determinaresmos el tamaño de las interaciones de las mitades
    for (iter1 = half1.begin(); iter1 != half1.end(); iter1++)
    {
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

    vector<Coord>::iterator iter3;

    // Complejidad O(n^2)
    // Donde determinaresmos el tamaño de las interaciones de las mitades
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
    float minsh = *min_element(shd.begin(), shd.end());
    float midd = half2.at(0).x;
    float d;
    if (minfh > minsh)
    {
        d = minsh;
    }
    else
    {
        d = minfh;
    }

    float middmd = midd - d;
    float middpd = midd + d;

    vector<Coord>::iterator ei;
    vector<Coord> strip;

    // O(n)
    // Donde n es el tamño de nuestro vector de condenadas
    for (ei = coordList.begin(); ei != coordList.end(); ei++)
    {
        if ((*ei).x >= middmd && (*ei).x <= middpd)
        {
            strip.push_back((*ei));
        }
    }
    
    // Complejidad N*log(N)
    // En promedio, es lineal en la distancia entre el primero y el último: Realiza aproximadamente N*log2(N) (donde N es esta distancia) comparaciones de elementos, y hasta ese número de intercambios (o movimientos) de elementos.
    sort(strip.begin(), strip.end(),
         [](const Coord &x, const Coord &y)
         {
             return x.y < y.y;
         });

    // vector<Coord>::iterator test2;
    // for (test2 = strip.begin(); test2 != strip.end(); test2++)
    // {
    //     cout << (*test2).toString() << endl;
    // }

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
            }
        }
    }

    float minDist = *min_element(candidates.begin(), candidates.end());
    cout << "Mid Dist: " << minDist;

    return 0;
}
