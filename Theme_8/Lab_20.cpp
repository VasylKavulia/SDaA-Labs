#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Activity {
    int id;
    int start;
    int end;
};

bool compare(Activity a, Activity b) {
    return a.end < b.end;
}

int main() {
    int best_m = 0, best_f = 0, best_mi = 0, best_s = 0;
    int max_cal = -1;

    for (int s = 0; s <= 35; s++) {
        for (int mi = 0; mi <= 35; mi++) {
            for (int f = 0; f <= 35; f++) {
                for (int m = 0; m <= 35; m++) {
                    if (m >= 2 * f && f >= mi && mi >= 8 * s) {
                        double vol = m * 1.0 + f * 1.5 + mi * 2.0 + s * 1.0;
                        int mass = m + f + mi + s;

                        if (vol <= 45.0 && mass <= 35) {
                            int cal = m * 1500 + f * 5000 + mi * 5000 + s * 4000;
                            if (cal > max_cal) {
                                max_cal = cal;
                                best_m = m;
                                best_f = f;
                                best_mi = mi;
                                best_s = s;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "Task 1\n";
    cout << "Meat: " << best_m << "\n";
    cout << "Flour: " << best_f << "\n";
    cout << "Milk: " << best_mi << "\n";
    cout << "Sugar: " << best_s << "\n";
    cout << "Calories: " << max_cal << "\n\n";

    cout << "Task 2\n";
    cout << "Enter number of activities: ";
    int n;
    if (!(cin >> n)) return 0;

    cout << "Enter start and end times:\n";
    vector<Activity> a(n);
    for (int i = 0; i < n; i++) {
        a[i].id = i + 1;
        cin >> a[i].start >> a[i].end;
    }

    sort(a.begin(), a.end(), compare);

    vector<Activity> res;
    if (n > 0) {
        res.push_back(a[0]);
        int last = a[0].end;
        for (int i = 1; i < n; i++) {
            if (a[i].start >= last) {
                res.push_back(a[i]);
                last = a[i].end;
            }
        }
    }

    cout << "Selected count: " << res.size() << "\n";
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i].start << " " << res[i].end << "\n";
    }

    return 0;
}