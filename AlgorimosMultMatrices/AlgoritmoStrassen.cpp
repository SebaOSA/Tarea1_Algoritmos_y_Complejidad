#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <limits>

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
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar el salto de línea
    }

    file.close();
    return matrices;
}

// Función para generar una matriz auxiliar de tamaño n x n con valores aleatorios
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

// Función para sumar dos matrices
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

// Función para restar dos matrices
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

// Algoritmo de Strassen para multiplicación de matrices
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

// Función para medir el tiempo de un algoritmo de multiplicación de matrices
double CalculadorTiempo(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>(*FuncMult)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    clock_t start = clock();
    vector<vector<int>> C = FuncMult(A, B);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

// Función para calcular el tiempo promedio de un algoritmo con múltiples matrices
void TiempoPromedio(int size, const string& Archivo, vector<vector<int>>(*FuncMult)(const vector<vector<int>>&, const vector<vector<int>>&)) {
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
            avgTime += CalculadorTiempo(matrix, auxMatrix, FuncMult);
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

    // Medir el tiempo del algoritmo de Strassen
    cout << "Calculando tiempo para el algoritmo de Strassen..." << endl;
    TiempoPromedio(size, Archivo, strassen);

    return 0;
}