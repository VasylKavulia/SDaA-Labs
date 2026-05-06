#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>

using namespace std;

struct ABITURIENT {
    char NAME[50];
    char GENDER[10];
    char SPEC[50];
    int EXAM[3];
};

float calculateAverage(ABITURIENT a) {
    return (a.EXAM[0] + a.EXAM[1] + a.EXAM[2]) / 3.0f;
}

bool isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

void printMaxThreeVowels(ABITURIENT* arr, int n) {
    cout << "\n--- Abiturients with <= 3 vowels in name ---\n";
    for (int i = 0; i < n; i++) {
        int vowelCount = 0;
        for (int j = 0; arr[i].NAME[j] != '\0'; j++) {
            if (isVowel(arr[i].NAME[j])) {
                vowelCount++;
            }
        }
        if (vowelCount <= 3) {
            cout << arr[i].NAME << "\n";
        }
    }
}

void printBelowPassingScore(ABITURIENT* arr, int n, float passingScore) {
    cout << "\n--- Abiturients below passing score (" << passingScore << ") ---\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (calculateAverage(arr[i]) < passingScore) {
            cout << arr[i].NAME << " - " << arr[i].SPEC << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No such abiturients found.\n";
    }
}

void sortAlphabetically(ABITURIENT* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].NAME, arr[j + 1].NAME) > 0) {
                ABITURIENT temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void deletePerfectScores(ABITURIENT*& arr, int& n) {
    int new_n = 0;
    for (int i = 0; i < n; i++) {
        if (calculateAverage(arr[i]) != 5.0f) {
            new_n++;
        }
    }

    ABITURIENT* new_arr = new ABITURIENT[new_n];
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (calculateAverage(arr[i]) != 5.0f) {
            new_arr[index++] = arr[i];
        }
    }

    delete[] arr;
    arr = new_arr;
    n = new_n;
}

void printArray(ABITURIENT* arr, int n) {
    cout << left << setw(20) << "Name" << setw(10) << "Gender" << setw(20) << "Specialty" << "Exams\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(20) << arr[i].NAME
            << setw(10) << arr[i].GENDER
            << setw(20) << arr[i].SPEC
            << arr[i].EXAM[0] << " " << arr[i].EXAM[1] << " " << arr[i].EXAM[2] << "\n";
    }
}

int main() {
    int n = 5;
    ABITURIENT* arr = new ABITURIENT[n];

    strcpy(arr[0].NAME, "Nikita O.");
    strcpy(arr[0].GENDER, "Male");
    strcpy(arr[0].SPEC, "Computer Science");
    arr[0].EXAM[0] = 5; arr[0].EXAM[1] = 5; arr[0].EXAM[2] = 5;

    strcpy(arr[1].NAME, "Olena G.");
    strcpy(arr[1].GENDER, "Female");
    strcpy(arr[1].SPEC, "Mathematics");
    arr[1].EXAM[0] = 4; arr[1].EXAM[1] = 3; arr[1].EXAM[2] = 4;

    strcpy(arr[2].NAME, "Ivan L.");
    strcpy(arr[2].GENDER, "Male");
    strcpy(arr[2].SPEC, "Physics");
    arr[2].EXAM[0] = 3; arr[2].EXAM[1] = 3; arr[2].EXAM[2] = 4;

    strcpy(arr[3].NAME, "Lisa Y.");
    strcpy(arr[3].GENDER, "Female");
    strcpy(arr[3].SPEC, "Biology");
    arr[3].EXAM[0] = 5; arr[3].EXAM[1] = 4; arr[3].EXAM[2] = 5;

    strcpy(arr[4].NAME, "Misha R.");
    strcpy(arr[4].GENDER, "Male");
    strcpy(arr[4].SPEC, "Engineering");
    arr[4].EXAM[0] = 5; arr[4].EXAM[1] = 5; arr[4].EXAM[2] = 5;

    cout << "--- Initial Array ---\n";
    printArray(arr, n);

    printMaxThreeVowels(arr, n);

    float passingScore;
    cout << "\nEnter passing score (e.g., 4.0): ";
    passingScore = 4.0f;
    cout << passingScore << "\n";

    printBelowPassingScore(arr, n, passingScore);

    sortAlphabetically(arr, n);
    cout << "\n--- Sorted alphabetically ---\n";
    printArray(arr, n);

    deletePerfectScores(arr, n);
    cout << "\n--- After removing abiturients with average 5.0 ---\n";
    printArray(arr, n);

    delete[] arr;

    return 0;
}