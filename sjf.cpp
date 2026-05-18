#include <iostream>
#include <climits>

using namespace std;

int main()
{
    int n = 4;

    int at[] = {0,1,2,3};
    int bt[] = {5,3,8,6};

    int rt[4];
    int ft[4], tat[4], wt[4];

    for(int i = 0; i < n; i++)
        rt[i] = bt[i];

    int completed = 0, time = 0, shortest;

    while(completed != n)
    {
        shortest = -1;
        int min_bt = INT_MAX;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0 && rt[i] < min_bt)
            {
                min_bt = rt[i];
                shortest = i;
            }
        }

        if(shortest == -1)
        {
            time++;
            continue;
        }

        rt[shortest]--;
        time++;

        if(rt[shortest] == 0)
        {
            completed++;

            ft[shortest] = time;

            tat[shortest] = ft[shortest] - at[shortest];

            wt[shortest] = tat[shortest] - bt[shortest];
        }
    }

    cout << "Process\tFT\tTAT\tWT\n";

    for(int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t"
             << ft[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << endl;
    }

    return 0;
}