#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // sort, random_shuffle
#include <chrono>
#include <random>

using namespace std;

// Generar un array ordenado
vector<int> generateOrderedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}

// Generar un array parcialmente ordenado
vector<int> generatePartiallyOrderedArray(int size) {
    vector<int> arr = generateOrderedArray(size);
    random_shuffle(arr.begin() + size / 4, arr.end() - size / 4);
    return arr;
}

// Generar un array inversamente ordenado
vector<int> generateReversedArray(int size) {
    vector<int> arr = generateOrderedArray(size);
    reverse(arr.begin(), arr.end());
    return arr;
}

// Guardar arrays en un archivo
void saveArraysToFile(const vector<vector<int>>& arrays, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& arr : arrays) {
            for (const int& num : arr) {
                file << num << " ";
            }
            file << "\n"; // Separar casos de prueba por líneas
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

int main() {
    vector<int> sizes = {10, 100, 1000, 10000, 100000}; // Tamaños de los arrays
    int numCases = 10; // Número de casos de prueba por archivo

    for (int size : sizes) {
        vector<vector<int>> orderedArrays, partiallyOrderedArrays, reversedArrays;

        for (int i = 0; i < numCases; ++i) {
            orderedArrays.push_back(generateOrderedArray(size));
            partiallyOrderedArrays.push_back(generatePartiallyOrderedArray(size));
            reversedArrays.push_back(generateReversedArray(size));
        }

        saveArraysToFile(orderedArrays, "ordered_" + to_string(size) + ".txt");
        saveArraysToFile(partiallyOrderedArrays, "partially_ordered_" + to_string(size) + ".txt");
        saveArraysToFile(reversedArrays, "reversed_" + to_string(size) + ".txt");
    }

    return 0;
}
