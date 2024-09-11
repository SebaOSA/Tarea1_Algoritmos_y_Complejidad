#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm> // Para usar la función swap
#include <string>

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
    ifstream file(NomArch); // Abre el archivo
    vector<int> arr; // Vector para almacenar los datos del archivo
    int num;
    
    // Verifica si el archivo se abrió correctamente
    if (file.is_open()) {
        // Mientras haya números en el archivo, los añade al vector
        while (file >> num) {
            arr.push_back(num);
        }
        file.close(); // Cierra el archivo después de leer
    } else {
        // Muestra un mensaje de error si no se pudo abrir el archivo
        cerr << "No se pudo abrir el archivo " << NomArch << " para leer." << endl;
    }
    return arr; // Retorna el vector con los datos
}

/*
    Entradas:
    - arr: Vector de enteros que se va a ordenar.

    *****

    Funcionamiento:
    Implementa el algoritmo de ordenamiento BubbleSort. Compara elementos adyacentes y los 
    intercambia si están en el orden incorrecto, repitiendo este proceso hasta que el vector 
    esté completamente ordenado.

    *****

    Salida:
    El vector arr se ordena en su lugar. No retorna ningún valor.
*/
void bubbleSort(vector<int>& arr) {
    int n = arr.size(); // Tamaño del array
    // Dos bucles anidados para comparar e intercambiar elementos
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            // Si el elemento actual es mayor que el siguiente, los intercambia
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]); // Función swap para intercambio
            }
        }
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
double CalculadorTiempo(void (*Sort)(vector<int>&), const string& NomArch) {
    vector<int> arr = LeerArray(NomArch); // Lee el array del archivo
    if (arr.empty()) {
        return 0.0;  // Si no se pudo leer el array, retorna 0 para evitar errores
    }
    
    // Marca el tiempo de inicio
    auto start = high_resolution_clock::now();
    Sort(arr);  // Aplica el algoritmo de ordenamiento (BubbleSort)
    // Marca el tiempo de fin
    auto end = high_resolution_clock::now();

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
void TiempoPromedio(void (*Sort)(vector<int>&), int size) {
    double totalTime = 0;  // Variable para almacenar el tiempo total
    string types[] = {"ordered", "partially_ordered", "reversed"}; // Tipos de orden

    // Iterar sobre los diferentes tipos de orden
    for (const string& type : types) {
        string NomArch = type + "_" + to_string(size) + ".txt"; // Nombre del archivo basado en el tipo y tamaño
        
        // Verifica si el archivo puede abrirse para contar las líneas
        ifstream file(NomArch);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo " << NomArch << " para leer." << endl;
            continue; // Si no se puede abrir el archivo, pasar al siguiente tipo
        }

        // Para cada archivo se ejecuta el algoritmo y se calcula el tiempo total
        int iterations = 1;  // Número de veces que se quiere ejecutar el algoritmo (puedes ajustar)
        for (int i = 0; i < iterations; ++i) {
            totalTime += CalculadorTiempo(Sort, NomArch); // Acumular el tiempo de ejecución
        }

        // Calcula el tiempo promedio para este tipo de array
        double avgTime = totalTime / iterations;
        cout << "Tiempo promedio para " << type << " con tamaño " << size << ": " << avgTime << " segundos" << endl;
        totalTime = 0; // Reiniciar el totalTime para el siguiente tipo
    }
}

int main() {
    int size;
    cout << "Ingrese el tamaño del array: ";
    cin >> size; // Leer el tamaño del array

    TiempoPromedio(bubbleSort, size); // Llamar a la función para medir el tiempo promedio

    return 0;
}
