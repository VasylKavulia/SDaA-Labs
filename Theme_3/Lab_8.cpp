#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

struct StackNode {
    int grade;
    StackNode* next;
};

void push(StackNode*& top, int g) {
    StackNode* newNode = new StackNode;
    newNode->grade = g;
    newNode->next = top;
    top = newNode;
}

int pop(StackNode*& top) {
    if (!top) return 0;
    int val = top->grade;
    StackNode* temp = top;
    top = top->next;
    delete temp;
    return val;
}

void task1() {
    cout << "--- TASK 1 ---\n";
    StackNode* stack = nullptr;

    int n = 5;
    int grades[] = { 85, 90, 78, 92, 88 };

    for (int i = 0; i < n; i++) {
        push(stack, grades[i]);
    }

    cout << "Stack elements:\n";
    int sum = 0;
    int count = 0;
    StackNode* curr = stack;
    while (curr) {
        cout << curr->grade << " ";
        sum += curr->grade;
        count++;
        curr = curr->next;
    }
    cout << "\n";

    if (count > 0) {
        cout << "Average grade: " << fixed << setprecision(2) << (float)sum / count << "\n";
    }

    while (stack) {
        pop(stack);
    }
    cout << "Stack cleared.\n\n";
}

struct CourseNode {
    char name[50];
    int hours;
    int listeners;
    CourseNode* prev;
    CourseNode* next;
};

void pushBackCourse(CourseNode*& head, CourseNode*& tail, const char* n, int h, int l) {
    CourseNode* newNode = new CourseNode;
    strcpy(newNode->name, n);
    newNode->hours = h;
    newNode->listeners = l;
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

void printForward(CourseNode* head) {
    while (head) {
        cout << left << setw(15) << head->name
            << "| " << setw(4) << head->hours << " hrs | "
            << head->listeners << " listeners\n";
        head = head->next;
    }
}

void printReverse(CourseNode* tail) {
    while (tail) {
        cout << left << setw(15) << tail->name
            << "| " << setw(4) << tail->hours << " hrs | "
            << tail->listeners << " listeners\n";
        tail = tail->prev;
    }
}

void freeList(CourseNode*& head) {
    while (head) {
        CourseNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void task2() {
    cout << "--- TASK 2 ---\n";
    CourseNode* head = nullptr;
    CourseNode* tail = nullptr;

    pushBackCourse(head, tail, "Math", 120, 45);
    pushBackCourse(head, tail, "Physics", 90, 30);
    pushBackCourse(head, tail, "CS", 150, 60);
    pushBackCourse(head, tail, "Literature", 60, 20);
    pushBackCourse(head, tail, "History", 80, 25);

    cout << "Courses list:\n";
    printForward(head);

    int sum = 0;
    int count = 0;
    CourseNode* curr = head;
    while (curr) {
        sum += curr->listeners;
        count++;
        curr = curr->next;
    }

    float avg = (count > 0) ? (float)sum / count : 0;
    cout << "\nAverage number of listeners: " << avg << "\n\n";

    CourseNode* aboveHead = nullptr;
    CourseNode* aboveTail = nullptr;
    CourseNode* belowHead = nullptr;
    CourseNode* belowTail = nullptr;

    curr = head;
    while (curr) {
        if (curr->listeners > avg) {
            pushBackCourse(aboveHead, aboveTail, curr->name, curr->hours, curr->listeners);
        }
        else {
            pushBackCourse(belowHead, belowTail, curr->name, curr->hours, curr->listeners);
        }
        curr = curr->next;
    }

    cout << "--- Courses with listeners above average ---\n";
    cout << "[Forward]:\n";
    printForward(aboveHead);
    cout << "\n[Reverse]:\n";
    printReverse(aboveTail);

    cout << "\n--- Courses with listeners below or equal to average ---\n";
    cout << "[Forward]:\n";
    printForward(belowHead);
    cout << "\n[Reverse]:\n";
    printReverse(belowTail);

    freeList(head);
    freeList(aboveHead);
    freeList(belowHead);
    cout << "\nMemory freed for Task 2.\n";
}

int main() {
    task1();
    task2();
    return 0;
}