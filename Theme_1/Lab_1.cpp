#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

bool checkMultipleOf4(int n) {
    return n % 4 == 0;
}

void generateArray(float* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = -1.50f + (rand() % 601) / 100.0f;
    }
}

void printArray(float* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(2) << arr[i] << " ";
    }
    cout << "\n";
}

void printMatrix(float** mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << fixed << setprecision(2) << mat[i][j] << "\t";
        }
        cout << "\n";
    }
}

float** createMatrix(float* arr, int n) {
    int rows = n / 4;
    float** mat = new float* [rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new float[4];
        for (int j = 0; j < 4; j++) {
            mat[i][j] = arr[i * 4 + j];
        }
    }
    return mat;
}

void bubbleSort1D(float* arr, int n, bool asc) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (asc) {
                if (arr[j] > arr[j + 1]) {
                    float temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
            else {
                if (arr[j] < arr[j + 1]) {
                    float temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

float findMax1D(float* arr, int n) {
    float max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int main() {
    srand(time(0));

    int n_values[] = { 20, 100, 1000 };
    int num_tests = 3;

    ofstream outfile("output.txt");
    outfile << "No | n    | Time, sec. | Space, byte\n";

    for (int t = 0; t < num_tests; t++) {
        int n = n_values[t];

        if (!checkMultipleOf4(n)) {
            continue;
        }

        clock_t start = clock();

        float* A = new float[n];
        generateArray(A, n);

        float** B = createMatrix(A, n);
        int rows = n / 4;

        for (int i = 0; i < rows; i++) {
            bubbleSort1D(B[i], 4, (i % 2 == 0));
        }

        float* max_vals = new float[4];
        for (int j = 0; j < 4; j++) {
            float* col = new float[rows];
            for (int i = 0; i < rows; i++) {
                col[i] = B[i][j];
            }
            max_vals[j] = findMax1D(col, rows);
            delete[] col;
        }

        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        int space = sizeof(float) * n + sizeof(float*) * rows + sizeof(float) * n + sizeof(float) * 4;

        outfile << t + 1 << "  | " << n << "   | " << fixed << setprecision(3) << time_spent << "      | " << space << "\n";

        if (n == 20) {
            cout << "Array A (n=20):\n";
            printArray(A, n);
            cout << "\nSorted Matrix B:\n";
            printMatrix(B, rows, 4);
            cout << "\nMax elements of each column:\n";
            printArray(max_vals, 4);
            cout << "\n-----------------------------------\n\n";
        }

        delete[] A;
        for (int i = 0; i < rows; i++) {
            delete[] B[i];
        }
        delete[] B;
        delete[] max_vals;
    }

    outfile.close();
    cout << "Test completed. Results written to output.txt\n";

    return 0;
}