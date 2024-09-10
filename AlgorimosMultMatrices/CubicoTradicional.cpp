#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Función para generar una MatrizTrad cuadrada de tamaño n x n con valores aleatorios
vector<vector<int>> MatrizTradAuxiliar(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 10;  // Valores aleatorios entre 0 y 9
        }
    }
    return matrix;
}

// Función para leer matrices desde un archivo
vector<vector<vector<int>>> LectorMatrices(const string& filename, int size) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return {};
    }

    vector<vector<vector<int>>> matrices;
    while (file) {
        vector<vector<int>> matrix(size, vector<int>(size));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (!(file >> matrix[i][j])) {
                    file.close();
                    return matrices;
                }
            }
        }
        matrices.push_back(matrix);
    }

    file.close();
    return matrices;
}

// Algoritmo cúbico tradicional para multiplicación de matrices
vector<vector<int>> MatrizTrad(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Función para medir el tiempo de multiplicación de una MatrizTrad con la auxiliar
double CalculadorTiempo(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>(*multiplyFunction)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    clock_t start = clock();
    vector<vector<int>> C = multiplyFunction(A, B);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

// Función para calcular el tiempo promedio de multiplicación de varias matrices con una auxiliar
void TiempoPromedio(int size, const string& Archivo, vector<vector<int>>(*multiplyFunction)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    vector<vector<vector<int>>> matrices = LectorMatrices(Archivo, size);

    if (matrices.empty()) {
        cerr << "No se leyeron matrices del archivo." << endl;
        return;
    }

    // Generar la MatrizTrad auxiliar
    vector<vector<int>> auxiliaryMatrix = MatrizTradAuxiliar(size);

    int matrixCount = matrices.size();
    if (matrixCount == 0) {
        cerr << "No se encontraron matrices en el archivo." << endl;
        return;
    }

    double totalTime = 0;

    for (const auto& matrix : matrices) {
        totalTime += CalculadorTiempo(matrix, auxiliaryMatrix, multiplyFunction);
    }

    double averageTime = totalTime / matrixCount;
    cout << "Tamaño " << size << ", Tiempo promedio: " << averageTime << " segundos" << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int size;
    cout << "Ingrese el tamaño de las matrices: ";
    cin >> size;

    string Archivo = "matrix_" + to_string(size) + "x" + to_string(size) + ".txt";

    // Medir el tiempo del algoritmo cúbico tradicional
    cout << "Calculando tiempo para el algoritmo cúbico tradicional..." << endl;
    TiempoPromedio(size, Archivo, MatrizTrad);

    return 0;
}
