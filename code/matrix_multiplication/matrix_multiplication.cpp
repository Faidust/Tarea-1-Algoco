#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <thread>
#include <atomic>
#include <functional>

using namespace std;
namespace fs = std::filesystem;

// Funcion de naive.cpp
vector<vector<int>> naiveMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B);

// Funcion de strassen.cpp
vector<vector<int>> strassenMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B);


// Leer una matriz n x n desde archivo
vector<vector<int>> leerMatriz(const string& nombreArchivo, int n)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir " << nombreArchivo << endl;
        return {};
    }

    vector<vector<int>> matriz(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> matriz[i][j];
        }
    }

    archivo.close();

    return matriz;
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

// Revisa cuanta memoria esta usando el proceso mientras corre un algoritmo
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

// Guarda las mediciones de los algoritmos en un archivo csv
void guardarMedicion(const string& archivoEntrada, const string& algoritmo, int n, double tiempo, long memoria)
{
    ofstream archivo("data/measurements/matrix_measurements.csv", ios::app);

    if (!archivo.is_open()) {
        cerr << "Error al abrir archivo de mediciones." << endl;
        return;
    }

    archivo << archivoEntrada << "," << algoritmo << "," << n << "," << tiempo << "," << memoria << "\n";

    archivo.close();
}


// Obtener el tamaño de la matriz desde el nombre del archivo
int obtenerDimension(const string& nombreArchivo)
{
    int posicion = nombreArchivo.find('_');

    string numero = nombreArchivo.substr(0, posicion);

    return stoi(numero);
}


// Procesar un par de matrices
void procesarMatrices(const string& ruta1, const string& ruta2)
{
    string nombre1 = fs::path(ruta1).filename().string();
    string nombre2 = fs::path(ruta2).filename().string();

    int n = obtenerDimension(nombre1);

    // Leer las dos matrices
    vector<vector<int>> A = leerMatriz(ruta1, n);
    vector<vector<int>> B = leerMatriz(ruta2, n);

    if (A.empty() || B.empty()) {
        cerr << "Error al leer las matrices." << endl;
        return;
    }

    cout << endl;
    cout << "Matriz A: " << nombre1 << endl;
    cout << "Matriz B: " << nombre2 << endl;
    cout << "Dimension: " << n << " x " << n << endl;

    // NAIVE

    long memoriaInicialNaive = obtenerMemoriaKB();

    atomic<bool> ejecutandoNaive = true;

    atomic<long> memoriaMaximaNaive = memoriaInicialNaive;

    thread hiloNaive(monitorearMemoria, ref(ejecutandoNaive), ref(memoriaMaximaNaive));

    auto inicioNaive = chrono::high_resolution_clock::now();

    vector<vector<int>> resultadoNaive = naiveMultiply(A, B);

    auto finNaive = chrono::high_resolution_clock::now();

    ejecutandoNaive = false;

    hiloNaive.join();

    chrono::duration<double> tiempoNaive = finNaive - inicioNaive;

    long memoriaNaive = memoriaMaximaNaive.load() - memoriaInicialNaive;

    if (memoriaNaive < 0) {
        memoriaNaive = 0;
    }

    cout << "Naive: " << tiempoNaive.count() << " segundos" << endl;
    cout << "Memoria: " << memoriaNaive << " KB" << endl;

    guardarMedicion(nombre1, "Naive", n, tiempoNaive.count(), memoriaNaive);



    // STRASSEN

    long memoriaInicialStrassen = obtenerMemoriaKB();

    atomic<bool> ejecutandoStrassen = true;

    atomic<long> memoriaMaximaStrassen = memoriaInicialStrassen;

    thread hiloStrassen(monitorearMemoria, ref(ejecutandoStrassen), ref(memoriaMaximaStrassen));

    auto inicioStrassen = chrono::high_resolution_clock::now();

    vector<vector<int>> resultadoStrassen = strassenMultiply(A, B);

    auto finStrassen = chrono::high_resolution_clock::now();

    ejecutandoStrassen = false;

    hiloStrassen.join();

    chrono::duration<double> tiempoStrassen = finStrassen - inicioStrassen;

    long memoriaStrassen = memoriaMaximaStrassen.load() - memoriaInicialStrassen;

    if (memoriaStrassen < 0) {
        memoriaStrassen = 0;
    }

    cout << "Strassen: " << tiempoStrassen.count() << " segundos" << endl;
    cout << "Memoria: " << memoriaStrassen << " KB" << endl;

    guardarMedicion(nombre1, "Strassen", n, tiempoStrassen.count(), memoriaStrassen);

    // Comparar resultados
    if (resultadoNaive == resultadoStrassen) {
        cout << "Naive y Strassen dieron el mismo resultado." << endl;
    }
    else {
        cout << "ERROR: dieron resultados distintos." << endl;
    }
}

// El main se hizo pasando estos parametros y de esta forma para que al leer cada archivo, la memoria se reinicie y asi no acumule o guarde memoria de los archvios pasados.
int main(int argc, char* argv[])
{
    if (argc != 3) {
        cerr << "Uso: ./matrix_multiplication matriz1 matriz2" << endl;
        return 1;
    }

    string ruta1 = argv[1];
    string ruta2 = argv[2];

    procesarMatrices(ruta1, ruta2);

    return 0;
}