#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    double coeff = 7 * 1.0 + 10 * 1.2 + 10 * 1.6 + 1.0 * 1.8 + 3 * 2.0 + 1.0 * 2.4 + 1.0 * 2.6 + 1.0 * 3.0;
    int s = 380000 / coeff;

    cout << "Task 1\n";
    cout << "Orderly: " << s << "\n";
    cout << "Nurse: " << s * 6 / 5 << "\n";
    cout << "Doctor: " << s * 8 / 5 << "\n";
    cout << "Pharm Head: " << s * 9 / 5 << "\n";
    cout << "Dept Head: " << s * 2 << "\n";
    cout << "Chief Doc: " << s * 12 / 5 << "\n";
    cout << "Supply Head: " << s * 13 / 5 << "\n";
    cout << "Hosp Head: " << s * 3 << "\n";
    cout << "Total: " << (int)(s * coeff) << "\n\n";

    cout << "Task 2\n";
    int s_nw[] = { 1500, 1900, 1600 };
    int d_nw[] = { 1800, 1200, 2000 };
    int c[3][3] = {
        {7, 8, 2},
        {1, 4, 3},
        {1, 5, 6}
    };

    int r_nw[3][3] = { 0 };
    int cost_nw = 0;
    int i = 0, j = 0;

    while (i < 3 && j < 3) {
        int take = min(s_nw[i], d_nw[j]);
        r_nw[i][j] = take;
        cost_nw += take * c[i][j];
        s_nw[i] -= take;
        d_nw[j] -= take;
        if (s_nw[i] == 0) i++;
        if (d_nw[j] == 0) j++;
    }

    cout << "North-West Corner Method:\n";
    cout << "|    |   M1 |   M2 |   M3 |\n";
    cout << "|----|------|------|------|\n";
    for (int r = 0; r < 3; r++) {
        cout << "| S" << r + 1 << " |";
        for (int col = 0; col < 3; col++) {
            cout << " " << setw(4) << r_nw[r][col] << " |";
        }
        cout << "\n";
    }
    cout << "Cost: " << cost_nw << "\n\n";

    int s_mc[] = { 1500, 1900, 1600 };
    int d_mc[] = { 1800, 1200, 2000 };
    int r_mc[3][3] = { 0 };
    int cost_mc = 0;

    while (true) {
        int min_c = 10000;
        int min_i = -1, min_j = -1;
        for (int r = 0; r < 3; r++) {
            for (int col = 0; col < 3; col++) {
                if (s_mc[r] > 0 && d_mc[col] > 0 && c[r][col] < min_c) {
                    min_c = c[r][col];
                    min_i = r;
                    min_j = col;
                }
            }
        }
        if (min_i == -1) break;

        int take = min(s_mc[min_i], d_mc[min_j]);
        r_mc[min_i][min_j] = take;
        cost_mc += take * c[min_i][min_j];
        s_mc[min_i] -= take;
        d_mc[min_j] -= take;
    }

    cout << "Minimum Cost Method:\n";
    cout << "|    |   M1 |   M2 |   M3 |\n";
    cout << "|----|------|------|------|\n";
    for (int r = 0; r < 3; r++) {
        cout << "| S" << r + 1 << " |";
        for (int col = 0; col < 3; col++) {
            cout << " " << setw(4) << r_mc[r][col] << " |";
        }
        cout << "\n";
    }
    cout << "Cost: " << cost_mc << "\n";

    return 0;
}