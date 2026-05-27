#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

using namespace std;

struct Book {
    string title;
    string genre;
    double price;
    int popularity;
    int year;
    bool isSold;
};

vector<Book> store;

void addBook(string t, string g, double p, int pop, int y, bool sold = false) {
    Book b;
    b.title = t;
    b.genre = g;
    b.price = p;
    b.popularity = pop;
    b.year = y;
    b.isSold = sold;
    store.push_back(b);
}

void removeSoldBooks() {
    vector<Book> temp;
    for (size_t i = 0; i < store.size(); i++) {
        if (!store[i].isSold) {
            temp.push_back(store[i]);
        }
    }
    store = temp;
}

bool compareByPrice(const Book& a, const Book& b) { return a.price < b.price; }
bool compareByPop(const Book& a, const Book& b) { return a.popularity > b.popularity; }
bool compareByDate(const Book& a, const Book& b) { return a.year > b.year; }

void sortBooks(int mode) {
    if (mode == 1) sort(store.begin(), store.end(), compareByPrice);
    else if (mode == 2) sort(store.begin(), store.end(), compareByPop);
    else if (mode == 3) sort(store.begin(), store.end(), compareByDate);
}

void filterBooks(string targetGenre, double minPrice, double maxPrice) {
    cout << "\n--- Filtered Books ---\n";
    for (size_t i = 0; i < store.size(); i++) {
        if (store[i].genre == targetGenre && store[i].price >= minPrice && store[i].price <= maxPrice) {
            cout << store[i].title << " (" << store[i].price << " UAH)\n";
        }
    }
}

void searchBook(string title) {
    for (size_t i = 0; i < store.size(); i++) {
        if (store[i].title == title) {
            cout << "Book found: " << store[i].title << ", Genre: " << store[i].genre 
                 << ", Price: " << store[i].price << "\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void runTask1() {
    cout << "\n=== TASK 1: BOOKSTORE ===\n";
    addBook("1984", "Fiction", 250.0, 95, 2020);
    addBook("Dune", "Sci-Fi", 400.0, 99, 2021);
    addBook("Harry_Potter", "Fantasy", 300.0, 100, 2019, true);
    addBook("Neuromancer", "Sci-Fi", 350.0, 80, 2015);

    cout << "Before removing sold books: " << store.size() << " books.\n";
    removeSoldBooks();
    cout << "After removing sold books: " << store.size() << " books.\n";

    sortBooks(1);
    filterBooks("Sci-Fi", 300.0, 500.0);
    searchBook("1984");
    cout << "=========================\n";
}

struct Car {
    string name;
    int year;
    double mileage;
};

list<Car> carList;

void printCars() {
    if (carList.empty()) {
        cout << "Список порожній!\n";
        return;
    }
    for (auto it = carList.begin(); it != carList.end(); ++it) {
        cout << "Авто: " << it->name << " | Рік: " << it->year << " | Пробіг: " << it->mileage << " км\n";
    }
}

void runTask2() {
    int choice = 0;
    while (true) {
        cout << "\nМЕНЮ ДЛЯ РОБОТИ ЗI СПИСКОМ\n";
        cout << "1. Ввод першого елемента в список\n";
        cout << "2. Вставка елемента в початок списка\n";
        cout << "3. Вставка елемента в кінець списка\n";
        cout << "4. Вставка елемента після заданого елемента\n";
        cout << "5. Вставка елемента перед заданим елементом\n";
        cout << "6. Пошук потрібного вузла\n";
        cout << "7. Видалення вузла із вказаним значенням\n";
        cout << "8. Перегляд списку\n";
        cout << "9. Вихід\n";
        cout << "Введіть номер операції: ";
        cin >> choice;

        if (choice == 9) break;

        Car c;
        string targetName;
        int targetYear;
        bool found = false;

        switch (choice) {
            case 1:
            case 2:
            case 3:
                cout << "Назва авто: "; cin >> c.name;
                cout << "Рік випуску: "; cin >> c.year;
                cout << "Пробіг (км): "; cin >> c.mileage;
                
                if (choice == 1) {
                    carList.clear();
                    carList.push_back(c);
                } else if (choice == 2) {
                    carList.push_front(c);
                } else {
                    carList.push_back(c);
                }
                break;

            case 4:
            case 5:
                cout << "Після/Перед яким авто вставити (введіть назву): ";
                cin >> targetName;
                cout << "Дані нового авто (Назва, Рік, Пробіг):\n";
                cin >> c.name >> c.year >> c.mileage;
                
                for (auto it = carList.begin(); it != carList.end(); ++it) {
                    if (it->name == targetName) {
                        if (choice == 4) {
                            it++; 
                            carList.insert(it, c);
                        } else {
                            carList.insert(it, c);
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Авто з такою назвою не знайдено.\n";
                break;

            case 6:
                cout << "Введіть назву авто для пошуку: ";
                cin >> targetName;
                for (auto it = carList.begin(); it != carList.end(); ++it) {
                    if (it->name == targetName) found = true;
                }
                if (found) cout << "Автомобіль з назвою " << targetName << " є в списку\n";
                else cout << "Автомобіля з назвою " << targetName << " нема в списку\n";
                break;

            case 7:
                cout << "Видалити всі авто старіші за (введіть рік): ";
                cin >> targetYear;
                for (auto it = carList.begin(); it != carList.end(); ) {
                    if (it->year < targetYear) {
                        it = carList.erase(it);
                    } else {
                        ++it;
                    }
                }
                cout << "Видалення завершено.\n";
                break;

            case 8:
                printCars();
                break;

            default:
                cout << "Невірний вибір!\n";
        }
    }
}

struct Order {
    int id;
    string client;
    string address;
    double cost;
    int priority;
    int time;
    string status; 
};

deque<Order> orders;

void addOrder(int id, string cl, string addr, double c, int p, int t, string s) {
    Order ord = {id, cl, addr, c, p, t, s};
    if (p == 1) {
        orders.push_front(ord);
    } else {
        orders.push_back(ord);
    }
}

void cleanOrders() {
    deque<Order> temp;
    for (size_t i = 0; i < orders.size(); i++) {
        if (orders[i].status != "Done" && orders[i].status != "Cancelled") {
            temp.push_back(orders[i]);
        }
    }
    orders = temp;
}

void searchOrder(int id) {
    for (size_t i = 0; i < orders.size(); i++) {
        if (orders[i].id == id) {
            cout << "Found Order ID " << id << " for client " << orders[i].client << "\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

void editOrderStatus(int id, string newStatus) {
    for (size_t i = 0; i < orders.size(); i++) {
        if (orders[i].id == id) {
            orders[i].status = newStatus;
            cout << "Order " << id << " status updated to " << newStatus << "\n";
            return;
        }
    }
}

bool compareByCost(const Order& a, const Order& b) {
    return a.cost < b.cost;
}

void sortOrdersByCost() {
    sort(orders.begin(), orders.end(), compareByCost);
}

void runTask3() {
    cout << "\n=== TASK 3: DELIVERY SERVICE ===\n";
    addOrder(1, "Shevchenko", "Kyiv", 500.0, 0, 1000, "Active");
    addOrder(2, "Franko", "Lviv", 1200.0, 1, 1100, "Active");
    addOrder(3, "Ukrainka", "Odesa", 300.0, 0, 1200, "Done");
    
    cout << "First order in queue client: " << orders.front().client << " (Should be urgent)\n";
    
    cleanOrders();
    cout << "Queue size after cleaning 'Done' orders: " << orders.size() << "\n";
    
    editOrderStatus(1, "Cancelled");
    cleanOrders();
    
    sortOrdersByCost();
    cout << "Remaining orders sorted by cost:\n";
    for (size_t i = 0; i < orders.size(); i++) {
        cout << "ID: " << orders[i].id << " | Cost: " << orders[i].cost << "\n";
    }
    cout << "================================\n";
}

int main() {
    int mainChoice = 0;
    while (true) {
        cout << "\n--- ГОЛОВНЕ МЕНЮ ЛАБОРАТОРНОЇ ---\n";
        cout << "1. Завдання 1 (Книжковий магазин - vector)\n";
        cout << "2. Завдання 2 (Список автомобілів - list)\n";
        cout << "3. Завдання 3 (Служба доставки - deque)\n";
        cout << "0. Вихід\n";
        cout << "Оберіть завдання: ";
        cin >> mainChoice;

        if (mainChoice == 0) break;
        else if (mainChoice == 1) runTask1();
        else if (mainChoice == 2) runTask2();
        else if (mainChoice == 3) runTask3();
        else cout << "Невірний вибір.\n";
    }
    return 0;
}
