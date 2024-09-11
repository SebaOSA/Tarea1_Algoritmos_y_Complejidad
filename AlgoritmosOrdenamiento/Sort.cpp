#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm> // sort

using namespace std;
using namespace chrono;

// Función para leer un array desde un archivo
/*
    Entradas:
    - NomArch: Nombre del archivo desde el cual se leerá el array.

    *****

    Funcionamiento:
    Lee los elementos del array desde un archivo especificado por el nombre. Abre el archivo, 
    lee cada número y lo añade al vector. Si el archivo no se puede abrir, muestra un mensaje de error.

    *****

    Salida:
    Devuelve un vector de enteros que contiene los números leídos desde el archivo.
*/
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

// Medir el tiempo de ejecución de sort
/*
    Entradas:
    - Sort: Puntero a función de ordenamiento que se aplicará al array.
    - NomArch: Nombre del archivo desde el cual se leerá el array.

    *****

    Funcionamiento:
    Lee el array desde el archivo especificado, mide el tiempo que tarda en ordenar el array 
    usando la función de ordenamiento pasada como argumento, y devuelve el tiempo de ejecución en segundos.

    *****

    Salida:
    Devuelve el tiempo en segundos que tarda en ordenar el array.
*/
double CalculadorTiempo(void (*Sort)(vector<int>&), const string& NomArch) {
    vector<int> arr = LeerArray(NomArch);
    auto start = high_resolution_clock::now();
    Sort(arr);
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

// Calcular el promedio de tiempos de ejecución
/*
    Entradas:
    - Sort: Puntero a función de ordenamiento que se aplicará a cada array.
    - size: Tamaño de los arrays que se utilizarán en el archivo.

    *****

    Funcionamiento:
    Calcula el tiempo promedio que tarda en ordenar varios arrays de diferentes tipos 
    (ordered, partially_ordered, reversed). Lee los arrays desde archivos con nombres 
    que incluyen el tipo de orden y el tamaño, ejecuta el algoritmo de ordenamiento 
    y luego calcula el tiempo promedio para cada tipo de array.

    *****

    Salida:
    Imprime en consola el tiempo promedio que tarda en ordenar cada tipo de array.
*/
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
            totalTime += CalculadorTiempo([](vector<int>& arr) { sort(arr.begin(), arr.end()); }, NomArch);
        }
        double avgTime = totalTime / iterations; // Promedio por tipo
        cout << "Tiempo promedio para " << type << " con tamaño " << size << ": " << avgTime << " segundos" << endl;
        totalTime = 0; // Resetear el totalTime para el siguiente tipo
    }
}

int main() {
    int size;
    cout << "Ingrese el tamaño del array: ";
    cin >> size;

    TiempoPromedio([](vector<int>& arr) { sort(arr.begin(), arr.end()); }, size);

    return 0;
}
