#include "Coord.h"

float genRandomFloat(float min, float max)
{
	float n = (float) rand() / RAND_MAX;
	float r = min + (max-min)*n;
	return r;
}

Coord::Coord(float minX, float maxX, float minY, float maxY)
{
    this->x = genRandomFloat(minX, maxX);
    this->y = genRandomFloat(minY, maxY);
}

Coord::Coord(float x, float y)
{
    this->x = x;
    this->y = y;
}


float Coord::getDist(Coord c)
{
    float squares = pow((c.y - this->y), 2) + pow((c.x - this->x), 2);
    float result = sqrt(squares);
    return result;
}

string Coord::toString()
{
    string s = "X: " + to_string(this->x) + ", Y: " + to_string(this->y);
    return s;
}