#include<stdio.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void LJF(struct Process p[], int n) {
    int time = 0, i, j;
    struct Process temp;

    // sort processes by arrival time
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // process the tasks
    for (i = 0; i < n; i++) {
        int max_bt = -1, max_index = -1;
        for (j = i; j < n; j++) {
            if (p[j].arrival_time <= time && p[j].burst_time > max_bt) {
                max_bt = p[j].burst_time;
                max_index = j;
            }
        }

        if (max_index == -1) {
            // no processes available yet
            // printf("Idle for 1 second at time %d\n", time);
            time++;
            i--;
            continue;
        }

        // process the selected task
        temp = p[i];
        p[i] = p[max_index];
        p[max_index] = temp;
        p[i].completion_time = time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        // printf("Process %d executed from time %d to %d\n", p[i].pid, time, p[i].completion_time);
        time = p[i].completion_time;
    }

    // calculate average turnaround time and waiting time
    float avg_turnaround_time = 0, avg_waiting_time = 0;
    for (i = 0; i < n; i++) {
        avg_turnaround_time += p[i].turnaround_time;
        avg_waiting_time += p[i].waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;
    printf("\nPid\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("Average turnaround time = %.2f\n", avg_turnaround_time);
    printf("Average waiting time = %.2f\n", avg_waiting_time);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);
        p[i].pid = i+1;
    }

    LJF(p, n);

    return 0;
}
