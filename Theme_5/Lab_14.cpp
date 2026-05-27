#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void task1() {
    string text;
    cout << "Введіть рядок: ";
    cin.ignore();
    getline(cin, text);

    map<char, int> charCount;
    for (char c : text) {
        charCount[c]++;
    }

    char maxChar = '\0';
    int maxCount = 0;

    cout << "Символи та їх кількість:\n";
    for (auto const& p : charCount) {
        cout << p.first << ": " << p.second << "\n";
        if (p.second > maxCount) {
            maxCount = p.second;
            maxChar = p.first;
        }
    }

    if (maxCount > 0) {
        cout << "Найчастіше зустрічається: '" << maxChar << "' (" << maxCount << " разів)\n";
    }
}

void task2() {
    map<string, int> warehouse;
    int choice;
    string name;
    int qty;

    while (true) {
        cout << "\n1. Додати/Змінити товар\n2. Видалити товар\n3. Знайти товар\n4. Вивести всі\n0. Назад\nВибір: ";
        cin >> choice;

        if (choice == 0) break;
        
        if (choice == 1) {
            cout << "Назва товару: ";
            cin >> name;
            cout << "Кількість: ";
            cin >> qty;
            warehouse[name] = qty;
        } else if (choice == 2) {
            cout << "Назва товару для видалення: ";
            cin >> name;
            warehouse.erase(name);
        } else if (choice == 3) {
            cout << "Назва товару для пошуку: ";
            cin >> name;
            if (warehouse.find(name) != warehouse.end()) {
                cout << "Кількість: " << warehouse[name] << "\n";
            } else {
                cout << "Товар не знайдено\n";
            }
        } else if (choice == 4) {
            cout << "Список товарів:\n";
            for (auto const& p : warehouse) {
                cout << p.first << " - " << p.second << " шт.\n";
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
        cout << "\n1. Додати студента\n2. Видалити за ПІБ\n3. Сортувати за балом\n4. Пошук за групою\n5. Вивести з балом вище заданого\n0. Назад\nВибір: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            Student s;
            cout << "ПІБ: ";
            cin >> s.name;
            cout << "Група: ";
            cin >> s.group;
            cout << "Середній бал: ";
            cin >> s.avgGrade;
            students.push_back(s);
        } else if (choice == 2) {
            string targetName;
            cout << "ПІБ для видалення: ";
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
            cout << "Відсортовано.\n";
        } else if (choice == 4) {
            int targetGroup;
            cout << "Група для пошуку: ";
            cin >> targetGroup;
            for (size_t i = 0; i < students.size(); i++) {
                if (students[i].group == targetGroup) {
                    cout << students[i].name << " (Бал: " << students[i].avgGrade << ")\n";
                }
            }
        } else if (choice == 5) {
            double minGrade;
            cout << "Мінімальний бал: ";
            cin >> minGrade;
            for (size_t i = 0; i < students.size(); i++) {
                if (students[i].avgGrade > minGrade) {
                    cout << students[i].name << " (Група: " << students[i].group << ", Бал: " << students[i].avgGrade << ")\n";
                }
            }
        }
    }
}

void task4() {
    multimap<int, string> wordsMap;
    string word;
    
    cout << "Введіть слова (введіть END для завершення):\n";
    while (cin >> word && word != "END") {
        wordsMap.insert({word.length(), word});
    }

    cout << "\nЗгруповані слова:\n";
    int currentLen = -1;
    int count = 0;
    
    for (auto it = wordsMap.begin(); it != wordsMap.end(); ++it) {
        if (it->first != currentLen) {
            if (currentLen != -1) {
                cout << "Кількість слів: " << count << "\n\n";
            }
            currentLen = it->first;
            count = 0;
            cout << "Довжина " << currentLen << ":\n";
        }
        cout << "- " << it->second << "\n";
        count++;
    }
    if (currentLen != -1) {
        cout << "Кількість слів: " << count << "\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- ЛАБОРАТОРНА РОБОТА 14 (ВАРІАНТ 1) ---\n";
        cout << "1. Завдання 1 (map: символи)\n";
        cout << "2. Завдання 2 (map: склад товарів)\n";
        cout << "3. Завдання 3 (vector: студенти)\n";
        cout << "4. Завдання 4 (multimap: довжина слів)\n";
        cout << "0. Вихід\n";
        cout << "Вибір: ";
        cin >> choice;

        if (choice == 0) break;
        if (choice == 1) task1();
        if (choice == 2) task2();
        if (choice == 3) task3();
        if (choice == 4) task4();
    }
    return 0;
}
