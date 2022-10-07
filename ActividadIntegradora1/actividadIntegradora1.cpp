// Daniel Alejandro Martinez Rosete A01654093
// Abiel Moisès Borja Garcìa A01654937

#include <iostream>
#include <vector>
#include <streambuf>
#include <iterator>
#include <fstream>
#include "actIntegradora.h"

using namespace std;




int main()
{
    vector<char> mcode1 = actIntegradora::genCharVectorFromFile("mcode1.txt");
    vector<char> mcode2 = actIntegradora::genCharVectorFromFile("mcode2.txt");
    vector<char> mcode3 = actIntegradora::genCharVectorFromFile("mcode3.txt");
    vector<char> transmission1 = actIntegradora::genCharVectorFromFile("transmission1.txt");
    vector<char> transmission2 = actIntegradora::genCharVectorFromFile("transmission2.txt");

    string transmission1String = actIntegradora::genStringFromFile("transmission1.txt");
    string transmission2String = actIntegradora::genStringFromFile("transmission2.txt");
    

    vector<int> trans1Code1 = actIntegradora::KMP(mcode1, transmission1);
    string trans1Code1Bool = "false";
    if (trans1Code1.size() > 0)
    {
        trans1Code1Bool = "true";
    }
    cout << endl;
    vector<int> trans1Code2 = actIntegradora::KMP(mcode2, transmission1);
    string trans1Code2Bool= "false";
    if (trans1Code2.size() > 0)
    {
        trans1Code2Bool = "true";
    }
    cout << endl;
    vector<int> trans1Code3 = actIntegradora::KMP(mcode3, transmission1);
    string trans1Code3Bool = "false";
    if (trans1Code3.size() > 0)
    {
        trans1Code3Bool = "true";
    }
    cout << endl;

    cout << "Es " << trans1Code1Bool << " que el archivo transmission1.txt contiene el codigo contenido en el archivo mcode1.txt y esta en el indice " << trans1Code1[0] << endl;
    cout << "Es " << trans1Code2Bool << " que el archivo transmission1.txt contiene el codigo contenido en el archivo mcode2.txt y esta en el indice " << trans1Code2[0] << endl;
    cout << "Es " << trans1Code3Bool << " que el archivo transmission1.txt contiene el codigo contenido en el archivo mcode3.txt y esta en el indice " << trans1Code3[0] << endl;

    vector<int> trans2Code1 = actIntegradora::KMP(mcode1, transmission2);
    string trans2Code1Bool = "false";
    if (trans2Code1.size() > 0)
    {
        trans2Code1Bool = "true";
    }
    cout <<endl;
    vector<int> trans2Code2 = actIntegradora::KMP(mcode2, transmission2);
    string trans2Code2Bool = "false";
    if (trans2Code2.size() > 0)
    {
        trans2Code2Bool = "true";
    }
    cout <<endl;
    vector<int> trans2Code3 = actIntegradora::KMP(mcode3, transmission2);
    string trans2Code3Bool = "false";
    if (trans2Code3.size() > 0)
    {
        trans2Code3Bool = "true";
    }
    cout << endl;

    cout << "Es " << trans2Code1Bool << " que el archivo transmission2.txt contiene el codigo contenido en el archivo mcode1.txt" << endl;
    cout << "Es " << trans2Code2Bool  << " que el archivo transmission2.txt contiene el codigo contenido en el archivo mcode2.txt" << endl;
    cout << "Es " << trans2Code3Bool  << " que el archivo transmission2.txt contiene el codigo contenido en el archivo mcode3.txt" << endl;

    cout <<endl;
    cout <<endl;

    int startTrans1 = 0;
    int endTrans1 = 1;

    actIntegradora::longestPalSubstr(transmission1String , startTrans1, endTrans1);
    cout << "El palindromo mas grande de transmission1 es: ";
    cout << transmission1String.substr(startTrans1, endTrans1) << endl;
    endTrans1 = (startTrans1 + endTrans1) - 1;
    cout << "Primer indice: " << startTrans1 << " Segundo indice: " << endTrans1 << endl;

    cout <<endl;
    cout <<endl;

    int startTrans2 = 0;
    int endTrans2 = 1;

    actIntegradora::longestPalSubstr(transmission2String , startTrans2, endTrans2);
    cout << "El palindromo mas grande de transmission2 es: ";
    cout << transmission2String.substr(startTrans2, endTrans2) << endl;
    endTrans2 = (startTrans2 + endTrans2) - 1;
    cout << "Primer indice: " << startTrans2 << " Segundo indice: " << endTrans2 << endl;

    cout << endl;
    cout << endl;

    
    vector<vector<string> > B;
    vector<vector<int> > C;
    cout << "Ejecutando table LCS" << endl;
    actIntegradora::makeLCSTables(transmission1String, transmission2String, B, C);

    // actIntegradora::printLCS(B, transmission1String, transmission1String.length(), transmission2String.length());

    cout <<"Termine tablas" << endl;
    actIntegradora::searchIndex(B, transmission1String.length(), transmission2String.length());

    return 0;
}