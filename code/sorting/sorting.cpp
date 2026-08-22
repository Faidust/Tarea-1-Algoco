#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

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

// ------------------------------------
// PROCESAR UN CASO DE PRUEBA
// ------------------------------------

void procesarArchivo(const string& ruta)
{
    vector<int> arr = leerArreglo(ruta);

    if (arr.empty()) {
        cerr << "No se pudo procesar: " << ruta << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "Archivo: " << fs::path(ruta).filename().string() << endl;
    cout << "Cantidad de elementos: " << arr.size() << endl;
    cout << "========================================" << endl;


    // ------------------------------------
    // PATIENCE SORT
    // ------------------------------------

    vector<int> arrPatience = arr;

    vector<int> resultadoPatience = patienceSort(arrPatience);

    cout << "Patience Sort terminado." << endl;


    // ------------------------------------
    // QUICK SORT
    // ------------------------------------

    vector<int> arrQuick = arr;

    quickSort(arrQuick, 0, arrQuick.size() - 1);

    cout << "Quick Sort terminado." << endl;


    // ------------------------------------
    // MERGE SORT
    // ------------------------------------

    vector<int> arrMerge = arr;

    mergeSort(arrMerge, 0, arrMerge.size() - 1);

    cout << "Merge Sort terminado." << endl;


    // ------------------------------------
    // STD::SORT
    // ------------------------------------

    vector<int> arrSort = arr;

    vector<int> resultadoSort = sortArray(arrSort);

    cout << "std::sort terminado." << endl;


    // ------------------------------------
    // COMPROBAR RESULTADOS
    // ------------------------------------

    if (resultadoPatience == arrQuick &&
        arrQuick == arrMerge &&
        arrMerge == resultadoSort) {

        cout << "Todos los algoritmos dieron el mismo resultado." << endl;
    }
    else {
        cout << "ERROR: Los algoritmos dieron resultados diferentes." << endl;
    }
}

// ------------------------------------
// MAIN
// ------------------------------------

int main()
{
    string carpetaEntrada = "data/array_input";

    if (!fs::exists(carpetaEntrada)) {
        cerr << "No existe la carpeta: " << carpetaEntrada << endl;
        return 1;
    }

    for (const auto& archivo : fs::directory_iterator(carpetaEntrada)) {

        if (archivo.path().extension() == ".txt") {
            procesarArchivo(archivo.path().string());
        }
    }

    return 0;
}