#include <vector>

using namespace std;

// Fuente utilizada (con ciertas modificaciones para la implementarlo en la tarea):
// GeeksforGeeks - Merge Sort
// https://www.geeksforgeeks.org/dsa/merge-sort/

void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Vectores temporales
    vector<int> L(n1);
    vector<int> R(n2);

    // Copiar la parte izquierda
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    // Copiar la parte derecha
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    // Mezclar ambas partes en orden
    while (i < n1 && j < n2) {

        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    // Copiar lo que quede de L
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar lo que quede de R
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(vector<int>& arr, int left, int right)
{
    // Caso base
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    // Ordenar mitad izquierda
    mergeSort(arr, left, mid);

    // Ordenar mitad derecha
    mergeSort(arr, mid + 1, right);

    // Unir ambas mitades ordenadas
    merge(arr, left, mid, right);
}