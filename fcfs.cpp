#include <iostream>
using namespace std;

int main()
{
    int n = 4;

    int at[] = {0,1,2,3};
    int bt[] = {5,3,8,6};

    int ft[4], tat[4], wt[4];

    ft[0] = at[0] + bt[0];

    for(int i = 1; i < n; i++)
    {
        ft[i] = ft[i-1] + bt[i];
    }

    for(int i = 0; i < n; i++)
    {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
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