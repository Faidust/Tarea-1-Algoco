#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Función implementada en patiencesort.cpp
vector<int> patienceSort(vector<int> arr);

// Función implementada en quicksort.cpp
void quickSort(vector<int>& arr, int low, int high);

// Función implementada en mergesort.cpp
void mergeSort(vector<int>& arr, int left, int right);

// Función implementada en sort.cpp
vector<int> sortArray(vector<int>& arr);


// Lee todos los números de un archivo y los guarda en un vector
vector<int> leerArreglo(const string& nombreArchivo)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo." << endl;
        return {};
    }

    vector<int> arr;
    int numero;

    while (archivo >> numero) {
        arr.push_back(numero);
    }

    archivo.close();

    return arr;
}


// Muestra el arreglo en consola
void mostrarArreglo(const vector<int>& arr)
{
    for (int numero : arr) {
        cout << numero << " ";
    }

    cout << endl;
}


int main(int argc, char* argv[])
{
    // Verifica que hayas indicado un archivo
    if (argc < 2) {
        cerr << "Uso: ./sorting <archivo_de_entrada>" << endl;
        return 1;
    }

    string nombreArchivo = argv[1];

    // Leer arreglo desde uno de los casos de prueba de la tarea
    vector<int> arr = leerArreglo(nombreArchivo);

    if (arr.empty()) {
        cerr << "El arreglo esta vacio o hubo un error al leerlo." << endl;
        return 1;
    }

    cout << "Arreglo original:" << endl;
    mostrarArreglo(arr);

    // ------------------------------------
    // PATIENCE SORT
    // ------------------------------------

    // Ejecutar Patience Sort
    vector<int> resultado = patienceSort(arr);

    cout << "\nArreglo ordenado con Patience Sort:" << endl;
    mostrarArreglo(resultado);

    // ------------------------------------
    // QUICK SORT
    // ------------------------------------

    vector<int> arrQuick = arr;

    quickSort(arrQuick, 0, arrQuick.size() - 1);

    cout << "\nArreglo ordenado con Quick Sort:" << endl;
    mostrarArreglo(arrQuick);

    // ------------------------------------
    // MERGE SORT
    // ------------------------------------

    vector<int> arrMerge = arr;

    mergeSort(arrMerge, 0, arrMerge.size() - 1);

    cout << "\nArreglo ordenado con Merge Sort:" << endl;
    mostrarArreglo(arrMerge);

    // ------------------------------------
    // STD::SORT
    // ------------------------------------

    vector<int> arrSort = arr;

    vector<int> resultadoSort = sortArray(arrSort);

    cout << "\nArreglo ordenado con Sort:" << endl;
    mostrarArreglo(resultadoSort);


    return 0;
}