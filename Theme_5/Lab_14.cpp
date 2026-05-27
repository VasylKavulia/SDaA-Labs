#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void task1() {
    string text;
    cout << "Enter string: ";
    cin.ignore();
    getline(cin, text);

    map<char, int> charCount;
    for (char c : text) {
        charCount[c]++;
    }

    char maxChar = '\0';
    int maxCount = 0;

    cout << "Character counts:\n";
    for (auto const& p : charCount) {
        cout << p.first << ": " << p.second << "\n";
        if (p.second > maxCount) {
            maxCount = p.second;
            maxChar = p.first;
        }
    }

    if (maxCount > 0) {
        cout << "Most frequent: '" << maxChar << "' (" << maxCount << " times)\n";
    }
}

void task2() {
    map<string, int> warehouse;
    int choice;
    string name;
    int qty;

    while (true) {
        cout << "\n1. Add/Update item\n2. Delete item\n3. Find item\n4. Show all\n0. Back\nChoice: ";
        cin >> choice;

        if (choice == 0) break;
        
        if (choice == 1) {
            cout << "Item name: ";
            cin >> name;
            cout << "Quantity: ";
            cin >> qty;
            warehouse[name] = qty;
        } else if (choice == 2) {
            cout << "Item name to delete: ";
            cin >> name;
            warehouse.erase(name);
        } else if (choice == 3) {
            cout << "Item name to find: ";
            cin >> name;
            if (warehouse.find(name) != warehouse.end()) {
                cout << "Quantity: " << warehouse[name] << "\n";
            } else {
                cout << "Item not found\n";
            }
        } else if (choice == 4) {
            cout << "Warehouse items:\n";
            for (auto const& p : warehouse) {
                cout << p.first << " - " << p.second << " pcs\n";
            }
        }
    }
}

struct Student {
    string name;
    int group;
    double avgGrade;
};

bool compareStudents(const Student& a, const Student& b) {
    return a.avgGrade < b.avgGrade;
}

void task3() {
    vector<Student> students;
    int choice;

    while (true) {
        cout << "\n1. Add student\n2. Delete by name\n3. Sort by grade\n4. Search by group\n5. Filter by min grade\n0. Back\nChoice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            Student s;
            cout << "Name: ";
            cin >> s.name;
            cout << "Group: ";
            cin >> s.group;
            cout << "Average grade: ";
            cin >> s.avgGrade;
            students.push_back(s);
        } else if (choice == 2) {
            string targetName;
            cout << "Name to delete: ";
            cin >> targetName;
            vector<Student> temp;
            for (size_t i = 0; i < students.size(); i++) {
                if (students[i].name != targetName) {
                    temp.push_back(students[i]);
                }
            }
            students = temp;
        } else if (choice == 3) {
            sort(students.begin(), students.end(), compareStudents);
            cout << "Sorted.\n";
        } else if (choice == 4) {
            int targetGroup;
            cout << "Group to search: ";
            cin >> targetGroup;
            for (size_t i = 0; i < students.size(); i++) {
                if (students[i].group == targetGroup) {
                    cout << students[i].name << " (Grade: " << students[i].avgGrade << ")\n";
                }
            }
        } else if (choice == 5) {
            double minGrade;
            cout << "Minimum grade: ";
            cin >> minGrade;
            for (size_t i = 0; i < students.size(); i++) {
                if (students[i].avgGrade > minGrade) {
                    cout << students[i].name << " (Group: " << students[i].group << ", Grade: " << students[i].avgGrade << ")\n";
                }
            }
        }
    }
}

void task4() {
    multimap<int, string> wordsMap;
    string word;
    
    cout << "Enter words (END to stop):\n";
    while (cin >> word && word != "END") {
        wordsMap.insert({word.length(), word});
    }

    cout << "\nGrouped words:\n";
    int currentLen = -1;
    int count = 0;
    
    for (auto it = wordsMap.begin(); it != wordsMap.end(); ++it) {
        if (it->first != currentLen) {
            if (currentLen != -1) {
                cout << "Total words: " << count << "\n\n";
            }
            currentLen = it->first;
            count = 0;
            cout << "Length " << currentLen << ":\n";
        }
        cout << "- " << it->second << "\n";
        count++;
    }
    if (currentLen != -1) {
        cout << "Total words: " << count << "\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- LAB 14 (VAR 1) MENU ---\n";
        cout << "1. Task 1 (map chars)\n";
        cout << "2. Task 2 (map warehouse)\n";
        cout << "3. Task 3 (vector students)\n";
        cout << "4. Task 4 (multimap word lengths)\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 0) break;
        if (choice == 1) task1();
        if (choice == 2) task2();
        if (choice == 3) task3();
        if (choice == 4) task4();
    }
    return 0;
}
