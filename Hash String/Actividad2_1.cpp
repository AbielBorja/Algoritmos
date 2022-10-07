// Daniel Alejandro Martinez Rosete A01654093
// Abiel Moisès Borja Garcìa A01654937
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <streambuf>
#include <iterator>
#include <sstream>
using namespace std;

// El función genera un vector de strings
vector<char> genCharVectorFromString(string s)
{
    vector<char> charsVector(s.begin(), s.end());
    return charsVector;
}

//Genera vector de un archivo recibido 
vector<char> genCharVectorFromFile(string filename, int n)
{
    ifstream t(filename);
    string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
    int last = n - (str.length() % n);
    string fillingStr;

    int sum = 0;
    while (n > 0) {
        sum = sum + (n % 10);
        n = n / 10;
    }

    for(int i = 0; i < last; i++)
    {
        fillingStr += to_string(sum);
    }
    str = str + fillingStr;
    return genCharVectorFromString(str);
}

// Imprime los caracteres del vector que se le envia
void printCharVector(vector<char>& v)
{
    for(const char &c: v)
    {
        if(c == '\n' || c == '\r') cout << setfill('|') << setw(2) << '*';
        else cout << setfill('|') << setw(2) << c;
    }
    cout << "|" << endl;
}

// Complejidad O(1)
// Genera numero hexadecimal, con respecto a numeros enteros
string int_to_hex(int i )
{
  stringstream stream;
    stream << std::hex << i;
    string result(stream.str());
    return result;
}

//Complejidad O(n^2)
// Crea una tabla con respecto a los vectores generados de acuerdo al archivo recibido.
// Se recibe los vectores y el tamaño de columnas que se quiere hacer la tabla
vector<vector<char> > makeHashTable(vector<char> vc, int n)
{
    // Vector en el que se agregaran cada caracter
    vector<vector<char> > table;

    for(int i = 0; i < vc.size(); i += n)
    {
        vector<char> row;
        for(int j=i;j < i+n;j++)
        { 
            if(vc[j] == '\n' || vc[j] == '\r')
            {
                // Si se encuentra un salto de linea dentro del texto se rellenara con un "@"
                row.push_back('@');
            }else
            {
                // Del caso contrario unicamente se agregara a los vectores
                row.push_back(vc[j]);
            }

        }
        // Una ves terminada cada renglon se agrega al nuevo vector de la tabla
        table.push_back(row);
        // Se va imprimiendo cada renglon
        printCharVector(row);
    }

    return table;
}

// Complejidad O(n^2+n)
// Se realiza la suma de cada columna para el realizamiento de hexadecimal de cada suma de las columnas
string hashString(vector<vector<char> > vc)
{
    // Se hace una suma vertical de cada una de las columnas
    vector<int> counts;
    for(int i = 0; i < vc.at(0).size(); i++)
    {
        int count = 0;
        for(int j = 0; j < vc.size(); j++)
        {
            // La suma de las columnas
            count += int(vc.at(j).at(i));
        }
        // Se guarda dentro del vector de cuentas
        counts.push_back(count);
    }

    // Se busca hacer string todas las sumas de las columnas hechas ya en hexadecimal
    string hash; 
    for(int i = 0; i < counts.size(); i++)
    {
        string hexaValue = "";
        hexaValue = int_to_hex(counts.at(i));
        hash += hexaValue[0];
        hash += hexaValue[1];
    }

    return hash;

}


int main()
{
    // Se abre archivo
    vector<char> file;
    file = genCharVectorFromFile("texto1.txt", 16);

    // Se crea la tabla
    vector<vector<char> > hashTable;
    hashTable = makeHashTable(file, 16);
    string hash;
    hash = hashString(hashTable);


    cout << endl;
    cout << endl;
    cout << hash << endl;
    cout << "Length of hash: " << hash.length() << endl;


    return 0;
}