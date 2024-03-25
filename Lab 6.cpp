#include <iostream>
#include <fstream>

// Function to read matrix size from file
int readMatrixSizeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return -1; // Return -1 if unable to open file
    int size;
    file >> size; // Read matrix size
    file.close();
    return size;
}

// Function to dynamically allocate memory for a matrix
int** allocateMatrix(int size) {
    int** matrix = new int*[size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new int[size];
    return matrix;
}

// Function to deallocate memory for a matrix
void deallocateMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

// Function to read values from a file into a matrix
void readMatrixFromFile(int** matrix, const std::string& filename, int N) {
    std::ifstream file(filename);
    if (!file.is_open()) return; // Return if unable to open file
    int matrixSize;
    file >> matrixSize; // Read matrix size from file
    if (matrixSize != N) return; // Exit if matrix size does not match N
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> matrix[i][j]; // Read matrix elements
    file.close();
}

// Function to print a matrix
void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            std::cout << matrix[i][j] << "\t"; // Print matrix elements
        std::cout << std::endl;
    }
}

// Function to add or subtract two matrices
int** addOrSubtractMatrices(int** matrix1, int** matrix2, int size, bool add) {
    int** result = allocateMatrix(size); // Allocate memory for result matrix
    int op = add ? 1 : -1; // Determine operation (addition or subtraction)
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = matrix1[i][j] + (op * matrix2[i][j]); // Perform operation
    return result;
}

// Function to update an element of the matrix
void updateElement(int** matrix, int row, int col, int newValue) {
    matrix[row][col] = newValue; // Update matrix element
}

// Function to find the max value in the matrix
int getMaxValue(int** matrix, int size) {
    int maxValue = matrix[0][0];
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (matrix[i][j] > maxValue) maxValue = matrix[i][j]; // Update max value if needed
    return maxValue;
}

// Function to transpose the matrix
int** transposeMatrix(int** matrix, int size) {
    int** transposed = allocateMatrix(size); // Allocate memory for transposed matrix
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            transposed[j][i] = matrix[i][j]; // Transpose matrix
    return transposed;
}

int main() {
    int N = readMatrixSizeFromFile("matrix_input.txt");
    if (N == -1) return 1; // Exit if unable to read matrix size
    int** matrix1 = allocateMatrix(N);
    int** matrix2 = allocateMatrix(N);
    int** result;

    readMatrixFromFile(matrix1, "matrix_input.txt", N);
    readMatrixFromFile(matrix2, "matrix_input.txt", N);

    std::cout << "Matrix 1:\n";
    printMatrix(matrix1, N);

    std::cout << "\nMatrix 2:\n";
    printMatrix(matrix2, N);

    std::cout << "\nAddition Result:\n";
    result = addOrSubtractMatrices(matrix1, matrix2, N, true);
    printMatrix(result, N);
    deallocateMatrix(result, N);

    std::cout << "\nSubtraction Result:\n";
    result = addOrSubtractMatrices(matrix1, matrix2, N, false);
    printMatrix(result, N);
    deallocateMatrix(result, N);

    std::cout << "\nUpdate Element Result:\n";
    updateElement(matrix1, 1, 1, 99);
    printMatrix(matrix1, N);

    std::cout << "\nMax Value of Matrix 1: " << getMax
