#include <iostream>
#include <string>

using namespace std;

struct Product {
    string name;
    double price;
    double nutrients[3];
    double calories;
};

void printArray(Product arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Name: " << arr[i].name << " | Price: " << arr[i].price 
             << " | Calories: " << arr[i].calories << endl;
    }
    cout << "---------------------------------" << endl;
}

int main() {
    const int n = 5;
    Product products[n] = {
        {"Apple", 1.5, {0.3, 0.2, 13.8}, 0},
        {"Bread", 2.0, {9.0, 3.2, 49.0}, 0},
        {"Milk", 1.2, {3.3, 3.6, 4.8}, 0},
        {"Cheese", 5.5, {25.0, 33.0, 1.3}, 0},
        {"Chicken", 7.0, {27.0, 14.0, 0.0}, 0}
    };

    for (int i = 0; i < n; i++) {
        products[i].calories = 4 * products[i].nutrients[0] + 
                               9 * products[i].nutrients[1] + 
                               4 * products[i].nutrients[2];
    }

    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (products[j].calories > products[max_idx].calories) {
                max_idx = j;
            }
        }
        Product temp = products[i];
        products[i] = products[max_idx];
        products[max_idx] = temp;
    }

    cout << "Sorted by calories:" << endl;
    printArray(products, n);

    Product products_copy[n];
    for (int i = 0; i < n; i++) {
        products_copy[i] = products[i];
    }

    int index = 0;
    while (index < n) {
        if (index == 0) {
            index++;
        }
        if (products_copy[index].price >= products_copy[index - 1].price) {
            index++;
        } else {
            Product temp = products_copy[index];
            products_copy[index] = products_copy[index - 1];
            products_copy[index - 1] = temp;
            index--;
        }
    }

    cout << "Sorted by price:" << endl;
    printArray(products_copy, n);

    double search_price;
    cout << "Enter price to search: ";
    cin >> search_price;

    bool found = false;
    cout << "Search results:" << endl;
    for (int i = 0; i < n; i++) {
        if (products[i].price == search_price) {
            cout << "Name: " << products[i].name << " | Price: " << products[i].price 
                 << " | Calories: " << products[i].calories << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Products not found." << endl;
    }

    return 0;
}