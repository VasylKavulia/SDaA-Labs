#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

struct TempNode {
    int day;
    float temp;
    TempNode* prev;
    TempNode* next;
};

void pushBackTemp(TempNode*& head, TempNode*& tail, int d, float t) {
    TempNode* newNode = new TempNode;
    newNode->day = d;
    newNode->temp = t;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void printTemp(TempNode* head) {
    while (head) {
        cout << "Date: " << head->day << ", Temp: " << fixed << setprecision(1) << head->temp << " C\n";
        head = head->next;
    }
}

void freeTemp(TempNode*& head) {
    while (head) {
        TempNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void task1() {
    cout << "--- TASK 1 ---\n";
    TempNode* head1 = nullptr;
    TempNode* tail1 = nullptr;
    TempNode* head2 = nullptr;
    TempNode* tail2 = nullptr;

    pushBackTemp(head1, tail1, 1, 14.5f);
    pushBackTemp(head1, tail1, 2, 16.0f);
    pushBackTemp(head1, tail1, 3, 12.3f);

    pushBackTemp(head2, tail2, 4, 11.0f);
    pushBackTemp(head2, tail2, 5, 18.2f);
    pushBackTemp(head2, tail2, 6, 17.5f);

    cout << "List 1 (Month 1):\n";
    printTemp(head1);

    cout << "\nList 2 (Month 2):\n";
    printTemp(head2);

    if (tail1 && head2) {
        tail1->next = head2;
        head2->prev = tail1;
        tail1 = tail2;
    }
    else if (!head1) {
        head1 = head2;
        tail1 = tail2;
    }

    cout << "\nMerged List:\n";
    printTemp(head1);

    if (head1) {
        float minT = head1->temp;
        float maxT = head1->temp;
        TempNode* curr = head1->next;

        while (curr) {
            if (curr->temp < minT) minT = curr->temp;
            if (curr->temp > maxT) maxT = curr->temp;
            curr = curr->next;
        }

        cout << "\nMax temperature: " << maxT << " C\n";
        cout << "Min temperature: " << minT << " C\n";
    }

    freeTemp(head1);
    cout << "Memory freed for Task 1.\n\n";
}

struct EmpNode {
    char name[50];
    char dept[50];
    float salary;
    EmpNode* prev;
    EmpNode* next;
};

void pushBackEmp(EmpNode*& head, EmpNode*& tail, const char* n, const char* d, float s) {
    EmpNode* newNode = new EmpNode;
    strcpy(newNode->name, n);
    strcpy(newNode->dept, d);
    newNode->salary = s;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void printEmpForward(EmpNode* head) {
    while (head) {
        cout << head->name << " | " << head->dept << " | " << fixed << setprecision(2) << head->salary << " USD\n";
        head = head->next;
    }
}

void printEmpReverse(EmpNode* tail) {
    while (tail) {
        cout << tail->name << " | " << tail->dept << " | " << fixed << setprecision(2) << tail->salary << " USD\n";
        tail = tail->prev;
    }
}

void freeEmp(EmpNode*& head) {
    while (head) {
        EmpNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void task2() {
    cout << "--- TASK 2 ---\n";
    EmpNode* head = nullptr;
    EmpNode* tail = nullptr;

    pushBackEmp(head, tail, "Oleg", "IT", 4500.0f);
    pushBackEmp(head, tail, "Ivan", "HR", 2500.0f);
    pushBackEmp(head, tail, "Maria", "IT", 5200.0f);
    pushBackEmp(head, tail, "Nikita", "Finance", 3800.0f);
    pushBackEmp(head, tail, "Andrey", "Marketing", 3000.0f);

    cout << "Employee List:\n";
    printEmpForward(head);

    float sum = 0;
    int count = 0;
    EmpNode* curr = head;
    while (curr) {
        sum += curr->salary;
        count++;
        curr = curr->next;
    }

    float avgSalary = (count > 0) ? (sum / count) : 0;
    cout << "\nAverage salary: " << avgSalary << " USD\n\n";

    EmpNode* highHead = nullptr;
    EmpNode* highTail = nullptr;
    EmpNode* lowHead = nullptr;
    EmpNode* lowTail = nullptr;

    curr = head;
    while (curr) {
        if (curr->salary > avgSalary) {
            pushBackEmp(highHead, highTail, curr->name, curr->dept, curr->salary);
        }
        else {
            pushBackEmp(lowHead, lowTail, curr->name, curr->dept, curr->salary);
        }
        curr = curr->next;
    }

    cout << "--- Above average salary ---\n";
    cout << "Forward:\n";
    printEmpForward(highHead);
    cout << "Reverse:\n";
    printEmpReverse(highTail);

    cout << "\n--- Below or equal to average salary ---\n";
    cout << "Forward:\n";
    printEmpForward(lowHead);
    cout << "Reverse:\n";
    printEmpReverse(lowTail);

    cout << "\nAdding new employee to the above average list\n";
    pushBackEmp(highHead, highTail, "Davis", "Management", 6000.0f);

    cout << "Updated above average list:\n";
    printEmpForward(highHead);

    freeEmp(head);
    freeEmp(highHead);
    freeEmp(lowHead);
    cout << "\nMemory freed for Task 2.\n";
}

int main() {
    task1();
    task2();
    return 0;
}