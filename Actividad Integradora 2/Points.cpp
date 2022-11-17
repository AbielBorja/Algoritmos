#include "Points.h"


Points::Points(vector<Point*> points)
{
    this->points = points;
    this->last = points.at(points.size()-1);
}

void Points::findClosest()
{
    double lowestDist = 10000.0;
    Point* closest;
    vector<Point*>::iterator it;
    for(it = this->points.begin(); it != this->points.end(); it++)
    {
        double currentDist = this->last->findDistance((*it));
        if(currentDist < lowestDist && currentDist != 0)
        {
            lowestDist = currentDist;
            closest = (*it);
        }
    }

    vector<Point*> newList;
    for(it = this->points.begin(); it != this->points.end(); it++)
    {
        if((*it)->x == closest->x && (*it)->y == closest->y)
        {
            newList.push_back((*it));
            newList.push_back(this->last);
        }else
        {
            if(this->last->x != (*it)->x && this->last->y != (*it)->y)
            {
                newList.push_back((*it));
            }
        }
    }


    for(it = newList.begin(); it != newList.end(); it++)
    {
        cout << "(" << (*it)->x << ", " << (*it)->y << ")" << endl;
    }

    cout << endl;
    cout << "El mas cercano a: " << "(" << last->x << ", " << last->y << ")" << " es: " << "(" << closest->x << ", " << closest->y << ")" << endl;

}