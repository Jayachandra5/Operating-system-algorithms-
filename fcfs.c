// this coerrect 
#include<stdio.h>
#include<stdlib.h>
//jsjskkssjsjhhhhggdd

void print_gantt_chart(int ct[], int n)
{
    int i, j;
    printf("\nGantt Chart:\n");
    printf("+");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < ct[i]; j++)
            printf("-");
        printf("+");
    }
    printf("\n|");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < ct[i]; j++)
            printf(" ");
        printf("|");
    }
    printf("\n");

    printf("0");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < ct[i]; j++)
            printf(" ");
        printf("%d", ct[i]);

    }
    printf("\n");
}


int main()
{
    int n, bt[30], at[30], wt[30], tat[30], ct[30], i, j;
    float avwt = 0, avtat = 0;

    printf("Enter the number of processes (maximum 30): ");
    scanf("%d", &n);

    printf("Enter the arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++)
    {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // Sort the processes based on their arrival time
    for(i = 0; i < n-1; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(at[i] > at[j])
            {
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    // Calculate completion time, waiting time, and turnaround time
    for(i = 0; i < n; i++)
    {
        if(i == 0)
        {
            ct[i] = at[i] + bt[i];
        }
        else
        {
            if(at[i] > ct[i-1])
            {
                ct[i] = at[i] + bt[i];
            }
            else
            {
                ct[i] = ct[i-1] + bt[i];
            }
        }
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avwt += wt[i];
        avtat += tat[i];
    }

    avwt /= n;
    avtat /= n;

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }
    
    printf("\n\nGantt Chart: \n\n");
    print_gantt_chart(ct,n);
    printf("\n\n");
    printf("Average Waiting Time: %.2f\n", avwt);
    printf("Average Turnaround Time: %.2f\n", avtat);

    return 0;
}


//"Welcome to First Come First Sever Scheduling!!"

/*#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20], at[20], ct[20], i, j, current_time = 0;
    float avwt = 0.0, avtat = 0.0;

    printf("Welcome to First Come First Sever Scheduling!!");


    printf("Enter total number of processes (max 20): ");
    scanf("%d", &n);

    printf("\nEnter Process Arrival Time and Burst Time\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    // sort the processes based on their arrival time
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(at[i] > at[j]) {
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    // calculate completion time and waiting time of each process
    for(i = 0; i < n; i++) {
        if(current_time < at[i]) {
            current_time = at[i];
        }
        ct[i] = current_time + bt[i];
        wt[i] = (current_time > at[i]) ? current_time - at[i] : 0;
        current_time = ct[i];
    }

    // calculate turnaround time of each process and average waiting and turnaround time
    for(i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avwt += (float)wt[i];
        avtat += (float)tat[i];
    }

    avwt /= (float)n;
    avtat /= (float)n;

    printf("\nProcess\t  Arrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avwt);
    printf("Average Turnaround Time: %.2f\n", avtat);
    
     // print Gantt chart
    printf("\nGantt Chart:\n");
    for(i=0;i<n;i++) {
        printf(" ");
        for(j=0;j<bt[i];j++) {
            printf("--");
        }
        printf("%d",ct[i]);
        printf(" ");
    }
    printf("\n|");
    for(i=0;i<n;i++) {
        for(j=0;j<bt[i]-1;j++) {
            printf(" ");
        }
        printf("P%d", i+1);
        for(j=0;j<bt[i]-1;j++) {
            printf(" ");
        }
        printf("|");
  }
    printf("\n");

    return 0;
}*/
