// Daniel Alejandro Martinez Rosete A01654093
// Abiel Moisès Borja Garcìa A01654937

#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
using namespace std;

//>>> ENTEROS
int genRandomInt(int min, int max)
{
	int i = min + rand()%(max-min+1);
	return i;
}

vector<int> genRandomIntVector(int min, int max, int size)
{
	vector<int> vec;
	for(int i = 0; i < size; i++)
		vec.push_back(genRandomInt(min, max));
	return vec;
}

void printIntVector(vector<int>& vec)
{
	// Declaramos un iterador para recorrer el vector de enteros:
	vector<int>::iterator it;
	cout << "[";
	// Usando el iterador, recorremos el vector eficientemente.
	// Usando la notación *it accedemos al contenido del iterador.
	for(it = vec.begin(); it != vec.end(); ++it)
		cout << setfill(' ') << setw(5) << *it << " ";
	cout << "]" << endl;
}

//<<< ENTEROS


// the interval from [left to middle] and [middle+1 to right] in vec are sorted
// the function will merge both of these intervals
// such the interval from [left to right] in vec becomes sorted
void merge(vector<int>& vec, int left, int middle, int right) {
	
    // temp is used to temporary store the vector obtained by merging
    // elements from [left to middle] and [middle+1 to right] in vec
	vector<int> temp;

	int i, j;
	i = left;
	j = middle + 1;

	while (i <= middle && j <= right) {

		if (vec[i] <= vec[j]) {
			temp.push_back(vec[i]);
			++i;
		}
		else {
			temp.push_back(vec[j]);
			++j;
		}

	}

	while (i <= middle) {
		temp.push_back(vec[i]);
		++i;
	}

	while (j <= right) {
		temp.push_back(vec[j]);
		++j;
	}

	for (int i = left; i <= right; ++i)
		vec[i] = temp[i - left];

}

// the mergeSort function
// Sorts the array in the range [left to right] in vec using
// merge sort algorithm
void mergeSort(vector<int>& vec, int left, int right) {
	if (left < right) {
        // Si el indice derecho es mayor que nuestro indice izquierdo encontraremos
        // el punto medio del arreglo
		int middle = left + (right - left) / 2;
        cout << "L: " << to_string(left) << " R: " << to_string(right)
            << " M: " << to_string(middle) << endl;
		mergeSort(vec, left, middle);
		mergeSort(vec, middle + 1, right);
		merge(vec, left, middle, right);
	}
}

int main() {

	// Inicializa el generador de números aleatorios.
	// Usando la hora del reloj interno como semilla.
	srand(time(NULL));
	// Inicaliza parámetros comunes:
	int min = -100;
	int max = 100;
	int size = 5;
	// Genera y muestra vectores de enteros y flotantes al azar:
	vector<int> elVector1 = genRandomIntVector(min, max, size);
	printIntVector(elVector1);
	cout << endl;

	mergeSort(elVector1, 0, size);

	cout << "\nVector Obtained After Sorting: " << endl;
	printIntVector(elVector1);

    return 0;
}