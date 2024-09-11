#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

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

// Algoritmo QuickSort
/*
    Entradas:
    - arr: Vector de enteros que se va a ordenar.
    - low: Índice inicial del vector para la partición actual.
    - high: Índice final del vector para la partición actual.

    *****

    Funcionamiento:
    Ordena el vector usando el algoritmo de QuickSort. Selecciona un pivote (el último elemento 
    en la partición actual), reorganiza los elementos de modo que los menores que el pivote queden 
    a la izquierda y los mayores a la derecha, y luego aplica recursivamente el algoritmo a las dos 
    particiones resultantes.

    *****

    Salida:
    El vector queda ordenado en el lugar.
*/
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

// Función envolvente para QuickSort
/*
    Entradas:
    - arr: Vector de enteros que se va a ordenar.

    *****

    Funcionamiento:
    Llama a la función quickSort con los índices inicial y final del vector para ordenar el 
    vector completo.

    *****

    Salida:
    El vector queda ordenado en el lugar.
*/
void quickSortWrapper(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// Medir el tiempo de ejecución de QuickSort
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
        cout << "Tiempo promedio para " << type << " con tamaño " << size << ": " << avgTime << " segundos" << endl;    }
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
