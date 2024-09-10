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

// Algoritmo QuickSort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Elegir un pivote
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        // Recursivamente ordenar las dos particiones
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortWrapper(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// Medir el tiempo de ejecución de QuickSort
double CalculadorTiempo(void (*Sort)(vector<int>&), const string& NomArch) {
    vector<int> arr = LeerArray(NomArch);
    auto start = high_resolution_clock::now();
    Sort(arr);
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

// Calcular el promedio de tiempos de ejecución
void TiempoPromedio(void (*Sort)(vector<int>&), int size) {
    double totalTime = 0;
    string types[] = {"ordered", "partially_ordered", "reversed"};

    for (const string& type : types) {
        string NomArch = type + "_" + to_string(size) + ".txt";
        
        // Leer el archivo para contar el número de elementos
        ifstream file(NomArch);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo " << NomArch << " para leer." << endl;
            continue;
        }

        int lines = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
        file.close();

        // Realizar las mediciones
        totalTime = 0;
        for (int i = 0; i < 10; ++i) { // Hacer 10 iteraciones para obtener un promedio más fiable
            totalTime += CalculadorTiempo(Sort, NomArch);
        }
        double avgTime = totalTime / 10.0; // Promedio por tipo
        cout <<  avgTime << endl;
    }
}

int main() {
    int size;
    cout << "Ingrese el tamaño del array (10, 100, 1000, 10000, 100000): ";
    cin >> size;

    // Validar tamaño
    if (size != 10 && size != 100 && size != 1000 && size != 10000 && size != 100000) {
        cerr << "Tamaño no válido. Use uno de los tamaños permitidos." << endl;
        return 1;
    }

    TiempoPromedio(quickSortWrapper, size);

    return 0;
}
