#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Función para leer un array desde un archivo
vector<int> LeerArray(const string& NomArch) {
    ifstream file(NomArch);
    vector<int> arr;
    int num;
    if (file.is_open()) {
        while (file >> num) {
            arr.push_back(num);
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo " << NomArch << " para leer." << endl;
    }
    return arr;
}

// Función para fusionar dos subarrays
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función de ordenamiento MergeSort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Medir el tiempo de ejecución de MergeSort
double CalculadorTiempo(void (*Sort)(vector<int>&, int, int), const string& NomArch) {
    vector<int> arr = LeerArray(NomArch);
    auto start = high_resolution_clock::now();
    Sort(arr, 0, arr.size() - 1);
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

// Calcular el promedio de tiempos de ejecución
void TiempoPromedio(void (*Sort)(vector<int>&, int, int), int size) {
    double totalTime = 0;
    string types[] = {"ordered", "partially_ordered", "reversed"};
    int totalLines = 0;

    for (const string& type : types) {
        string NomArch = type + "_" + to_string(size) + ".txt";
        ifstream file(NomArch);
        if (file.is_open()) {
            totalLines = count(istreambuf_iterator<char>(file),
                                    istreambuf_iterator<char>(), '\n');
            file.close();
        }
        else {
            cerr << "No se pudo abrir el archivo " << NomArch << " para contar líneas." << endl;
            return;
        }

        int iterations = totalLines;
        for (int i = 0; i < iterations; ++i) {
            totalTime += CalculadorTiempo(Sort, NomArch);
        }
        double avgTime = totalTime / iterations; // promedio por tipo
        cout <<  avgTime << endl;
        totalTime = 0; // Resetear el totalTime para el siguiente tipo
    }
}

int main() {
    int size;
    cout << "Ingrese el tamaño del array: ";
    cin >> size;

    TiempoPromedio(mergeSort, size);

    return 0;
}
