#include <iostream>
using namespace std;

int main()
{
    int n = 4;

    int at[] = {0,1,2,3};
    int bt[] = {5,3,8,6};
    int pr[] = {1,2,1,3};

    int rem_bt[4];
    int ft[4], tat[4], wt[4];

    for(int i=0;i<n;i++)
        rem_bt[i] = bt[i];

    int completed = 0, time = 0;

    while(completed < n)
    {
        int highest = -1;
        int minPriority = 999;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && rem_bt[i] > 0)
            {
                if(pr[i] < minPriority)
                {
                    minPriority = pr[i];
                    highest = i;
                }
            }
        }

        rem_bt[highest]--;
        time++;

        if(rem_bt[highest] == 0)
        {
            ft[highest] = time;
            completed++;
        }
    }

    for(int i=0;i<n;i++)
    {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    cout<<"Process\tFT\tTAT\tWT\n";

    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i<<"\t"<<ft[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
    }

    return 0;
}