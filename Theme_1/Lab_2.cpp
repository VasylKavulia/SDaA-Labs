#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void bubbleSort(int* arr, int n, bool asc) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (asc) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
            else {
                if (arr[j] < arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void printMatrix(int** mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << "\n";
    }
}

void task1(int n) {
    cout << "--- TASK 1 ---\n";
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    cout << "Original array: ";
    printArray(arr, n);

    int* evens = new int[n];
    int* odds = new int[n];
    int e_count = 0, o_count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            evens[e_count++] = arr[i];
        }
        else {
            odds[o_count++] = arr[i];
        }
    }

    clock_t start_even = clock();
    bubbleSort(evens, e_count, true);
    clock_t end_even = clock();

    clock_t start_odd = clock();
    bubbleSort(odds, o_count, false);
    clock_t end_odd = clock();

    for (int i = 0; i < e_count; i++) arr[i] = evens[i];
    for (int i = 0; i < o_count; i++) arr[e_count + i] = odds[i];

    cout << "Modified array: ";
    printArray(arr, n);

    double time_even = (double)(end_even - start_even) / CLOCKS_PER_SEC;
    double time_odd = (double)(end_odd - start_odd) / CLOCKS_PER_SEC;

    cout << fixed << setprecision(6);
    cout << "Ascending (even) sort time: " << time_even << " sec\n";
    cout << "Descending (odd) sort time: " << time_odd << " sec\n\n";

    delete[] arr;
    delete[] evens;
    delete[] odds;
}

bool isUnique(int* arr, int size, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) return false;
    }
    return true;
}

void removeElementsTask2(int* arr, int n, int X) {
    int writeIdx = 0;
    int removedCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > X) {
            arr[writeIdx++] = arr[i];
        }
        else {
            removedCount++;
        }
    }
    for (int i = 0; i < removedCount; i++) {
        arr[writeIdx++] = 0;
    }
}

void task2(int n, int X) {
    cout << "--- TASK 2 ---\n";
    int* arr = new int[n];
    int count = 0;

    while (count < n) {
        int val = rand() % 100;
        if (isUnique(arr, count, val)) {
            arr[count++] = val;
        }
    }

    cout << "Unique array: ";
    printArray(arr, n);
    cout << "Threshold X: " << X << "\n";

    removeElementsTask2(arr, n, X);

    cout << "Modified array: ";
    printArray(arr, n);

    int space_complexity = sizeof(int) * n;
    cout << "Space for this task: " << space_complexity << " bytes\n\n";

    delete[] arr;
}

void task3() {
    cout << "--- TASK 3 ---\n";
    int n = 5;
    int** mat = new int* [n];
    for (int i = 0; i < n; i++) {
        mat[i] = new int[n];
        for (int j = 0; j < n; j++) {
            mat[i][j] = rand() % 100;
        }
    }

    cout << "Original 5x5 matrix:\n";
    printMatrix(mat, n, n);

    clock_t start = clock();

    int max_val = mat[0][0];
    int max_i = 0, max_j = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] > max_val) {
                max_val = mat[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    if (max_i != 0) {
        for (int j = 0; j < n; j++) {
            int temp = mat[0][j];
            mat[0][j] = mat[max_i][j];
            mat[max_i][j] = temp;
        }
        cout << "\nIteration 1 (Rows swapped):\n";
        printMatrix(mat, n, n);
    }

    if (max_j != 0) {
        for (int i = 0; i < n; i++) {
            int temp = mat[i][0];
            mat[i][0] = mat[i][max_j];
            mat[i][max_j] = temp;
        }
        cout << "\nIteration 2 (Cols swapped):\n";
        printMatrix(mat, n, n);
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "Time for this task: " << fixed << setprecision(6) << time_spent << " sec\n\n";

    for (int i = 0; i < n; i++) delete[] mat[i];
    delete[] mat;
}

void task4(int n) {
    cout << "--- TASK 4 ---\n";
    int** mat = new int* [n];
    for (int i = 0; i < n; i++) {
        mat[i] = new int[n];
        for (int j = 0; j < n; j++) {
            mat[i][j] = rand() % 100;
        }
    }

    cout << "Original square matrix:\n";
    printMatrix(mat, n, n);

    int** new_mat = new int* [n];
    for (int i = 0; i < n; i++) {
        new_mat[i] = new int[n - 1];
        int col_idx = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                new_mat[i][col_idx++] = mat[i][j];
            }
        }
    }

    cout << "\nMatrix after removing main diagonal:\n";
    printMatrix(new_mat, n, n - 1);

    int max_val = new_mat[0][0];
    int max_row = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (new_mat[i][j] > max_val) {
                max_val = new_mat[i][j];
                max_row = i;
            }
        }
    }

    int** final_mat = new int* [n - 1];
    int row_idx = 0;
    for (int i = 0; i < n; i++) {
        if (i != max_row) {
            final_mat[row_idx] = new int[n - 1];
            for (int j = 0; j < n - 1; j++) {
                final_mat[row_idx][j] = new_mat[i][j];
            }
            row_idx++;
        }
    }

    cout << "\nMatrix after removing row with max element (" << max_val << "):\n";
    printMatrix(final_mat, n - 1, n - 1);

    for (int i = 0; i < n; i++) delete[] mat[i];
    delete[] mat;

    for (int i = 0; i < n; i++) delete[] new_mat[i];
    delete[] new_mat;

    for (int i = 0; i < n - 1; i++) delete[] final_mat[i];
    delete[] final_mat;
}

int main() {
    srand(time(0));

    task1(20);
    task2(15, 50);
    task3();
    task4(4);

    return 0;
}