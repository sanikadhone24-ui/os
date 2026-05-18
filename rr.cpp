#include <iostream>
using namespace std;

int main()
{
    int n = 4, tq = 2;

    int at[] = {0,1,2,3};
    int bt[] = {5,3,8,6};

    int rt[4];
    int ft[4], tat[4], wt[4];

    for(int i=0;i<n;i++)
        rt[i] = bt[i];

    int time = 0;

    while(true)
    {
        bool done = true;

        for(int i=0;i<n;i++)
        {
            if(rt[i] > 0)
            {
                done = false;

                if(rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
                }
                else
                {
                    time += rt[i];
                    ft[i] = time;
                    rt[i] = 0;
                }
            }
        }

        if(done == true)
            break;
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