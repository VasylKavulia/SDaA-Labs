#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

struct worker {
    char name[50];
    char position[50];
    int year_joined;
    float base_salary;
};

int experience(worker w, int current_year) {
    return current_year - w.year_joined;
}

float salary(worker w) {
    return w.base_salary * 0.67f;
}

enum Faculty { IT, ECONOMICS, LAW, MANAGEMENT };

struct Student {
    char name[50];
    int course;
    float avg_grade;
    Faculty faculty;
};

void printFaculty(Faculty f) {
    switch (f) {
    case IT: cout << "IT"; break;
    case ECONOMICS: cout << "Economics"; break;
    case LAW: cout << "Law"; break;
    case MANAGEMENT: cout << "Management"; break;
    }
}

enum PaymentType { CASH, CARD, BANK_TRANSFER };

union PaymentDetails {
    char currency[10];
    char card_number[20];
    char bank_account[30];
};

struct Payment {
    int id;
    PaymentType type;
    float amount;
    PaymentDetails details;
};

void printPaymentType(PaymentType pt) {
    switch (pt) {
    case CASH: cout << "Cash"; break;
    case CARD: cout << "Card"; break;
    case BANK_TRANSFER: cout << "Bank Transfer"; break;
    }
}

void task1() {
    cout << "--- TASK 1 ---\n";
    int n = 3;
    worker workers[3] = {
        {"Ivan K.", "Manager", 2018, 5000.0f},
        {"Maria P.", "Developer", 2021, 6000.0f},
        {"Leonid O.", "Designer", 2015, 4500.0f}
    };

    int current_year = 2026;

    cout << left << setw(15) << "Name" << setw(15) << "Position"
        << setw(15) << "Experience" << setw(15) << "Net Salary" << "\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(15) << workers[i].name
            << setw(15) << workers[i].position
            << setw(15) << experience(workers[i], current_year)
            << fixed << setprecision(2) << salary(workers[i]) << "\n";
    }
    cout << "\n";
}

void task2() {
    cout << "--- TASK 2 ---\n";
    int n = 5;
    Student students[5] = {
        {"Nikita M.", 2, 85.5f, IT},
        {"Oleg I.", 3, 90.0f, ECONOMICS},
        {"Nazar O.", 1, 78.2f, IT},
        {"Lubomir D.", 4, 92.4f, LAW},
        {"Ardrey V", 2, 88.1f, MANAGEMENT}
    };

    Faculty target_faculty = IT;
    cout << "Students in IT faculty:\n";

    float total_score = 0;

    for (int i = 0; i < n; i++) {
        if (students[i].faculty == target_faculty) {
            cout << "" << students[i].name << " Course " << students[i].course << "\n";
        }
        total_score += students[i].avg_grade;
    }

    float group_avg = total_score / n;
    cout << "Average grade of group: " << fixed << setprecision(2) << group_avg << "\n\n";
}

void task3() {
    cout << "--- TASK 3 ---\n";
    int n = 4;
    Payment payments[4];

    payments[0].id = 101;
    payments[0].type = CASH;
    payments[0].amount = 150.50f;
    strcpy(payments[0].details.currency, "USD");

    payments[1].id = 102;
    payments[1].type = CARD;
    payments[1].amount = 890.00f;
    strcpy(payments[1].details.card_number, "1111-2222-3333-4444");

    payments[2].id = 103;
    payments[2].type = BANK_TRANSFER;
    payments[2].amount = 1200.00f;
    strcpy(payments[2].details.bank_account, "UA1234567890123456789");

    payments[3].id = 104;
    payments[3].type = CARD;
    payments[3].amount = 45.00f;
    strcpy(payments[3].details.card_number, "5555-6666-7777-8888");

    int cash_count = 0, card_count = 0, bank_count = 0;

    cout << left << setw(10) << "ID" << setw(15) << "Type"
        << setw(10) << "Amount" << "Details\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << payments[i].id << setw(15);

        switch (payments[i].type) {
        case CASH:
            cout << "Cash";
            cash_count++;
            cout << setw(10) << payments[i].amount << payments[i].details.currency << "\n";
            break;
        case CARD:
            cout << "Card";
            card_count++;
            cout << setw(10) << payments[i].amount << payments[i].details.card_number << "\n";
            break;
        case BANK_TRANSFER:
            cout << "Bank Transfer";
            bank_count++;
            cout << setw(10) << payments[i].amount << payments[i].details.bank_account << "\n";
            break;
        }
    }

    cout << "\nPayment counts:\n";
    cout << "Cash: " << cash_count << "\n";
    cout << "Card: " << card_count << "\n";
    cout << "Bank Transfer: " << bank_count << "\n";
}

int main() {
    task1();
    task2();
    task3();

    return 0;
}