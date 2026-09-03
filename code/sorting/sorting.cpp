#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <thread>
#include <atomic>
#include <functional>

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

long obtenerMemoriaKB()
{
    ifstream archivo("/proc/self/status");

    string palabra;
    long memoriaKB = 0;

    while (archivo >> palabra) {
        if (palabra == "VmRSS:") {
            archivo >> memoriaKB;
            return memoriaKB;
        }
    }

    return 0;
}

void guardarMedicion(const string& archivoEntrada, const string& algoritmo, int n, double tiempo, double memoria)
{
    ofstream archivo("data/measurements/sorting_measurements.csv", ios::app);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de mediciones." << endl;
        return;
    }

    archivo << archivoEntrada << ","
            << algoritmo << ","
            << n << ","
            << tiempo << ","
            << memoria << "\n";

    archivo.close();
}

void monitorearMemoria(atomic<bool>& ejecutando, atomic<long>& memoriaMaximaKB)
{
    while (ejecutando) {

        ifstream archivo("/proc/self/status");

        string palabra;
        long memoriaActualKB = 0;

        while (archivo >> palabra) {
            if (palabra == "VmRSS:") {
                archivo >> memoriaActualKB;
                break;
            }
        }

        if (memoriaActualKB > memoriaMaximaKB.load()) {
            memoriaMaximaKB = memoriaActualKB;
        }

        this_thread::sleep_for(chrono::microseconds(100));
    }
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

    double memoriaInicialPatience = obtenerMemoriaKB();

    atomic<bool> ejecutandoPatience = true;

    atomic<long> memoriaMaximaPatience = memoriaInicialPatience;

    thread hiloPatience(monitorearMemoria, ref(ejecutandoPatience), ref(memoriaMaximaPatience));

    auto inicioPatience = chrono::high_resolution_clock::now();

    vector<int> resultadoPatience = patienceSort(arrPatience);

    auto finPatience = chrono::high_resolution_clock::now();

    ejecutandoPatience = false;

    hiloPatience.join();

    chrono::duration<double> tiempoPatience = finPatience - inicioPatience;

    long memoriaPatience = memoriaMaximaPatience.load() - memoriaInicialPatience;

    if (memoriaPatience < 0) {
        memoriaPatience = 0;
    }

    cout << "Patience Sort: " << tiempoPatience.count() << " segundos" << endl;
    cout << "Memoria: " << memoriaPatience << " KB" << endl;

    guardarMedicion(fs::path(ruta).filename().string(), "PatienceSort", arr.size(), tiempoPatience.count(), memoriaPatience);



    // ------------------------------------
    // QUICK SORT
    // ------------------------------------

    vector<int> arrQuick = arr;

    double memoriaInicialQuick = obtenerMemoriaKB();

    atomic<bool> ejecutandoQuick = true;

    atomic<long> memoriaMaximaQuick = memoriaInicialQuick;

    thread hiloQuick(monitorearMemoria, ref(ejecutandoQuick), ref(memoriaMaximaQuick));

    auto inicioQuick = chrono::high_resolution_clock::now();

    quickSort(arrQuick, 0, arrQuick.size() - 1);

    auto finQuick = chrono::high_resolution_clock::now();

    ejecutandoQuick = false;

    hiloQuick.join();

    chrono::duration<double> tiempoQuick = finQuick - inicioQuick;

    long memoriaQuick = memoriaMaximaQuick.load() - memoriaInicialQuick;

    if (memoriaQuick < 0) {
        memoriaQuick = 0;
    }

    cout << "Quick Sort: " << tiempoQuick.count() << " segundos" << endl;
    cout << "Memoria: " << memoriaQuick << " KB" << endl;

    guardarMedicion(fs::path(ruta).filename().string(), "QuickSort", arr.size(), tiempoQuick.count(), memoriaQuick);

    // ------------------------------------
    // MERGE SORT
    // ------------------------------------

    vector<int> arrMerge = arr;

    double memoriaInicialMerge = obtenerMemoriaKB();

    atomic<bool> ejecutandoMerge = true;

    atomic<long> memoriaMaximaMerge = memoriaInicialMerge;

    thread hiloMerge(monitorearMemoria, ref(ejecutandoMerge), ref(memoriaMaximaMerge));

    auto inicioMerge = chrono::high_resolution_clock::now();

    mergeSort(arrMerge, 0, arrMerge.size() - 1);

    auto finMerge = chrono::high_resolution_clock::now();

    ejecutandoMerge = false;

    hiloMerge.join();

    chrono::duration<double> tiempoMerge = finMerge - inicioMerge;

    long memoriaMerge = memoriaMaximaMerge.load() - memoriaInicialMerge;

    if (memoriaMerge < 0) {
        memoriaMerge = 0;
    }

    cout << "Merge Sort: " << tiempoMerge.count() << " segundos" << endl;
    cout << "Memoria: " << memoriaMerge << " KB" << endl;

    guardarMedicion(fs::path(ruta).filename().string(), "MergeSort", arr.size(), tiempoMerge.count(), memoriaMerge);


    // ------------------------------------
    // STD::SORT
    // ------------------------------------

    vector<int> arrSort = arr;

    double memoriaInicialSort = obtenerMemoriaKB();

    atomic<bool> ejecutandoSort = true;

    atomic<long> memoriaMaximaSort = memoriaInicialSort;

    thread hiloSort(monitorearMemoria, ref(ejecutandoSort), ref(memoriaMaximaSort));

    auto inicioSort = chrono::high_resolution_clock::now();

    vector<int> resultadoSort = sortArray(arrSort);

    auto finSort = chrono::high_resolution_clock::now();

    ejecutandoSort = false;

    hiloSort.join();

    chrono::duration<double> tiempoSort = finSort - inicioSort;

    long memoriaSort = memoriaMaximaSort.load() - memoriaInicialSort;

    if (memoriaSort < 0) {
        memoriaSort = 0;
    }

    cout << "std::sort: " << tiempoSort.count() << " segundos" << endl;
    cout << "Memoria: " << memoriaSort << " KB" << endl;

    guardarMedicion(fs::path(ruta).filename().string(), "Sort", arr.size(), tiempoSort.count(), memoriaSort);


    // ------------------------------------
    // COMPROBAR RESULTADOS
    // ------------------------------------

    if (resultadoPatience == arrQuick && arrQuick == arrMerge && arrMerge == resultadoSort) {

        cout << "Todos los algoritmos dieron el mismo resultado." << endl;
    }
    else {
        cout << "ERROR: Los algoritmos dieron resultados diferentes." << endl;
    }
}

// ------------------------------------
// MAIN
// ------------------------------------

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Uso: ./sorting archivo" << endl;
        return 1;
    }

    string ruta = argv[1];

    procesarArchivo(ruta);

    return 0;
}