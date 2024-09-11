#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

/*
    Entradas:
    - n: Tamaño de la matriz a generar.

    *****

    Funcionamiento:
    Genera una matriz cuadrada de tamaño n x n con valores aleatorios entre 0 y 9.

    *****

    Salida:
    Devuelve una matriz de tamaño n x n con valores aleatorios.
*/
vector<vector<int>> MatrizTradAuxiliar(int n) {
    vector<vector<int>> matrix(n, vector<int>(n)); // Crear una matriz de tamaño n x n
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 10; // Asignar valores aleatorios entre 0 y 9
        }
    }
    return matrix; // Devolver la matriz generada
}

/*
    Entradas:
    - filename: Nombre del archivo desde donde se leerán las matrices.
    - size: Tamaño de las matrices que se van a leer.

    *****

    Funcionamiento:
    Lee matrices cuadradas de tamaño 'size' desde un archivo. El archivo debe estar estructurado 
    de tal forma que contenga valores que representen las matrices. Lee todos los valores 
    hasta que el archivo termine.

    *****

    Salida:
    Devuelve un vector tridimensional que contiene todas las matrices leídas desde el archivo.
*/
vector<vector<vector<int>>> LectorMatrices(const string& filename, int size) {
    ifstream file(filename); // Abrir el archivo
    if (!file.is_open()) { // Comprobar si se abrió correctamente
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return {}; // Devolver un vector vacío si falla
    }

    vector<vector<vector<int>>> matrices; // Vector para almacenar todas las matrices
    while (file) {
        vector<vector<int>> matrix(size, vector<int>(size)); // Crear una matriz de tamaño 'size' x 'size'
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (!(file >> matrix[i][j])) { // Leer los valores de la matriz desde el archivo
                    file.close(); // Cerrar el archivo si no hay más datos
                    return matrices; // Devolver las matrices leídas hasta el momento
                }
            }
        }
        matrices.push_back(matrix); // Agregar la matriz al vector de matrices
    }

    file.close(); // Cerrar el archivo
    return matrices; // Devolver todas las matrices leídas
}

/*
    Entradas:
    - A: Primera matriz de tamaño n x n.
    - B: Segunda matriz de tamaño n x n.

    *****

    Funcionamiento:
    Implementa el algoritmo cúbico tradicional para multiplicación de matrices.

    *****

    Salida:
    Devuelve la matriz resultante de la multiplicación de A y B.
*/
vector<vector<int>> MatrizTrad(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0)); // Inicializar matriz resultado C con ceros
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j]; // Multiplicar y acumular el resultado
            }
        }
    }
    return C; // Devolver la matriz resultado
}

/*
    Entradas:
    - A: Primera matriz.
    - B: Segunda matriz.
    - multiplyFunction: Puntero a una función de multiplicación de matrices.

    *****

    Funcionamiento:
    Mide el tiempo de ejecución de una función de multiplicación de matrices. Utiliza `clock()` 
    para calcular el tiempo transcurrido entre el inicio y el final de la ejecución.

    *****

    Salida:
    Devuelve el tiempo en segundos que tardó en ejecutarse la multiplicación.
*/
double CalculadorTiempo(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>(*multiplyFunction)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    clock_t start = clock(); // Comienza a contar el tiempo
    vector<vector<int>> C = multiplyFunction(A, B); // Ejecuta la función de multiplicación
    clock_t end = clock(); // Detiene el conteo de tiempo
    return double(end - start) / CLOCKS_PER_SEC; // Devuelve el tiempo en segundos
}

/*
    Entradas:
    - size: Tamaño de las matrices que se utilizarán.
    - Archivo: Nombre del archivo desde donde se leerán las matrices.
    - multiplyFunction: Puntero a una función de multiplicación de matrices.

    *****

    Funcionamiento:
    Lee múltiples matrices desde un archivo y mide el tiempo promedio que tarda en multiplicarlas 
    utilizando la función de multiplicación proporcionada. Para cada matriz, se multiplica por una 
    matriz auxiliar generada aleatoriamente.

    *****

    Salida:
    Imprime el tiempo promedio de multiplicación para las matrices.
*/
void TiempoPromedio(int size, const string& Archivo, vector<vector<int>>(*multiplyFunction)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    vector<vector<vector<int>>> matrices = LectorMatrices(Archivo, size); // Leer matrices desde el archivo

    if (matrices.empty()) { // Verificar si la lectura de matrices falló
        cerr << "No se leyeron matrices del archivo." << endl;
        return;
    }

    // Generar la matriz auxiliar para multiplicar
    vector<vector<int>> auxiliaryMatrix = MatrizTradAuxiliar(size);

    int matrixCount = matrices.size(); // Número de matrices leídas
    if (matrixCount == 0) {
        cerr << "No se encontraron matrices en el archivo." << endl;
        return;
    }

    double totalTime = 0; // Variable para almacenar el tiempo total

    // Calcular el tiempo de multiplicación para cada matriz leída
    for (const auto& matrix : matrices) {
        totalTime += CalculadorTiempo(matrix, auxiliaryMatrix, multiplyFunction); // Acumular el tiempo
    }

    // Calcular el tiempo promedio
    double averageTime = totalTime / matrixCount;
    cout << "Tamaño " << size << ", Tiempo promedio: " << averageTime << " segundos" << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicializar la semilla de aleatoriedad

    int size;
    cout << "Ingrese el tamaño de las matrices: ";
    cin >> size; // Solicitar el tamaño de las matrices al usuario

    // Crear el nombre del archivo basado en el tamaño de la matriz
    string Archivo = "matrix_" + to_string(size) + "x" + to_string(size) + ".txt";

    // Medir el tiempo del algoritmo cúbico tradicional
    cout << "Calculando tiempo para el algoritmo cúbico tradicional..." << endl;
    TiempoPromedio(size, Archivo, MatrizTrad); // Llamar a la función para medir el tiempo

    return 0;
}
