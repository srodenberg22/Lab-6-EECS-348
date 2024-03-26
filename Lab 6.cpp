#include <iostream>
#include <fstream>

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
void readMatrixFromFile(int** matrix, std::ifstream& file, int N) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> matrix[i][j]; // Read matrix elements
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
    std::ifstream file("matrix_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1; // Exit if unable to open file
    }

    int N;
    file >> N; // Read matrix size

    int** matrix1 = allocateMatrix(N);
    int** matrix2 = allocateMatrix(N);
    int** result;

    // Read the first matrix from the file
    readMatrixFromFile(matrix1, file, N);

    // Read the second matrix from the file
    readMatrixFromFile(matrix2, file, N);

    file.close(); // Close the file

    // Print the matrices
    std::cout << "Matrix 1:\n";
    printMatrix(matrix1, N);

    std::cout << "\nMatrix 2:\n";
    printMatrix(matrix2, N);

    // Perform addition
    std::cout << "\nAddition Result:\n";
    result = addOrSubtractMatrices(matrix1, matrix2, N, true);
    printMatrix(result, N);
    deallocateMatrix(result, N);

    // Perform subtraction
    std::cout << "\nSubtraction Result:\n";
    result = addOrSubtractMatrices(matrix1, matrix2, N, false);
    printMatrix(result, N);
    deallocateMatrix(result, N);

    // Update an element in matrix1
    std::cout << "\nUpdate Element Result:\n";
    updateElement(matrix1, 1, 1, 99);
    printMatrix(matrix1, N);

    // Find max value in matrix1
    std::cout << "\nMax Value of Matrix 1: " << getMaxValue(matrix1, N) << std::endl;

    // Transpose matrix1
    std::cout << "\nTransposed Matrix 1:\n";
    result = transposeMatrix(matrix1, N);
    printMatrix(result, N);
    deallocateMatrix(result, N);

    // Deallocate memory
    deallocateMatrix(matrix1, N);
    deallocateMatrix(matrix2, N);

    return 0;
}
