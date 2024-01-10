#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

// Process structure
typedef struct {
    int pid;           // Process ID
    int arrival_time;  // Arrival time
    int burst_time;    // Burst time
    int remaining_time; // Remaining time
    int completion_time; // Completion time
    int waiting_time;   // Waiting time
    int turnaround_time; // Turnaround time
    int is_completed;   // Flag to indicate if the process is completed
} Process;

// Function to sort the processes by arrival time
void sort_processes_by_arrival_time(Process *processes, int n) {
    int i, j;
    Process temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to sort the processes by remaining time
void sort_processes_by_remaining_time(Process *processes, int n) {
    int i, j;
    Process temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].remaining_time < processes[j].remaining_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}
int main() {
    int i, j, t, n, total_waiting_time = 0, total_turnaround_time = 0;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input data for each process
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = 0;
    }

    sort_processes_by_arrival_time(processes, n); // Sort processes by arrival time

printf("\n\n\nprocess  At   BT   WT   TA\n\n");
    // Run the scheduler
    for (t = processes[0].arrival_time; ; ) {
        // Find the process with the longest remaining time
        int idx = -1;
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= t && !processes[i].is_completed) {
                if (idx == -1 || processes[i].remaining_time > processes[idx].remaining_time) {
                    idx = i;
                }
            }
        }

        if (idx == -1) break; // All processes completed

        // Execute the process for 1 unit of time
        processes[idx].remaining_time--;
        t++;
        

        // If the process is completed, calculate waiting and turnaround time
        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = t;
            processes[idx].waiting_time = processes[idx].completion_time - processes[idx].arrival_time - processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            total_waiting_time += processes[idx].waiting_time;
            total_turnaround_time += processes[idx].turnaround_time;
            processes[idx].is_completed = 1;
            printf("%d         %d    %d    %d    %d\n",processes[idx].pid,processes[idx].arrival_time,processes[idx].burst_time,processes[idx].waiting_time, processes[idx].turnaround_time);
        }
    }

    printf("\n\n");

    // Calculate and print average waiting and turnaround time
    printf("Average waiting time = %f\n", (float)total_waiting_time / n);
    printf("Average turnaround time = %f\n", (float)total_turnaround_time / n);

    return 0;
}
