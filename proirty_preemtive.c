/*
Name - Kothamasu Jayachandra
Roll Num - 2110110293
*/

//Welcome to Prority(preemtive) Scheduling!!"

#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int priority;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
};

int main() {
    int n, i, j;
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("Welcome to Prority Scheduling!!");

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n], temp;
    for (i = 0; i < n; i++) {
        printf("Enter the arrival time, burst time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
    }

    // sort the processes based on arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int current_time = 0, completed = 0;
    printf("\nGantt Chart:\n");
    printf("|");
    while (completed != n) {
        int highest_priority = -1, selected = -1;
        for (i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                if (p[i].priority < highest_priority || highest_priority == -1) {
                    highest_priority = p[i].priority;
                    selected = i;
                }
            }
        }
        if (selected == -1) {
            printf(" ");
            current_time++;
        } else {
            p[selected].remaining_time--;
            current_time++;
            printf("P%d", p[selected].pid);
            if (p[selected].remaining_time == 0) {
                p[selected].turnaround_time = current_time - p[selected].arrival_time;
                p[selected].waiting_time = p[selected].turnaround_time - p[selected].burst_time;
                avg_turnaround_time += p[selected].turnaround_time;
                avg_waiting_time += p[selected].waiting_time;
                completed++;
            }
        }
        printf("|");
    }
    printf("\n");

    printf("\nProcess\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, p[i].arrival_time,
               p[i].priority, p[i].waiting_time, p[i].turnaround_time);
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    printf("\nAverage Waiting Time: %f\n", avg_waiting_time);
    printf("Average Turnaround Time: %f\n", avg_turnaround_time);

    return 0;
}
