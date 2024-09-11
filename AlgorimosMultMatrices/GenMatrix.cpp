#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función para generar una matriz cuadrada de tamaño n x n con valores aleatorios
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 10;  // Valores aleatorios entre 0 y 9
        }
    }
    return matrix;
}

// Función para guardar una matriz en un archivo
void saveMatrixToFile(const vector<vector<int>>& matrix, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        int n = matrix.size();
        file << n << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file << matrix[i][j] << " ";
            }
            file << endl;
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

// Función para generar y guardar múltiples matrices
void generateAndSaveMatrices(int size, const string& filename, int count) {
    ofstream file(filename);
    if (file.is_open()) {
        int n = size;
        for (int i = 0; i < count; ++i) {
            vector<vector<int>> matrix = generateMatrix(n);
            file << n << endl;
            for (int row = 0; row < n; ++row) {
                for (int col = 0; col < n; ++col) {
                    file << matrix[row][col] << " ";
                }
                file << endl;
            }
            file << endl; // Separar matrices con una línea en blanco
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Tamaños de matrices y número de ejemplares por tamaño
    vector<int> sizes = {4, 10, 50, 100, 500, 1000, 2000, 3000};
    vector<int> counts = {5, 5, 5, 5, 5, 1, 1, 1}; // Número de matrices por tamaño

    for (size_t i = 0; i < sizes.size(); ++i) {
        int size = sizes[i];
        int count = counts[i];
        string filename = "matrix_" + to_string(size) + "x" + to_string(size) + ".txt";
        generateAndSaveMatrices(size, filename, count);
        cout << "Matrices de tamaño " << size << "x" << size << " generadas y guardadas en " << filename << endl;
    }

    return 0;
}
