#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

// Función para leer matrices desde un archivo
vector<vector<vector<int>>> LectorMatrices(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
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
    }

    file.close();
    return matrices;
}

// Función para generar una matriz auxiliar con valores aleatorios
vector<vector<int>> MatrizAuxiliar(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 10;  // Valores aleatorios entre 0 y 9
        }
    }
    return matrix;
}

// Algoritmo cúbico optimizado para multiplicación de matrices (mejorado en memoria caché)
vector<vector<int>> MatrizOpti(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < n; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Función para medir el tiempo de un algoritmo de multiplicación de matrices
double CalculadorTiempo(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>(*multiplyFunction)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    clock_t start = clock();
    vector<vector<int>> C = multiplyFunction(A, B);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

// Función para calcular el tiempo promedio de un algoritmo con múltiples matrices
void TiempoPromedio(int size, const string& Archivo, vector<vector<int>>(*multiplyFunction)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    vector<vector<vector<int>>> matrices = LectorMatrices(Archivo);

    if (matrices.empty()) {
        cerr << "Error al leer las matrices." << endl;
        return;
    }

    int iterations = 10;
    double totalTime = 0;

    // Generar una matriz auxiliar
    vector<vector<int>> auxMatrix = MatrizAuxiliar(size);

    for (const auto& matrix : matrices) {
        if (matrix.size() != size) {
            cerr << "Tamaño de matriz en el archivo no coincide con el tamaño esperado." << endl;
            continue;
        }

        double avgTime = 0;
        for (int i = 0; i < iterations; ++i) {
            avgTime += CalculadorTiempo(matrix, auxMatrix, multiplyFunction);
        }
        avgTime /= iterations;
        cout << "Tamaño " << size << ", Tiempo promedio para una matriz: " << avgTime << " segundos" << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int size;
    cout << "Ingrese el tamaño de las matrices: ";
    cin >> size;

    string Archivo = "matrix_" + to_string(size) + "x" + to_string(size) + ".txt";

    // Medir el tiempo del algoritmo cúbico optimizado
    cout << "Calculando tiempo para el algoritmo cúbico optimizado..." << endl;
    TiempoPromedio(size, Archivo, MatrizOpti);

    return 0;
}
