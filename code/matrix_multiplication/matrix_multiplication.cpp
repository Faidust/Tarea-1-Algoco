#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

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
    string nombreArchivo = fs::path(ruta1).filename().string();

    int n = obtenerDimension(nombreArchivo);

    // Leer las dos matrices
    vector<vector<int>> A = leerMatriz(ruta1, n);
    vector<vector<int>> B = leerMatriz(ruta2, n);

    if (A.empty() || B.empty()) {
        cerr << "Error al leer las matrices." << endl;
        return;
    }

    cout << endl;
    cout << "Matriz A: " << fs::path(ruta1).filename().string() << endl;
    cout << "Matriz B: " << fs::path(ruta2).filename().string() << endl;
    cout << "Dimension: " << n << " x " << n << endl;

    // Multiplicacion Naive
    vector<vector<int>> resultadoNaive = naiveMultiply(A, B);

    cout << "Naive terminado." << endl;

    // Multiplicacion Strassen
    vector<vector<int>> resultadoStrassen = strassenMultiply(A, B);

    cout << "Strassen terminado." << endl;

    // Comparar resultados
    if (resultadoNaive == resultadoStrassen) {
        cout << "Naive y Strassen dieron el mismo resultado." << endl;
    }
    else {
        cout << "ERROR: dieron resultados distintos." << endl;
    }
}


int main()
{
    string carpeta = "data/matrix_input";

    // Recorrer todos los archivos de la carpeta
    for (const auto& archivo : fs::directory_iterator(carpeta)) {

        string nombre = archivo.path().filename().string();

        // Revisar solamente archivos que terminen en _1.txt
        if (nombre.size() >= 6 && nombre.substr(nombre.size() - 6) == "_1.txt") {

            // Crear el nombre del archivo _2
            string nombre2 = nombre;

            nombre2.replace(nombre2.size() - 6, 6, "_2.txt");

            string ruta1 = archivo.path().string();
            string ruta2 = carpeta + "/" + nombre2;

            // Si existe el archivo _2, procesar el par
            if (fs::exists(ruta2)) {
                procesarMatrices(ruta1, ruta2);
            }
        }
    }

    return 0;
}