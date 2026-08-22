#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>

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

// Esta funcion es para guardar los tiempos de cada algoritmo en un archivo csv
void guardarTiempo(const string& archivoEntrada, const string& algoritmo, int n, double tiempo)
{
    ofstream archivo("data/measurements/sorting_measurements.csv", ios::app);

    if (!archivo.is_open()) {
        cerr << "Error al abrir archivo de mediciones." << endl;
        return;
    }

    archivo << archivoEntrada << "," << algoritmo << "," << n << "," << tiempo << "\n";
}

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

    auto inicioPatience = chrono::high_resolution_clock::now();

    vector<int> resultadoPatience = patienceSort(arrPatience);

    auto finPatience = chrono::high_resolution_clock::now();

    chrono::duration<double> tiempoPatience =
        finPatience - inicioPatience;

    cout << "Patience Sort: " << tiempoPatience.count() << " segundos" << endl;

    guardarTiempo(fs::path(ruta).filename().string(), "PatienceSort", arr.size(), tiempoPatience.count());


    // ------------------------------------
    // QUICK SORT
    // ------------------------------------

    vector<int> arrQuick = arr;

    auto inicioQuick = chrono::high_resolution_clock::now();

    quickSort(arrQuick, 0, arrQuick.size() - 1);

    auto finQuick = chrono::high_resolution_clock::now();

    chrono::duration<double> tiempoQuick = finQuick - inicioQuick;

    cout << "Quick Sort: " << tiempoQuick.count() << " segundos" << endl;

    guardarTiempo(fs::path(ruta).filename().string(), "QuickSort", arr.size(), tiempoQuick.count());

    // ------------------------------------
    // MERGE SORT
    // ------------------------------------

    vector<int> arrMerge = arr;

    auto inicioMerge = chrono::high_resolution_clock::now();

    mergeSort(arrMerge, 0, arrMerge.size() - 1);

    auto finMerge = chrono::high_resolution_clock::now();

    chrono::duration<double> tiempoMerge = finMerge - inicioMerge;

    cout << "Merge Sort: " << tiempoMerge.count() << " segundos" << endl;

    guardarTiempo(fs::path(ruta).filename().string(), "MergeSort", arr.size(), tiempoMerge.count());


    // ------------------------------------
    // STD::SORT
    // ------------------------------------

    vector<int> arrSort = arr;

    auto inicioSort = chrono::high_resolution_clock::now();

    vector<int> resultadoSort = sortArray(arrSort);

    auto finSort = chrono::high_resolution_clock::now();

    chrono::duration<double> tiempoSort = finSort - inicioSort;

    cout << "std::sort: " << tiempoSort.count() << " segundos" << endl;

    guardarTiempo(fs::path(ruta).filename().string(), "Sort", arr.size(), tiempoSort.count());


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

    ofstream archivoMediciones("data/measurements/sorting_measurements.csv");

    archivoMediciones << "archivo,algoritmo,n,tiempo\n";

    archivoMediciones.close();

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