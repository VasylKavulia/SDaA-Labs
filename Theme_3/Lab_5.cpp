#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

struct Node1 {
    int data;
    Node1* next;
};

void pushFront1(Node1*& head, int val) {
    Node1* newNode = new Node1;
    newNode->data = val;
    newNode->next = head;
    head = newNode;
}

void pushBack1(Node1*& head, int val) {
    Node1* newNode = new Node1;
    newNode->data = val;
    newNode->next = nullptr;
    if (!head) {
        head = newNode;
        return;
    }
    Node1* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAfter1(Node1* prev, int val) {
    if (!prev) return;
    Node1* newNode = new Node1;
    newNode->data = val;
    newNode->next = prev->next;
    prev->next = newNode;
}

void printList1(Node1* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n";
}

float getAverage1(Node1* head) {
    if (!head) return 0;
    int sum = 0;
    int count = 0;
    while (head) {
        sum += head->data;
        count++;
        head = head->next;
    }
    return (float)sum / count;
}

void removeFirstEven(Node1*& head) {
    if (!head) return;

    if (head->data % 2 == 0) {
        Node1* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node1* curr = head->next;
    Node1* prev = head;

    while (curr) {
        if (curr->data % 2 == 0) {
            prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void freeList1(Node1*& head) {
    while (head) {
        Node1* temp = head;
        head = head->next;
        delete temp;
    }
}

void task1() {
    cout << "--- TASK 1 ---\n";
    Node1* head = nullptr;

    pushFront1(head, 5);
    pushBack1(head, 15);
    insertAfter1(head, 10);
    pushBack1(head, 25);

    cout << "Initial list: ";
    printList1(head);

    cout << "Average: " << fixed << setprecision(2) << getAverage1(head) << "\n";

    removeFirstEven(head);
    cout << "List after removing first even element: ";
    printList1(head);

    freeList1(head);
    cout << "\n";
}

struct Node2 {
    char city[50];
    int distance;
    Node2* next;
};

void pushBack2(Node2*& head, const char* name, int dist) {
    Node2* newNode = new Node2;
    strcpy(newNode->city, name);
    newNode->distance = dist;
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
        return;
    }
    Node2* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printFurthestTwo(Node2* head) {
    if (!head || !head->next) return;

    Node2* max1 = nullptr;
    Node2* max2 = nullptr;

    Node2* temp = head;
    while (temp) {
        if (!max1 || temp->distance > max1->distance) {
            max2 = max1;
            max1 = temp;
        }
        else if (!max2 || temp->distance > max2->distance) {
            max2 = temp;
        }
        temp = temp->next;
    }

    cout << "Two furthest cities from Kyiv:\n";
    cout << "1. " << max1->city << " (" << max1->distance << " km)\n";
    cout << "2. " << max2->city << " (" << max2->distance << " km)\n";
}

void printList2(Node2* head) {
    while (head) {
        cout << head->city << " - " << head->distance << " km\n";
        head = head->next;
    }
}

void freeList2(Node2*& head) {
    while (head) {
        Node2* temp = head;
        head = head->next;
        delete temp;
    }
}

void task2() {
    cout << "--- TASK 2 ---\n";
    Node2* head = nullptr;

    pushBack2(head, "Lviv", 540);
    pushBack2(head, "Odesa", 475);
    pushBack2(head, "Kharkiv", 480);
    pushBack2(head, "Uzhhorod", 810);

    printFurthestTwo(head);

    cout << "\nAdding a foreign city\n";
    pushBack2(head, "Warsaw", 780);

    printList2(head);

    freeList2(head);
    cout << "\n";
}

struct Node3 {
    char model[50];
    int year;
    float price;
    Node3* next;
};

void pushBack3(Node3*& head, const char* mod, int yr, float pr) {
    Node3* newNode = new Node3;
    strcpy(newNode->model, mod);
    newNode->year = yr;
    newNode->price = pr;
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
        return;
    }
    Node3* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printFilteredCars(Node3* head, int currentYear) {
    cout << "Cars older than 10 years and cheaper than 5000:\n";
    bool found = false;
    while (head) {
        if ((currentYear - head->year > 10) && (head->price < 5000.0f)) {
            cout << head->model << " (" << head->year << ") - " << head->price << " USD\n";
            found = true;
        }
        head = head->next;
    }
    if (!found) {
        cout << "No matching cars found.\n";
    }
}

void freeList3(Node3*& head) {
    while (head) {
        Node3* temp = head;
        head = head->next;
        delete temp;
    }
}

void task3() {
    cout << "--- TASK 3 ---\n";
    Node3* head = nullptr;
    int currentYear = 2026;

    pushBack3(head, "Toyota Corolla", 2010, 4500.0f);
    pushBack3(head, "Honda Civic", 2018, 12000.0f);
    pushBack3(head, "Ford Focus", 2008, 3800.0f);
    pushBack3(head, "BMW 3 Series", 2015, 9500.0f);
    pushBack3(head, "Volkswagen Golf", 2011, 4900.0f);

    printFilteredCars(head, currentYear);

    freeList3(head);
    cout << "\n";
}

int main() {
    task1();
    task2();
    task3();

    return 0;
}