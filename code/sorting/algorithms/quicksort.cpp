#include <vector>
#include <algorithm>

using namespace std;

// Agrega aquí la fuente de donde obtuviste el algoritmo.
// Ejemplo:
// Fuente consultada:
// GeeksforGeeks - Quick Sort
// URL: ...

int partition(vector<int>& vec, int low, int high)
{
    // Se usa el ultimo elemento como pivote
    int pivot = vec[high];

    // i indica hasta donde llegan los elementos
    // menores o iguales al pivote
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Se coloca el pivote en su posicion definitiva
    swap(vec[i + 1], vec[high]);

    return i + 1;
}

void quickSort(vector<int>& vec, int low, int high)
{
    if (low < high) {

        // Se divide el arreglo usando el pivote
        int pi = partition(vec, low, high);

        // Ordenar la parte izquierda
        quickSort(vec, low, pi - 1);

        // Ordenar la parte derecha
        quickSort(vec, pi + 1, high);
    }
}