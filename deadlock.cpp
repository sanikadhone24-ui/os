// Deadlock Detection Algorithm in C++

#include <iostream>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    int Allocation[n][m], Request[n][m], Available[m];

    // Input Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> Allocation[i][j];
        }
    }

    // Input Request Matrix
    cout << "\nEnter Request Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> Request[i][j];
        }
    }

    // Input Available Resources
    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < m; i++) {
        cin >> Available[i];
    }

    bool Finish[n] = {false};
    int Work[m];

    // Initialize Work = Available
    for (int i = 0; i < m; i++) {
        Work[i] = Available[i];
    }

    bool found;

    do {
        found = false;

        for (int i = 0; i < n; i++) {

            if (!Finish[i]) {
                bool possible = true;

                // Check if Request <= Work
                for (int j = 0; j < m; j++) {
                    if (Request[i][j] > Work[j]) {
                        possible = false;
                        break;
                    }
                }

                // If possible, process can finish
                if (possible) {
                    for (int j = 0; j < m; j++) {
                        Work[j] += Allocation[i][j];
                    }

                    Finish[i] = true;
                    found = true;

                    cout << "Process P" << i << " can finish.\n";
                }
            }
        }

    } while (found);

    // Check for deadlock
    bool deadlock = false;

    cout << "\nDeadlocked Processes: ";
    for (int i = 0; i < n; i++) {
        if (!Finish[i]) {
            deadlock = true;
            cout << "P" << i << " ";
        }
    }

    if (!deadlock) {
        cout << "None";
    }

    cout << endl;

    return 0;
}