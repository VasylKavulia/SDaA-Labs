#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <chrono>

using namespace std;

void task1() {
    map<string, int> wordCount;
    string word;
    cout << "Введіть текст (введіть END для завершення):\n";
    while (cin >> word && word != "END") {
        wordCount[word]++;
    }
    cout << "\nРезультат:\n";
    for (auto const& p : wordCount) {
        cout << p.first << ": " << p.second << "\n";
    }
}

void task2() {
    map<string, string> phonebook;
    int choice;
    string name, phone;
    while (true) {
        cout << "\n1. Додати\n2. Знайти\n3. Видалити\n0. Назад\nВибір: ";
        cin >> choice;
        if (choice == 0) break;
        if (choice == 1) {
            cout << "Ім'я: ";
            cin >> name;
            cout << "Номер: ";
            cin >> phone;
            phonebook[name] = phone;
        } else if (choice == 2) {
            cout << "Ім'я: ";
            cin >> name;
            if (phonebook.find(name) != phonebook.end()) {
                cout << "Номер: " << phonebook[name] << "\n";
            } else {
                cout << "Не знайдено\n";
            }
        } else if (choice == 3) {
            cout << "Ім'я: ";
            cin >> name;
            phonebook.erase(name);
        }
    }
}

map<string, int> students;

void updateGrade(string name, int grade) {
    students[name] = grade;
}

void task3() {
    updateGrade("Шевченко", 4);
    updateGrade("Франко", 5);
    
    cout << "Поточні оцінки:\n";
    for (auto const& p : students) {
        cout << p.first << ": " << p.second << "\n";
    }
    
    string name;
    int grade;
    cout << "\nВведіть ім'я студента: ";
    cin >> name;
    cout << "Введіть нову оцінку: ";
    cin >> grade;
    updateGrade(name, grade);
    
    cout << "Оновлений список оцінок:\n";
    for (auto const& p : students) {
        cout << p.first << ": " << p.second << "\n";
    }
}

void task4() {
    multimap<char, string> dict;
    string word;
    cout << "Введіть слова (введіть END для завершення):\n";
    while (cin >> word && word != "END") {
        dict.insert({word[0], word});
    }
    cout << "\nРезультат:\n";
    for (auto const& p : dict) {
        cout << p.first << ": " << p.second << "\n";
    }
}

void task5() {
    int N, M, K;
    cout << "Введіть N (вставка): ";
    cin >> N;
    cout << "Введіть M (видалення): ";
    cin >> M;
    cout << "Введіть K (пошук): ";
    cin >> K;

    map<int, int> treeMap;
    unordered_map<int, int> hashMap;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) treeMap[i] = i;
    auto end = chrono::high_resolution_clock::now();
    cout << "map вставка: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мкс\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) hashMap[i] = i;
    end = chrono::high_resolution_clock::now();
    cout << "unordered_map вставка: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мкс\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++) treeMap.erase(i);
    end = chrono::high_resolution_clock::now();
    cout << "map видалення: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мкс\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++) hashMap.erase(i);
    end = chrono::high_resolution_clock::now();
    cout << "unordered_map видалення: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мкс\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < K; i++) treeMap.find(i);
    end = chrono::high_resolution_clock::now();
    cout << "map пошук: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мкс\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < K; i++) hashMap.find(i);
    end = chrono::high_resolution_clock::now();
    cout << "unordered_map пошук: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мкс\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- МЕНЮ ЛАБОРАТОРНОЇ РОБОТИ №13 ---\n";
        cout << "1. Завдання 1 (map: підрахунок слів)\n";
        cout << "2. Завдання 2 (map: телефонний довідник)\n";
        cout << "3. Завдання 3 (map: оцінки студентів)\n";
        cout << "4. Завдання 4 (multimap: групування слів)\n";
        cout << "5. Завдання 5 (map vs unordered_map)\n";
        cout << "0. Вихід\n";
        cout << "Вибір: ";
        cin >> choice;
        
        if (choice == 0) break;
        if (choice == 1) task1();
        if (choice == 2) task2();
        if (choice == 3) task3();
        if (choice == 4) task4();
        if (choice == 5) task5();
    }
    return 0;
}
