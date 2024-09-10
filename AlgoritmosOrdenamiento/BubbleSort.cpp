#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm> // swap

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

// Algoritmo BubbleSort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Medir el tiempo de ejecución de BubbleSort
double CalculadorTiempo(void (*Sort)(vector<int>&), const string& NomArch) {
    vector<int> arr = LeerArray(NomArch);
    auto start = high_resolution_clock::now();
    Sort(arr);
    auto end =  high_resolution_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

// Calcular el promedio de tiempos de ejecución
void TiempoPromedio(void (*Sort)(vector<int>&), int size) {
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

    TiempoPromedio(bubbleSort, size);

    return 0;
}
