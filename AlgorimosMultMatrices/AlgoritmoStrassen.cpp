#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

/*
    Entradas:
    - NomArch: El nombre del archivo que contiene las matrices.

    *****

    Funcionamiento:
    Esta función lee matrices de un archivo y las almacena en un vector tridimensional. 
    Cada matriz es de tamaño n x n, donde n se especifica al inicio de cada bloque de datos.

    *****

    Salida:
    Un vector tridimensional que contiene múltiples matrices.
*/
vector<vector<vector<int>>> LectorMatrices(const string& NomArch) {
    ifstream file(NomArch);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << NomArch << endl;
        return {};
    }

    vector<vector<vector<int>>> matrices;
    int n;

    while (file >> n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file >> matrix[i][j];
            }
        }
        matrices.push_back(matrix);
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar el salto de línea
    }

    file.close();
    return matrices;
}

/*
    Entradas:
    - n: El tamaño de la matriz (n x n).

    *****

    Funcionamiento:
    Genera una matriz cuadrada de tamaño n x n con valores aleatorios entre 0 y 99.

    *****

    Salida:
    Una matriz de tamaño n x n con valores aleatorios.
*/
vector<vector<int>> MatrizAuxiliar(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    srand(static_cast<unsigned>(time(nullptr))); // Inicializar la semilla de aleatoriedad

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 100; // Valores aleatorios entre 0 y 99
        }
    }
    return matrix;
}

/*
    Entradas:
    - A: Primera matriz (n x n).
    - B: Segunda matriz (n x n).

    *****

    Funcionamiento:
    Suma dos matrices de igual tamaño (n x n), almacenando el resultado en una nueva matriz.

    *****

    Salida:
    La matriz resultante de la suma de A y B.
*/
vector<vector<int>> suma(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

/*
    Entradas:
    - A: Primera matriz (n x n).
    - B: Segunda matriz (n x n).

    *****

    Funcionamiento:
    Resta dos matrices de igual tamaño (n x n), almacenando el resultado en una nueva matriz.

    *****

    Salida:
    La matriz resultante de la resta de A y B.
*/
vector<vector<int>> resta(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

/*
    Entradas:
    - A: Primera matriz (n x n).
    - B: Segunda matriz (n x n).

    *****

    Funcionamiento:
    Implementa el algoritmo de Strassen para multiplicar dos matrices cuadradas de tamaño n x n.
    El algoritmo divide las matrices en submatrices y realiza multiplicaciones más pequeñas, 
    lo que reduce la complejidad asintótica en comparación con el método tradicional.

    *****

    Salida:
    La matriz resultante de la multiplicación de A y B utilizando el algoritmo de Strassen.
*/
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n == 1) {
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));

    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    auto M1 = strassen(suma(A11, A22), suma(B11, B22));
    auto M2 = strassen(suma(A21, A22), B11);
    auto M3 = strassen(A11, resta(B12, B22));
    auto M4 = strassen(A22, resta(B21, B11));
    auto M5 = strassen(suma(A11, A12), B22);
    auto M6 = strassen(resta(A21, A11), suma(B11, B12));
    auto M7 = strassen(resta(A12, A22), suma(B21, B22));

    vector<vector<int>> C(n, vector<int>(n));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + newSize] = M3[i][j] + M5[i][j];
            C[i + newSize][j] = M2[i][j] + M4[i][j];
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    return C;
}

/*
    Entradas:
    - A: Primera matriz (n x n).
    - B: Segunda matriz (n x n).
    - FuncMult: Puntero a la función de multiplicación de matrices a utilizar.

    *****

    Funcionamiento:
    Mide el tiempo de ejecución de la función de multiplicación de matrices pasada como parámetro 
    usando las matrices A y B. Utiliza la función clock() para obtener el tiempo transcurrido.

    *****

    Salida:
    El tiempo en segundos que tarda en ejecutarse la función de multiplicación.
*/
double CalculadorTiempo(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>(*FuncMult)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    clock_t start = clock();
    vector<vector<int>> C = FuncMult(A, B);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

/*
    Entradas:
    - size: Tamaño de las matrices (n x n).
    - Archivo: Nombre del archivo que contiene las matrices.
    - FuncMult: Puntero a la función de multiplicación de matrices a utilizar.

    *****

    Funcionamiento:
    Calcula el tiempo promedio de multiplicación de varias matrices con una matriz auxiliar generada aleatoriamente. 
    Las matrices se leen desde un archivo. Para cada matriz leída, se multiplica con la auxiliar 
    y se calcula el tiempo promedio de 10 ejecuciones.

    *****

    Salida:
    Muestra el tiempo promedio de multiplicación para cada matriz leída.
*/
void TiempoPromedio(int size, const string& Archivo, vector<vector<int>>(*FuncMult)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    vector<vector<vector<int>>> matrices = LectorMatrices(Archivo);

    if (matrices.empty()) {
        cout << "No se encontraron matrices en el archivo." << endl;
        return;
    }

    vector<vector<int>> Auxiliar = MatrizAuxiliar(size);

    for (const auto& matrix : matrices) {
        double total_time = 0;
        for (int i = 0; i < 10; ++i) {
            total_time += CalculadorTiempo(matrix, Auxiliar, FuncMult);
        }
        cout << "Tiempo promedio de multiplicación: " << total_time / 10 << " segundos." << endl;
    }
}
int main() {
    srand(static_cast<unsigned int>(time(0)));
    int size;
    cout << "Ingrese el tamaño de las matrices: ";
    cin >> size;

    string Archivo = "matrix_" + to_string(size) + "x" + to_string(size) + ".txt";

    // Medir el tiempo del algoritmo de Strassen
    cout << "Calculando tiempo para el algoritmo de Strassen..." << endl;
    TiempoPromedio(size, Archivo, strassen);

    return 0;
}