#include <iostream>
#include <iomanip>

using namespace std;

bool checkHamiltonian(int v, bool visited[], int count, int n, int adj[][6]) {
    if (count == n) return true;
    visited[v] = true;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] > 0 && !visited[i]) {
            if (checkHamiltonian(i, visited, count + 1, n, adj)) return true;
        }
    }
    visited[v] = false;
    return false;
}

int main() {
    int n = 6;
    int adj[6][6] = { 0 };

    adj[0][2] = 2; adj[2][0] = 2;
    adj[0][4] = 8; adj[4][0] = 8;
    adj[1][2] = 6; adj[2][1] = 6;
    adj[1][3] = 4; adj[3][1] = 4;
    adj[2][5] = 9; adj[5][2] = 9;
    adj[3][4] = 4; adj[4][3] = 4;

    cout << "--- TASK 1: Adjacency atrix ---\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << adj[i][j];
        }
        cout << "\n";
    }

    cout << "\n--- TASK 2: Completeness check ---\n";
    bool complete = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && adj[i][j] == 0) complete = false;
        }
    }
    if (complete) cout << "The graph is complete.\n";
    else cout << "The graph is not complete.\n";

    cout << "\n--- TASK 3: Adjacency List ---\n";
    for (int i = 0; i < n; i++) {
        cout << "City " << (i + 1) << ": ";
        for (int j = 0; j < n; j++) {
            if (adj[i][j] > 0) {
                cout << (j + 1) << "(dist: " << adj[i][j] << ") ";
            }
        }
        cout << "\n";
    }

    cout << "\n--- TASK 4: Average path length ---\n";
    int totalLen = 0;
    int edgeCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj[i][j] > 0) {
                totalLen += adj[i][j];
                edgeCount++;
            }
        }
    }
    cout << "Average length: " << fixed << setprecision(2) << (float)totalLen / edgeCount << "\n";

    cout << "\n--- TASK 5 & 6: Isolated cities (degree == 1) ---\n";
    int isoCount = 0;
    int isoList[6];
    for (int i = 0; i < n; i++) {
        int deg = 0;
        int lastNeigh = -1;
        for (int j = 0; j < n; j++) {
            if (adj[i][j] > 0) {
                deg++;
                lastNeigh = j;
            }
        }
        if (deg == 1) {
            cout << "City " << (i + 1) << " is isolated. Nearest is " << (lastNeigh + 1) << " (dist: " << adj[i][lastNeigh] << ")\n";
            isoList[isoCount] = i + 1;
            isoCount++;
        }
    }
    cout << "Total isolated cities: " << isoCount << "\n";
    if (isoCount > 0) {
        cout << "Isolated city numbers: ";
        for (int i = 0; i < isoCount; i++) cout << isoList[i] << " ";
        cout << "\n";
    }

    cout << "\n--- TASK 7: Max 3-city route ---\n";
    int maxDist = 0;
    int c1 = -1, c2 = -1, c3 = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] > 0) {
                for (int k = 0; k < n; k++) {
                    if (i != k && adj[j][k] > 0) {
                        int dist = adj[i][j] + adj[j][k];
                        if (dist > maxDist) {
                            maxDist = dist;
                            c1 = i + 1;
                            c2 = j + 1;
                            c3 = k + 1;
                        }
                    }
                }
            }
        }
    }
    cout << "(" << c1 << ") --- " << adj[c1 - 1][c2 - 1] << " --- (" << c2 << ") --- " << adj[c2 - 1][c3 - 1] << " --- (" << c3 << ")\n";

    cout << "\n--- TASK 8: Hamiltonian path check ---\n";
    bool hasPath = false;
    for (int i = 0; i < n; i++) {
        bool visited[6] = { false };
        if (checkHamiltonian(i, visited, 1, n, adj)) {
            hasPath = true;
            break;
        }
    }
    if (hasPath) cout << "possible to visit all cities exactly once.\n";
    else cout << "not possible to visit all cities exactly once.\n";

    return 0;
}