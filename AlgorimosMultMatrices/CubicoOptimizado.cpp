#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

/*
    Entradas:
    - filename: Nombre del archivo desde donde se leerán las matrices.

    *****

    Funcionamiento:
    Lee matrices cuadradas desde un archivo. El archivo debe estar estructurado de tal forma que 
    cada conjunto de datos de una matriz comience con un entero 'n' (el tamaño de la matriz), 
    seguido de n x n números enteros que representan los elementos de la matriz.

    *****

    Salida:
    Devuelve un vector tridimensional que contiene todas las matrices leídas desde el archivo.
*/
vector<vector<vector<int>>> LectorMatrices(const string& filename) {
    ifstream file(filename); // Abrir el archivo
    if (!file.is_open()) { // Comprobar si se abrió correctamente
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return {}; // Devolver un vector vacío si falla
    }

    vector<vector<vector<int>>> matrices; // Vector tridimensional para almacenar las matrices
    int n;

    // Leer el tamaño de la matriz (n) y luego los valores de la matriz
    while (file >> n) {
        vector<vector<int>> matrix(n, vector<int>(n)); // Crear una matriz de tamaño n x n
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file >> matrix[i][j]; // Leer los valores de la matriz desde el archivo
            }
        }
        matrices.push_back(matrix); // Agregar la matriz al vector de matrices
    }

    file.close(); // Cerrar el archivo
    return matrices; // Devolver las matrices leídas
}

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
vector<vector<int>> MatrizAuxiliar(int n) {
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
    - A: Primera matriz de tamaño n x n.
    - B: Segunda matriz de tamaño n x n.

    *****

    Funcionamiento:
    Implementa una versión optimizada del algoritmo cúbico de multiplicación de matrices. 
    Mejora el uso de la memoria caché al realizar las multiplicaciones en un orden que 
    favorece el acceso secuencial de los elementos.

    *****

    Salida:
    Devuelve la matriz resultante de la multiplicación de A y B.
*/
vector<vector<int>> MatrizOpti(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0)); // Inicializar matriz resultado C con ceros
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) { // Cambiar el orden de los bucles para optimizar la caché
            for (int j = 0; j < n; ++j) {
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
    Imprime el tiempo promedio de multiplicación para cada matriz.
*/
void TiempoPromedio(int size, const string& Archivo, vector<vector<int>>(*multiplyFunction)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    vector<vector<vector<int>>> matrices = LectorMatrices(Archivo); // Leer matrices desde el archivo

    if (matrices.empty()) { // Verificar si la lectura de matrices falló
        cerr << "Error al leer las matrices." << endl;
        return;
    }

    int iterations = 10; // Número de iteraciones para obtener un promedio
    double totalTime = 0;

    // Generar una matriz auxiliar de tamaño 'size'
    vector<vector<int>> auxMatrix = MatrizAuxiliar(size);

    for (const auto& matrix : matrices) {
        if (matrix.size() != size) { // Verificar si el tamaño de la matriz es correcto
            cerr << "Tamaño de matriz en el archivo no coincide con el tamaño esperado." << endl;
            continue;
        }

        double avgTime = 0;
        for (int i = 0; i < iterations; ++i) { // Realizar varias iteraciones para calcular el promedio
            avgTime += CalculadorTiempo(matrix, auxMatrix, multiplyFunction); // Calcular tiempo de ejecución
        }
        avgTime /= iterations; // Calcular el tiempo promedio
        cout << "Tamaño " << size << ", Tiempo promedio para una matriz: " << avgTime << " segundos" << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicializar la semilla de aleatoriedad
    int size;
    cout << "Ingrese el tamaño de las matrices: ";
    cin >> size; // Solicitar el tamaño de las matrices al usuario

    // Crear el nombre del archivo basado en el tamaño de la matriz
    string Archivo = "matrix_" + to_string(size) + "x" + to_string(size) + ".txt";

    // Medir el tiempo del algoritmo cúbico optimizado
    cout << "Calculando tiempo para el algoritmo cúbico optimizado..." << endl;
    TiempoPromedio(size, Archivo, MatrizOpti); // Llamar a la función para medir el tiempo

    return 0;
}
