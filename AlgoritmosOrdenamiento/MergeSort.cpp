#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

/*
    Entradas:
    - NomArch: Nombre del archivo desde donde se leerán los números.

    *****

    Funcionamiento:
    Lee un array de números enteros desde el archivo proporcionado. El archivo debe contener 
    una lista de números en líneas separadas. Si no se puede abrir el archivo, se muestra un 
    mensaje de error.

    *****

    Salida:
    Devuelve un vector de enteros que contiene los números leídos desde el archivo. Si no se 
    pudo abrir el archivo, retorna un vector vacío.
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

/*
    Entradas:
    - arr: Vector de enteros que contiene el array a ordenar.
    - l: Índice del extremo izquierdo del subarray.
    - m: Índice del punto medio del subarray.
    - r: Índice del extremo derecho del subarray.

    *****

    Funcionamiento:
    Fusiona dos subarrays ordenados en un solo subarray ordenado. El primer subarray va de `l` a `m`
    y el segundo subarray va de `m + 1` a `r`. Compara los elementos de los dos subarrays y
    los combina de manera ordenada.

    *****

    Salida:
    No retorna ningún valor, pero el vector `arr` queda modificado, conteniendo los elementos ordenados.
*/
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Crea arrays temporales
    vector<int> L(n1), R(n2);

    // Copia los datos a los arrays temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    // Fusiona los arrays temporales de nuevo en arr[l..r]
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

    // Copia los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/*
    Entradas:
    - arr: Vector de enteros a ordenar.
    - l: Índice izquierdo del array.
    - r: Índice derecho del array.

    *****

    Funcionamiento:
    Implementa el algoritmo MergeSort. Divide recursivamente el array en dos mitades, 
    las ordena por separado y luego fusiona las dos mitades ordenadas usando la función `merge`.

    *****

    Salida:
    No retorna ningún valor, pero el vector `arr` queda ordenado.
*/
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        // Encuentra el punto medio para dividir el array en dos mitades
        int m = l + (r - l) / 2;

        // Ordena la primera mitad
        mergeSort(arr, l, m);
        // Ordena la segunda mitad
        mergeSort(arr, m + 1, r);

        // Fusiona las dos mitades ordenadas
        merge(arr, l, m, r);
    }
}

/*
    Entradas:
    - Sort: Puntero a función de ordenamiento que se aplicará al array.
    - NomArch: Nombre del archivo desde donde se leerá el array.

    *****

    Funcionamiento:
    Lee un array desde el archivo proporcionado y mide el tiempo que toma ordenarlo 
    utilizando la función de ordenamiento proporcionada. Calcula el tiempo usando 
    la biblioteca chrono.

    *****

    Salida:
    Devuelve el tiempo en segundos que tomó ordenar el array.
*/
double CalculadorTiempo(void (*Sort)(vector<int>&, int, int), const string& NomArch) {
    vector<int> arr = LeerArray(NomArch);  // Lee el array del archivo
    auto start = high_resolution_clock::now();  // Marca el tiempo de inicio
    Sort(arr, 0, arr.size() - 1);  // Aplica el algoritmo de ordenamiento (MergeSort)
    auto end = high_resolution_clock::now();  // Marca el tiempo de fin

    // Calcula la duración en segundos y la retorna
    duration<double> duration = end - start;
    return duration.count();
}

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
void TiempoPromedio(void (*Sort)(vector<int>&, int, int), int size) {
    double totalTime = 0;  // Variable para almacenar el tiempo total
    string types[] = {"ordered", "partially_ordered", "reversed"};  // Tipos de orden

    // Itera sobre los diferentes tipos de orden
    for (const string& type : types) {
        string NomArch = type + "_" + to_string(size) + ".txt";  // Nombre del archivo basado en el tipo y tamaño

        // Verifica si el archivo puede abrirse para contar las líneas
        ifstream file(NomArch);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo " << NomArch << " para leer." << endl;
            continue;  // Si no se puede abrir el archivo, pasar al siguiente tipo
        }

        // Para cada archivo se ejecuta el algoritmo y se calcula el tiempo total
        int iterations = 1;  // Número de veces que se quiere ejecutar el algoritmo (puedes ajustar)
        for (int i = 0; i < iterations; ++i) {
            totalTime += CalculadorTiempo(Sort, NomArch);  // Acumular el tiempo de ejecución
        }

        // Calcula el tiempo promedio para este tipo de array
        double avgTime = totalTime / iterations;
        cout << "Tiempo promedio para " << type << " con tamaño " << size << ": " << avgTime << " segundos" << endl;
        totalTime = 0;  // Reiniciar el totalTime para el siguiente tipo
    }
}

int main() {
    int size;
    cout << "Ingrese el tamaño del array: ";
    cin >> size;  // Leer el tamaño del array

    TiempoPromedio(mergeSort, size);  // Llamar a la función para medir el tiempo promedio

    return 0;
}
