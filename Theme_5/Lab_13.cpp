#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <chrono>

using namespace std;

void task1() {
    map<string, int> wordCount;
    string word;
    cout << "Enter text (END to stop):\n";
    while (cin >> word && word != "END") {
        wordCount[word]++;
    }
    cout << "\nResult:\n";
    for (auto const& p : wordCount) {
        cout << p.first << ": " << p.second << "\n";
    }
}

void task2() {
    map<string, string> phonebook;
    int choice;
    string name, phone;
    while (true) {
        cout << "\n1. Add\n2. Find\n3. Delete\n0. Back\nChoice: ";
        cin >> choice;
        if (choice == 0) break;
        if (choice == 1) {
            cout << "Name: ";
            cin >> name;
            cout << "Phone: ";
            cin >> phone;
            phonebook[name] = phone;
        } else if (choice == 2) {
            cout << "Name: ";
            cin >> name;
            if (phonebook.find(name) != phonebook.end()) {
                cout << "Phone: " << phonebook[name] << "\n";
            } else {
                cout << "Not found\n";
            }
        } else if (choice == 3) {
            cout << "Name: ";
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
    updateGrade("Smith", 4);
    updateGrade("Johnson", 5);
    
    cout << "Current grades:\n";
    for (auto const& p : students) {
        cout << p.first << ": " << p.second << "\n";
    }
    
    string name;
    int grade;
    cout << "\nEnter student name: ";
    cin >> name;
    cout << "Enter new grade: ";
    cin >> grade;
    updateGrade(name, grade);
    
    cout << "Updated grades:\n";
    for (auto const& p : students) {
        cout << p.first << ": " << p.second << "\n";
    }
}

void task4() {
    multimap<char, string> dict;
    string word;
    cout << "Enter words (END to stop):\n";
    while (cin >> word && word != "END") {
        dict.insert({word[0], word});
    }
    cout << "\nResult:\n";
    for (auto const& p : dict) {
        cout << p.first << ": " << p.second << "\n";
    }
}

void task5() {
    int N, M, K;
    cout << "Enter N (insert): ";
    cin >> N;
    cout << "Enter M (delete): ";
    cin >> M;
    cout << "Enter K (search): ";
    cin >> K;

    map<int, int> treeMap;
    unordered_map<int, int> hashMap;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) treeMap[i] = i;
    auto end = chrono::high_resolution_clock::now();
    cout << "map insert: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) hashMap[i] = i;
    end = chrono::high_resolution_clock::now();
    cout << "unordered_map insert: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++) treeMap.erase(i);
    end = chrono::high_resolution_clock::now();
    cout << "map delete: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++) hashMap.erase(i);
    end = chrono::high_resolution_clock::now();
    cout << "unordered_map delete: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < K; i++) treeMap.find(i);
    end = chrono::high_resolution_clock::now();
    cout << "map search: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < K; i++) hashMap.find(i);
    end = chrono::high_resolution_clock::now();
    cout << "unordered_map search: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- LAB 13 MENU ---\n";
        cout << "1. Task 1 (map word count)\n";
        cout << "2. Task 2 (map phonebook)\n";
        cout << "3. Task 3 (map students)\n";
        cout << "4. Task 4 (multimap words)\n";
        cout << "5. Task 5 (map vs unordered_map)\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
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
