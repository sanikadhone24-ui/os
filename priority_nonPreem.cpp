#include <iostream>
using namespace std;

int main()
{
    int n = 4;

    int at[] = {0,1,2,3};
    int bt[] = {5,3,8,6};
    int pr[] = {1,2,1,3};

    int ft[4], tat[4], wt[4];
    int completed[4] = {0};

    int time = 0, count = 0;

    while(count < n)
    {
        int highest = -1;
        int minPriority = 999;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && completed[i] == 0)
            {
                if(pr[i] < minPriority)
                {
                    minPriority = pr[i];
                    highest = i;
                }
            }
        }

        time += bt[highest];
        ft[highest] = time;

        completed[highest] = 1;
        count++;
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