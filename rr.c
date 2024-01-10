// this one is coreect 

#include<stdio.h>

int main()
{
    int n,i,j,tq,rem_bt[100],wt[100],tat[100],at[100],bt[100],ct[100],pid[100];
    float avgwt=0,avgtat=0;
    printf("Enter Total Process: ");
    scanf("%d",&n);
    printf("Enter Arrival Time and Burst Time for Process:\n");
    for(i=0;i<n;i++) {
        printf("Process Number %d :",i+1);
        scanf("%d%d",&at[i],&bt[i]);
        pid[i] = i+1;
        rem_bt[i] = bt[i];
    }
    printf("Enter Time Quantum:");
    scanf("%d",&tq);
    int wt_total = 0, tat_total = 0;
    int completed = 0;
    int current_time = 0;
    while(completed < n) {
        for(i=0; i<n; i++) {
            if(at[i] <= current_time && rem_bt[i] > 0) {
                if(rem_bt[i] > tq) {
                    current_time += tq;
                    rem_bt[i] -= tq;
                } else {
                    current_time += rem_bt[i];
                    rem_bt[i] = 0;
                    ct[i] = current_time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    wt_total += wt[i];
                    tat_total += tat[i];
                    completed++;
                }
            }
        }
    }
    printf("\nProcess |Turnaround Time|Waiting Time\n\n");
    for(i=0;i<n;i++) {
        printf("P[%d]\t|\t%d\t|\t%d\n", pid[i], tat[i], wt[i]);
    }
    avgwt = (float)wt_total/n;
    avgtat = (float)tat_total/n;
    printf("\nAverage Waiting Time=%f\n",avgwt);
    printf("Avg Turnaround Time=%f",avgtat);
    return 0;
}


/*
#include <stdio.h>

#define MAX_PROCESSES 10 // maximum number of processes

// structure for process information
typedef struct {
    int pid;           // process ID
    int arrival_time;  // arrival time of the process
    int burst_time;    // burst time of the process
    int remaining_time;// remaining time to complete the process
    int waiting_time;  // time the process has spent waiting
} process;

// function to perform round-robin scheduling
void round_robin(process p[], int n,int qnt) {
    int time = 0;                 // current time
    int completed = 0;            // number of completed processes
    int i, j;
    int time_quantum = qnt;

    // print the Gantt chart header
    printf("+");
    for (i = 0; i < n * 4; i++) {
        printf("-");
    }
    printf("+\n|");
    for (i = 0; i < n; i++) {
        printf(" P%d |", p[i].pid);
    }
    printf("\n+");
    for (i = 0; i < n * 4; i++) {
        printf("-");
    }
    printf("+\n");

    while (completed < n) {       // loop until all processes are completed
        for (i = 0; i < n; i++) { // loop through all processes
            if (p[i].remaining_time > 0) { // if the process has remaining time
                if (p[i].remaining_time > time_quantum) {
                    p[i].remaining_time -= time_quantum;
                    time += time_quantum;
                } else {
                    time += p[i].remaining_time;
                    p[i].waiting_time = time - p[i].burst_time - p[i].arrival_time;
                    p[i].remaining_time = 0;
                    completed++;
                }
                // print the Gantt chart
                printf("| P%d ", p[i].pid);
            } else {
                // if the process has already completed, print an empty space in the Gantt chart
                printf("|    ");
            }
        }
        printf("|\n");
    }

    float total_wait_time,total_turnaround_time;
// Calculate the total waiting time and turnaround time
    for (i = 0; i < n; i++) {
        total_wait_time += p[i].waiting_time;
        total_turnaround_time += p[i].waiting_time + p[i].burst_time;
    }

    // Calculate the average waiting time and average turnaround time
    float avg_wait_time = total_wait_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    // print the waiting time and turnaround time for each process
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", p[i].pid, p[i].waiting_time, p[i].waiting_time + p[i].burst_time);
    }

    printf("\n\nAverage waiting time: %f\n", avg_wait_time);
    printf("Average turnaround time: %f\n", avg_turnaround_time);


}

int main() {
    int qnt,n, i;
    process p[MAX_PROCESSES];

    printf("Welcome to Round Robin Scheduling!!");

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter time quantum: ");
    scanf("%d", &qnt);

    // get process information from the user
    for (i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Enter burst time: ");
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].pid = i + 1;
        printf("\n");
    }

    // perform round-robin scheduling
    round_robin(p, n,qnt);

    return 0;
}

*/