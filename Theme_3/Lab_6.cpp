#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>

using namespace std;

struct FloatNode {
    float data;
    FloatNode* next;
};

void pushF(FloatNode*& top, float val) {
    FloatNode* node = new FloatNode;
    node->data = val;
    node->next = top;
    top = node;
}

float popF(FloatNode*& top) {
    float val = top->data;
    FloatNode* temp = top;
    top = top->next;
    delete temp;
    return val;
}

bool isEmptyF(FloatNode* top) {
    return top == nullptr;
}

void task1() {
    cout << "--- TASK 1 ---\n";
    FloatNode* originalStack = nullptr;
    FloatNode* newStack = nullptr;

    for (int i = 0; i < 10; i++) {
        float val = (rand() % 1701) / 100.0f - 6.0f;
        pushF(originalStack, val);
    }

    float threshold = 2.0f;
    cout << "Threshold value: " << threshold << "\n";

    while (!isEmptyF(originalStack)) {
        float val = popF(originalStack);
        if (val >= threshold) {
            pushF(newStack, val);
        }
    }

    float sum = 0;
    int count = 0;
    FloatNode* tempStack = nullptr;

    cout << "New stack elements: ";
    while (!isEmptyF(newStack)) {
        float val = popF(newStack);
        cout << fixed << setprecision(2) << val << " ";
        sum += val;
        count++;
        pushF(tempStack, val);
    }
    cout << "\n";

    if (count > 0) {
        cout << "Arithmetic mean: " << fixed << setprecision(4) << sum / count << "\n";
    }
    else {
        cout << "New stack is empty.\n";
    }

    while (!isEmptyF(tempStack)) popF(tempStack);
    cout << "\n";
}

struct MusicRecord {
    char medium[30];
    char title[50];
    char artist[50];
    float duration;
    int tracks;
    float price;
};

struct MusicNode {
    MusicRecord data;
    MusicNode* next;
};

void pushM(MusicNode*& top, MusicRecord rec) {
    MusicNode* node = new MusicNode;
    node->data = rec;
    node->next = top;
    top = node;
}

MusicRecord popM(MusicNode*& top) {
    MusicRecord rec = top->data;
    MusicNode* temp = top;
    top = top->next;
    delete temp;
    return rec;
}

bool isEmptyM(MusicNode* top) {
    return top == nullptr;
}

void task2() {
    cout << "--- TASK 2 ---\n";
    MusicNode* stack = nullptr;

    MusicRecord r1 = { "Vinyl", "The Dark Side", "Pink Floyd", 42.5f, 10, 35.0f };
    MusicRecord r2 = { "Audiocassette", "Thriller", "Michael Jackson", 42.1f, 9, 15.0f };
    MusicRecord r3 = { "CD", "Bad", "Michael Jackson", 48.0f, 11, 20.0f };
    MusicRecord r4 = { "Audiocassette", "Nevermind", "Nirvana", 42.3f, 12, 12.0f };

    pushM(stack, r1);
    pushM(stack, r2);
    pushM(stack, r3);
    pushM(stack, r4);

    const char* targetArtist = "Michael Jackson";
    float totalArtistDuration = 0;

    MusicNode* cassetteStack = nullptr;

    while (!isEmptyM(stack)) {
        MusicRecord rec = popM(stack);

        if (strcmp(rec.artist, targetArtist) == 0) {
            totalArtistDuration += rec.duration;
        }

        if (strcmp(rec.medium, "Audiocassette") == 0) {
            pushM(cassetteStack, rec);
        }
    }

    cout << "Total duration for " << targetArtist << ": " << totalArtistDuration << " mins\n";

    float totalPrice = 0;
    int count = 0;

    while (!isEmptyM(cassetteStack)) {
        MusicRecord rec = popM(cassetteStack);
        totalPrice += rec.price;
        count++;
    }

    if (count > 0) {
        cout << "Average price of audiocassettes: " << totalPrice / count << " USD\n";
    }
    else {
        cout << "No audiocassettes found.\n";
    }
    cout << "\n";
}

struct IntNode {
    int data;
    IntNode* next;
};

struct IntQueue {
    IntNode* front = nullptr;
    IntNode* rear = nullptr;
};

void enqueueI(IntQueue& q, int val) {
    IntNode* node = new IntNode;
    node->data = val;
    node->next = nullptr;
    if (!q.rear) {
        q.front = q.rear = node;
    }
    else {
        q.rear->next = node;
        q.rear = node;
    }
}

int dequeueI(IntQueue& q) {
    int val = q.front->data;
    IntNode* temp = q.front;
    q.front = q.front->next;
    if (!q.front) q.rear = nullptr;
    delete temp;
    return val;
}

bool isEmptyI(IntQueue& q) {
    return q.front == nullptr;
}

void task3() {
    cout << "--- TASK 3 ---\n";
    IntQueue initialQ, newQ;

    for (int i = 0; i < 7; i++) {
        enqueueI(initialQ, rand() % 50 + 1);
    }

    cout << "Processing queue\n";
    while (!isEmptyI(initialQ)) {
        int val = dequeueI(initialQ);
        if (val % 2 == 0) {
            enqueueI(newQ, val);
            enqueueI(newQ, 100);
        }
    }

    double product = 1.0;
    int count = 0;

    cout << "New queue elements: ";
    IntQueue tempQ;
    while (!isEmptyI(newQ)) {
        int val = dequeueI(newQ);
        cout << val << " ";
        product *= val;
        count++;
        enqueueI(tempQ, val);
    }
    cout << "\n";

    if (count > 0) {
        cout << "Geometric mean: " << fixed << setprecision(4) << pow(product, 1.0 / count) << "\n";
    }

    while (!isEmptyI(tempQ)) {
        dequeueI(tempQ);
    }

    cout << "Memory freed.\n\n";
}

struct Team {
    char name[50];
    char city[50];
    int points;
};

struct TeamNode {
    Team data;
    TeamNode* next;
};

struct TeamQueue {
    TeamNode* front = nullptr;
    TeamNode* rear = nullptr;
};

void enqueueT(TeamQueue& q, Team t) {
    TeamNode* node = new TeamNode;
    node->data = t;
    node->next = nullptr;
    if (!q.rear) {
        q.front = q.rear = node;
    }
    else {
        q.rear->next = node;
        q.rear = node;
    }
}

Team dequeueT(TeamQueue& q) {
    Team t = q.front->data;
    TeamNode* temp = q.front;
    q.front = q.front->next;
    if (!q.front) q.rear = nullptr;
    delete temp;
    return t;
}

bool isEmptyT(TeamQueue& q) {
    return q.front == nullptr;
}

void task4() {
    cout << "--- TASK 4 ---\n";
    TeamQueue q;

    Team t1 = { "Lokomotyv", "Kyiv", 45 };
    Team t2 = { "Barkom-Kazhany", "Lviv", 30 };
    Team t3 = { "VC Kyiv", "Kyiv", 50 };
    Team t4 = { "VC Odesa", "Odesa", 20 };
    Team t5 = { "VC Lviv", "Lviv", 40 };

    enqueueT(q, t1);
    enqueueT(q, t2);
    enqueueT(q, t3);
    enqueueT(q, t4);
    enqueueT(q, t5);

    TeamQueue tempQ;
    TeamQueue uniqueCityQ;
    TeamQueue highPointsQ;

    Team leader = { "", "", -1 };
    Team outsider = { "", "", 9999 };

    char seenCities[10][50];
    int seenCount = 0;
    int targetPoints = 35;

    while (!isEmptyT(q)) {
        Team t = dequeueT(q);

        if (t.points > leader.points) leader = t;
        if (t.points < outsider.points) outsider = t;

        bool citySeen = false;
        for (int i = 0; i < seenCount; i++) {
            if (strcmp(seenCities[i], t.city) == 0) {
                citySeen = true;
                break;
            }
        }

        if (!citySeen) {
            strcpy(seenCities[seenCount++], t.city);
            enqueueT(uniqueCityQ, t);
        }

        if (t.points > targetPoints) {
            enqueueT(highPointsQ, t);
        }

        enqueueT(tempQ, t);
    }

    while (!isEmptyT(tempQ)) {
        enqueueT(q, dequeueT(tempQ));
    }

    cout << "Leader: " << leader.name << " (" << leader.points << " pts)\n";
    cout << "Outsider: " << outsider.name << " (" << outsider.points << " pts)\n";

    cout << "\nTeams from unique cities:\n";
    while (!isEmptyT(uniqueCityQ)) {
        Team t = dequeueT(uniqueCityQ);
        cout << "- " << t.name << " (" << t.city << ")\n";
    }

    cout << "\nTeams with > " << targetPoints << " points:\n";
    while (!isEmptyT(highPointsQ)) {
        Team t = dequeueT(highPointsQ);
        cout << "- " << t.name << " (" << t.points << " pts)\n";
    }

    while (!isEmptyT(q)) dequeueT(q);
}

int main() {
    srand(time(0));

    task1();
    task2();
    task3();
    task4();

    return 0;
}