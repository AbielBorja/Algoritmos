#include <iostream>
#include <math.h>
using namespace std;

void display_root( float a, float b, float c)
{
    float base = b * b - 4 * a * c;
    if (base < 0){
        cout << "Not possible";
    }
    else{
        float x1 = (-b + sqrt(base))/(2*a);
        float x2 = (-b - sqrt(base))/(2*a);

        cout << x1 << endl;
        cout << x2 << endl;
        
    }
} 

int main()
{
    float a, b, c;
    a = b = c = 0;
    cin >> a;
    cin >> b;
    cin >> c;

    display_root(a,b,c);

    return 0;
}