#include <vector>

using namespace std;

// Fuente utilizada (con ciertas modificaciones para la implementarlo en la tarea):
// GeeksforGeeks - matrix multiplication
// https://www.geeksforgeeks.org/cpp/cpp-matrix-multiplication/

vector<vector<int>> naiveMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
    int n = A.size();

    // Crear matriz resultado n x n llena de ceros
    vector<vector<int>> result(
        n,
        vector<int>(n, 0)
    );

    // Multiplicación Naive de matrices
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            for (int k = 0; k < n; k++) {

                result[i][j] +=
                    A[i][k] * B[k][j];
            }
        }
    }

    return result;
}