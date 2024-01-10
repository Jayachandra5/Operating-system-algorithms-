// this corrcet 
#include<stdio.h>

int main() {
    int n, i, j, temp, current_time = 0, smallest_bt, completed = 0;
    float avg_wt = 0, avg_tat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], wt[n], tat[n], rt[n];

    for(i=0; i<n; i++) {
        printf("Enter the Arrival Time, Burst Time, and Process ID of process %d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &pid[i]);
        rt[i] = bt[i];
    }

    while(completed != n) {
        smallest_bt = -1;
        for(i=0; i<n; i++) {
            if(at[i] <= current_time && rt[i] > 0) {
                if(smallest_bt == -1 || rt[i] < rt[smallest_bt]) {
                    smallest_bt = i;
                }
            }
        }

        if(smallest_bt == -1) {
            current_time++;
            continue;
        }

        rt[smallest_bt]--;

        if(rt[smallest_bt] == 0) {
            completed++;
            tat[smallest_bt] = current_time + 1 - at[smallest_bt];
            wt[smallest_bt] = tat[smallest_bt] - bt[smallest_bt];
            if(wt[smallest_bt] < 0) {
                wt[smallest_bt] = 0;
            }
            avg_wt += wt[smallest_bt];
            avg_tat += tat[smallest_bt];
        }

        current_time++;
    }

    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0; i<n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %f\nAverage Turnaround Time: %f\n", avg_wt/n, avg_tat/n);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>

struct process {
    int process_id;
    int burst_time;
    int arrival_time;
};

int main() {
    int num_processes, i, j, temp;
    float total_wait_time = 0, total_turnaround_time = 0;
    
     printf("Welcome to Shortest Job First Non Preemtive Scheduling!!");

    // Accept the number of processes in the ready queue
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    
    // Create an array of processes
    struct process processes[num_processes];
    
    // Accept the process id, arrival time, and burst time for each process
    for (i = 0; i < num_processes; i++) {
        printf("Enter the process id, arrival time, and burst time for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].process_id, &processes[i].arrival_time, &processes[i].burst_time);
    }
    
    // Sort the processes based on their arrival time in ascending order
    for (i = 0; i < num_processes; i++) {
        for (j = i + 1; j < num_processes; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                // Swap the processes
                temp = processes[i].burst_time;
                processes[i].burst_time = processes[j].burst_time;
                processes[j].burst_time = temp;
                
                temp = processes[i].process_id;
                processes[i].process_id = processes[j].process_id;
                processes[j].process_id = temp;
                
                temp = processes[i].arrival_time;
                processes[i].arrival_time = processes[j].arrival_time;
                processes[j].arrival_time = temp;
            }
        }
    }
    
    // Calculate the waiting time and turnaround time for each process
    int waiting_time[num_processes], turnaround_time[num_processes];
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;
    for (i = 1; i < num_processes; i++) {
        int previous_completion_time = processes[i-1].burst_time + processes[i-1].arrival_time;
        int current_arrival_time = processes[i].arrival_time;
        int current_burst_time = processes[i].burst_time;
        
        if (previous_completion_time < current_arrival_time) {
            // If the CPU is idle, then the waiting time is 0
            waiting_time[i] = 0;
        } else {
            // Otherwise, the waiting time is the difference between the previous completion time and the current arrival time
            waiting_time[i] = previous_completion_time - current_arrival_time;
        }
        
        turnaround_time[i] = waiting_time[i] + current_burst_time;
    }
    
    // Calculate the total waiting time and turnaround time
    for (i = 0; i < num_processes; i++) {
        total_wait_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Calculate the average waiting time and average turnaround time
    float avg_wait_time = total_wait_time / num_processes;
    float avg_turnaround_time = total_turnaround_time / num_processes;
    
    // Print the waiting time, turnaround time, average waiting time, and average turnaround time
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
    }
    printf("Average waiting time: %f\n", avg_wait_time);
    printf("Average turnaround time: %f\n", avg_turnaround_time);
    
    return 0;
}

*/
