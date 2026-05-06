#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

struct Node1 {
    int height;
    char name[50];
    Node1* left;
    Node1* right;
};

struct Node2 {
    int height;
    Node2* left;
    Node2* right;
};

void insert1(Node1*& root, int h, const char* n) {
    if (!root) {
        root = new Node1;
        root->height = h;
        strcpy(root->name, n);
        root->left = nullptr;
        root->right = nullptr;
        return;
    }
    if (h < root->height) {
        insert1(root->left, h, n);
    }
    else {
        insert1(root->right, h, n);
    }
}

void insert2(Node2*& root, int h) {
    if (!root) {
        root = new Node2;
        root->height = h;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }
    if (h < root->height) {
        insert2(root->left, h);
    }
    else {
        insert2(root->right, h);
    }
}

void countNames(Node1* root, const char* target, int& count) {
    if (!root) return;
    if (strcmp(root->name, target) == 0) {
        count++;
    }
    countNames(root->left, target, count);
    countNames(root->right, target, count);
}

void traverseAndInsert(Node1* node, Node2*& newRoot) {
    if (!node) return;
    insert2(newRoot, node->height);
    traverseAndInsert(node->left, newRoot);
    traverseAndInsert(node->right, newRoot);
}

int countNodes1(Node1* root) {
    if (!root) return 0;
    return 1 + countNodes1(root->left) + countNodes1(root->right);
}

int countNodes2(Node2* root) {
    if (!root) return 0;
    return 1 + countNodes2(root->left) + countNodes2(root->right);
}

int getDepth1(Node1* root) {
    if (!root) return 0;
    int leftDepth = getDepth1(root->left);
    int rightDepth = getDepth1(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

int getDepth2(Node2* root) {
    if (!root) return 0;
    int leftDepth = getDepth2(root->left);
    int rightDepth = getDepth2(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

void printInOrder1(Node1* root) {
    if (!root) return;
    printInOrder1(root->left);
    cout << "[" << root->height << " cm, " << root->name << "] ";
    printInOrder1(root->right);
}

void printInOrder2(Node2* root) {
    if (!root) return;
    printInOrder2(root->left);
    cout << root->height << " ";
    printInOrder2(root->right);
}

void freeTree1(Node1*& root) {
    if (!root) return;
    freeTree1(root->left);
    freeTree1(root->right);
    delete root;
    root = nullptr;
}

void freeTree2(Node2*& root) {
    if (!root) return;
    freeTree2(root->left);
    freeTree2(root->right);
    delete root;
    root = nullptr;
}

int main() {
    srand(time(0));

    Node1* originalTree = nullptr;
    int n = 15;

    const char* namesPool[] = { "Ivan", "Maria", "Misha", "Anna", "Roma", "Sophia", "Andrey", "Nastya" };
    int poolSize = 8;

    cout << "--- Initializing original tree ---\n";
    cout << "Target number of nodes: " << n << "\n";

    for (int i = 0; i < n; i++) {
        int h = 150 + rand() % 50;
        const char* randomName = namesPool[rand() % poolSize];
        insert1(originalTree, h, randomName);
    }

    cout << "\nOriginal tree: \n";
    printInOrder1(originalTree);
    cout << "\n";

    const char* searchName = "Anna";
    int nameCount = 0;
    countNames(originalTree, searchName, nameCount);

    cout << "\n--- Name search ---\n";
    cout << "Name '" << searchName << "' appears " << nameCount << " time in the tree.\n";

    Node2* leftSubTree = nullptr;
    if (originalTree && originalTree->left) {
        traverseAndInsert(originalTree->left, leftSubTree);
    }

    cout << "\n--- Creating new tree from left subtree ---\n";
    cout << "New tree: \n";
    if (leftSubTree) {
        printInOrder2(leftSubTree);
        cout << "\n";
    }
    else {
        cout << "Left subtree is empty.\n";
    }

    cout << "\n--- Tree statistics ---\n";
    cout << "Original tree - Nodes: " << countNodes1(originalTree) << ", Depth: " << getDepth1(originalTree) << "\n";
    cout << "New tree      - Nodes: " << countNodes2(leftSubTree) << ", Depth: " << getDepth2(leftSubTree) << "\n";

    freeTree1(originalTree);
    freeTree2(leftSubTree);

    cout << "\nMemory successfully freed.\n";

    return 0;
}