#include <vector>

using namespace std;

// Fuente utilizada (con ciertas modificaciones para la implementarlo en la tarea):
// Github - Strassen Matrix Multiplication
// https://github.com/dmonaldo/strassen-matrix-multiplication


// Suma dos matrices
vector<vector<int>> sumarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
    int n = A.size();

    vector<vector<int>> resultado(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultado[i][j] = A[i][j] + B[i][j];
        }
    }

    return resultado;
}


// Resta dos matrices
vector<vector<int>> restarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
    int n = A.size();

    vector<vector<int>> resultado(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultado[i][j] = A[i][j] - B[i][j];
        }
    }

    return resultado;
}


// Multiplicacion de matrices usando Strassen
vector<vector<int>> strassenMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
    int n = A.size();

    // Caso base de la recursion
    if (n == 1) {
        vector<vector<int>> resultado(1, vector<int>(1));

        resultado[0][0] = A[0][0] * B[0][0];

        return resultado;
    }

    int mitad = n / 2;


    // ------------------------------------
    // DIVIDIR MATRIZ A EN 4 PARTES
    // ------------------------------------

    vector<vector<int>> A11(mitad, vector<int>(mitad));
    vector<vector<int>> A12(mitad, vector<int>(mitad));
    vector<vector<int>> A21(mitad, vector<int>(mitad));
    vector<vector<int>> A22(mitad, vector<int>(mitad));


    // ------------------------------------
    // DIVIDIR MATRIZ B EN 4 PARTES
    // ------------------------------------

    vector<vector<int>> B11(mitad, vector<int>(mitad));
    vector<vector<int>> B12(mitad, vector<int>(mitad));
    vector<vector<int>> B21(mitad, vector<int>(mitad));
    vector<vector<int>> B22(mitad, vector<int>(mitad));


    // Guardar los valores en cada submatriz
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {

            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mitad];
            A21[i][j] = A[i + mitad][j];
            A22[i][j] = A[i + mitad][j + mitad];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mitad];
            B21[i][j] = B[i + mitad][j];
            B22[i][j] = B[i + mitad][j + mitad];
        }
    }


    // ------------------------------------
    // CALCULAR S1 ... S10
    // ------------------------------------

    vector<vector<int>> s1 = restarMatrices(B12, B22);
    vector<vector<int>> s2 = sumarMatrices(A11, A12);
    vector<vector<int>> s3 = sumarMatrices(A21, A22);
    vector<vector<int>> s4 = restarMatrices(B21, B11);
    vector<vector<int>> s5 = sumarMatrices(A11, A22);
    vector<vector<int>> s6 = sumarMatrices(B11, B22);
    vector<vector<int>> s7 = restarMatrices(A12, A22);
    vector<vector<int>> s8 = sumarMatrices(B21, B22);
    vector<vector<int>> s9 = restarMatrices(A11, A21);
    vector<vector<int>> s10 = sumarMatrices(B11, B12);


    // ------------------------------------
    // CALCULAR LAS 7 MULTIPLICACIONES
    // ------------------------------------

    vector<vector<int>> p1 = strassenMultiply(A11, s1);
    vector<vector<int>> p2 = strassenMultiply(s2, B22);
    vector<vector<int>> p3 = strassenMultiply(s3, B11);
    vector<vector<int>> p4 = strassenMultiply(A22, s4);
    vector<vector<int>> p5 = strassenMultiply(s5, s6);
    vector<vector<int>> p6 = strassenMultiply(s7, s8);
    vector<vector<int>> p7 = strassenMultiply(s9, s10);


    // ------------------------------------
    // CALCULAR C11
    // C11 = P5 + P4 - P2 + P6
    // ------------------------------------

    vector<vector<int>> temp1 = sumarMatrices(p5, p4);
    vector<vector<int>> temp2 = restarMatrices(temp1, p2);
    vector<vector<int>> C11 = sumarMatrices(temp2, p6);


    // ------------------------------------
    // CALCULAR C12
    // C12 = P1 + P2
    // ------------------------------------

    vector<vector<int>> C12 = sumarMatrices(p1, p2);


    // ------------------------------------
    // CALCULAR C21
    // C21 = P3 + P4
    // ------------------------------------

    vector<vector<int>> C21 = sumarMatrices(p3, p4);


    // ------------------------------------
    // CALCULAR C22
    // C22 = P5 + P1 - P3 - P7
    // ------------------------------------

    temp1 = sumarMatrices(p5, p1);
    temp2 = restarMatrices(temp1, p3);
    vector<vector<int>> C22 = restarMatrices(temp2, p7);


    // ------------------------------------
    // UNIR LAS 4 PARTES
    // ------------------------------------

    vector<vector<int>> resultado(n, vector<int>(n, 0));

    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {

            resultado[i][j] = C11[i][j];

            resultado[i][j + mitad] = C12[i][j];

            resultado[i + mitad][j] = C21[i][j];

            resultado[i + mitad][j + mitad] = C22[i][j];
        }
    }

    return resultado;
}