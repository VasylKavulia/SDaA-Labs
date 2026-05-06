#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>

using namespace std;

struct Node1 {
    int data;
    Node1* left;
    Node1* right;
};

bool insert1(Node1*& root, int val) {
    if (!root) {
        root = new Node1;
        root->data = val;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    if (val == root->data) {
        return false;
    }
    if (val < root->data) {
        return insert1(root->left, val);
    }
    else {
        return insert1(root->right, val);
    }
}

int getDepth1(Node1* root) {
    if (!root) return 0;
    int leftDepth = getDepth1(root->left);
    int rightDepth = getDepth1(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

void splitTree1(Node1* root, Node1*& evenRoot, Node1*& oddRoot) {
    if (!root) return;
    if (root->data % 2 == 0) {
        insert1(evenRoot, root->data);
    }
    else {
        insert1(oddRoot, root->data);
    }
    splitTree1(root->left, evenRoot, oddRoot);
    splitTree1(root->right, evenRoot, oddRoot);
}

void freeTree1(Node1*& root) {
    if (!root) return;
    freeTree1(root->left);
    freeTree1(root->right);
    delete root;
    root = nullptr;
}

void printInOrder1(Node1* root) {
    if (!root) return;
    printInOrder1(root->left);
    cout << root->data << " ";
    printInOrder1(root->right);
}

void task1() {
    cout << "--- TASK 1 ---\n";
    Node1* root = nullptr;
    int n, choice;

    n = 10;
    choice = 2;

    cout << "Number of nodes: " << n << "\n";
    cout << "Input method (1 - manual, 2 - random): " << choice << "\n";

    if (choice == 2) {
        int a = 1, b = 20;
        cout << "Range [a, b]: [" << a << ", " << b << "]\n";

        if (n <= (b - a)) {
            int count = 0;
            while (count < n) {
                int val = a + rand() % (b - a + 1);
                if (insert1(root, val)) {
                    count++;
                }
            }
        }
        else {
            cout << "Invalid bounds. 'n' must be <= 'b - a'\n";
            return;
        }
    }

    cout << "Оriginal Tree: ";
    printInOrder1(root);
    cout << "\n";

    Node1* evenRoot = nullptr;
    Node1* oddRoot = nullptr;

    splitTree1(root, evenRoot, oddRoot);

    cout << "Depth of Original Tree: " << getDepth1(root) << "\n";
    cout << "Depth of Even Tree: " << getDepth1(evenRoot) << "\n";
    cout << "Depth of Odd Tree: " << getDepth1(oddRoot) << "\n";

    freeTree1(root);
    freeTree1(evenRoot);
    freeTree1(oddRoot);
    cout << "Memory freed for Task 1.\n\n";
}

struct Tech {
    int code;
    char name[50];
    float price;
};

struct Node2 {
    Tech data;
    Node2* left;
    Node2* right;
};

void insert2(Node2*& root, Tech t) {
    if (!root) {
        root = new Node2;
        root->data = t;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }
    if (t.code < root->data.code) {
        insert2(root->left, t);
    }
    else if (t.code > root->data.code) {
        insert2(root->right, t);
    }
}

void calcAvgPrice(Node2* root, float& sum, int& count) {
    if (!root) return;
    calcAvgPrice(root->left, sum, count);
    sum += root->data.price;
    count++;
    calcAvgPrice(root->right, sum, count);
}

int getDepth2(Node2* root) {
    if (!root) return 0;
    int leftDepth = getDepth2(root->left);
    int rightDepth = getDepth2(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

void countNodesPerLevel(Node2* root, int currentLevel, int* counts) {
    if (!root) return;
    counts[currentLevel]++;
    countNodesPerLevel(root->left, currentLevel + 1, counts);
    countNodesPerLevel(root->right, currentLevel + 1, counts);
}

Node2* findNode(Node2* root, int code) {
    if (!root) return nullptr;
    if (root->data.code == code) return root;
    if (code < root->data.code) return findNode(root->left, code);
    return findNode(root->right, code);
}

void freeTree2(Node2*& root) {
    if (!root) return;
    freeTree2(root->left);
    freeTree2(root->right);
    delete root;
    root = nullptr;
}

void task2() {
    cout << "--- TASK 2 ---\n";

    ofstream outfile("equipment.txt");
    outfile << "105 Laptop_Dell 850.50\n";
    outfile << "102 Mouse_Logitech 25.00\n";
    outfile << "108 Monitor_LG 200.00\n";
    outfile << "101 Keyboard_Razer 75.00\n";
    outfile << "109 Printer_HP 150.00\n";
    outfile.close();

    Node2* root = nullptr;
    ifstream infile("equipment.txt");
    if (!infile.is_open()) {
        cout << "Could not open file.\n";
        return;
    }

    Tech temp;
    while (infile >> temp.code >> temp.name >> temp.price) {
        insert2(root, temp);
    }
    infile.close();

    float sumPrice = 0;
    int count = 0;
    calcAvgPrice(root, sumPrice, count);

    if (count > 0) {
        cout << "Average price: " << fixed << setprecision(2) << sumPrice / count << " USD\n";
    }

    int depth = getDepth2(root);
    int* levelCounts = new int[depth];
    for (int i = 0; i < depth; i++) levelCounts[i] = 0;

    countNodesPerLevel(root, 0, levelCounts);

    cout << "Nodes per level:\n";
    for (int i = 0; i < depth; i++) {
        cout << "Level " << i << ": " << levelCounts[i] << " nodes\n";
    }
    delete[] levelCounts;

    int targetCode = 105;
    cout << "\nSearching for code " << targetCode << " to delete children\n";
    Node2* target = findNode(root, targetCode);

    if (target) {
        cout << "Node found. Deleting children\n";
        freeTree2(target->left);
        freeTree2(target->right);
    }
    else {
        cout << "Node not found.\n";
    }

    freeTree2(root);
    cout << "Memory freed for Task 2.\n";
}

int main() {
    srand(time(0));
    task1();
    task2();
    return 0;
}