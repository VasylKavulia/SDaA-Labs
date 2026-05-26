#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <list>
#include <queue>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

void createMockFiles() {
    ofstream f1("numbers.txt");
    for (int i = 0; i < 1000; i++) {
        f1 << (rand() % 300 - 100) << " ";
    }
    f1.close();

    ofstream f2("names.txt");
    f2 << "Anna Ivan Oleg Maria Igor Olena Anton Yulia Max Alina " << endl;
    f2.close();
}

int countUniqueListElements(list<int> l) {
    l.sort();
    l.unique();
    return l.size();
}

struct Ticket {
    int priority_value;
    string category;
    string text;

    bool operator<(const Ticket& other) const {
        return priority_value < other.priority_value;
    }
};

bool startsWithVowel(const string& s) {
    if (s.empty()) return false;
    char c = tolower(s[0]);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int main() {
    srand(time(NULL));
    createMockFiles();

    // --- TASK 1 ---
    cout << "--- Task 1 ---\n";
    int n;
    cout << "Enter how many numbers to read from file (max 1000): ";
    cin >> n;
    if (n < 1 || n > 1000) n = 100;

    vector<int> v(n);
    ifstream fin1("numbers.txt");
    for (int i = 0; i < n; i++) {
        fin1 >> v[i];
    }
    fin1.close();

    int partSize = v.size() / 3;
    sort(v.begin(), v.begin() + partSize, greater<int>());
    sort(v.begin() + 2 * partSize, v.end());

    auto it = unique(v.begin(), v.end());
    v.erase(it, v.end());

    auto bound = partition(v.begin(), v.end(), [](int x) { return x > 10; });

    transform(v.begin(), bound, v.begin(), [](int x) { return x + 100; });

    if (!v.empty()) {
        auto minmax = minmax_element(v.begin(), v.end());
        int current_min = *minmax.first;
        int current_max = *minmax.second;

        replace_if(v.begin(), v.end(), [](int x) { return x > 100; }, current_max);
        replace_if(v.begin(), v.end(), [](int x) { return x < 100; }, current_min);
    }

    auto rem = remove_if(v.begin(), v.end(), [](int x) { return x >= -5 && x <= 5; });
    v.erase(rem, v.end());

    cout << "Task 1 completed. Vector size is now: " << v.size() << "\n\n";


    // --- TASK 2 ---
    cout << "--- Task 2 ---\n";
    vector<string> names;
    ifstream fin2("names.txt");
    string temp;
    while (fin2 >> temp) {
        names.push_back(temp);
    }
    fin2.close();

    string target;
    cout << "Enter a name to count its occurrences: ";
    cin >> target;
    int occurrences = count(names.begin(), names.end(), target);
    cout << target << " found " << occurrences << " times.\n";

    for (string& str : names) {
        transform(str.begin(), str.end(), str.begin(), ::toupper);
    }
    for (string& str : names) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    stable_partition(names.begin(), names.end(), startsWithVowel);

    cout << "Organized names: ";
    for (const string& str : names) {
        cout << str << " ";
    }
    cout << "\n\n";


    // --- TASK 3 & 4 ---
    cout << "--- Task 3 & 4 ---\n";
    list<int> l1;
    cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; i++) {
        int val;
        cin >> val;
        l1.push_back(val);
    }

    cout << "List 1 elements: ";
    for (list<int>::iterator lit = l1.begin(); lit != l1.end(); ++lit) {
        cout << *lit << " ";
    }
    cout << "\n";

    list<int> l2;
    for (int i = 0; i < 10; i++) {
        l2.push_back(rand() % 50 + 1);
    }
    l2.sort();

    l1.sort(greater<int>());
    l2.sort(greater<int>());
    l1.merge(l2, greater<int>());

    cout << "Unique elements in merged list: " << countUniqueListElements(l1) << "\n\n";


    // --- TASK 5 ---
    cout << "--- Task 5 ---\n";
    priority_queue<Ticket> pq;
    pq.push({ 3, "High", "Critical error on startup" });
    pq.push({ 1, "Low", "Update profile picture" });
    pq.push({ 2, "Medium", "Fix typos on main page" });
    pq.push({ 3, "High", "Database connection lost" });

    while (!pq.empty()) {
        Ticket t = pq.top();
        pq.pop();
        cout << "[" << t.category << " Priority] " << t.text << "\n";
    }

    return 0;
}