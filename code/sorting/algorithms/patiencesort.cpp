#include <vector>
#include <climits>

using namespace std;

// Fuente consultada:
// GeeksforGeeks - Patience Sorting
// Agrega aquí el link exacto desde donde obtuviste la implementación.

vector<int> merge_piles(vector<vector<int>>& piles)
{
    vector<int> ans;

    while (!piles.empty()) {

        int minu = INT_MAX;
        int index = -1;

        // Buscar el menor elemento entre las "cimas" de las pilas
        for (int i = 0; i < piles.size(); i++) {

            int top = piles[i].back();

            if (top < minu) {
                minu = top;
                index = i;
            }
        }

        // Agregar el menor al arreglo resultado
        ans.push_back(minu);

        // Sacarlo de su pila
        piles[index].pop_back();

        // Si la pila quedó vacía, eliminarla
        if (piles[index].empty()) {
            piles.erase(piles.begin() + index);
        }
    }

    return ans;
}


vector<int> patienceSort(vector<int> arr)
{
    vector<vector<int>> piles;

    // Construcción de las pilas
    for (int i = 0; i < arr.size(); i++) {

        bool inserted = false;

        // Buscar la primera pila cuya cima sea mayor que arr[i]
        for (int j = 0; j < piles.size(); j++) {

            if (arr[i] < piles[j].back()) {

                piles[j].push_back(arr[i]);
                inserted = true;
                break;
            }
        }

        // Si no pudo insertarse en ninguna pila,
        // se crea una nueva
        if (!inserted) {

            vector<int> newPile;
            newPile.push_back(arr[i]);

            piles.push_back(newPile);
        }
    }

    // Fusionar las pilas para obtener el arreglo ordenado
    return merge_piles(piles);
}