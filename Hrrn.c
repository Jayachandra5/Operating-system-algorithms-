#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int response_ratio;
    int completed;
};

void calculate_waiting_time(struct process *procs, int n)
{
    int i, j;
    int current_time = 0;
    float average_waiting_time = 0.0;
    float average_turnaround_time = 0.0;

    for (i = 0; i < n; i++) {
        // Initialize the response ratio for each process
        procs[i].response_ratio = 0;
        procs[i].completed = 0;
    }

    printf("P\tAT\tBT\tWT\tTT\n");

    while (1) {
        // Find the process with the highest response ratio
        int highest_rr_index = -1;
        float highest_rr_value = -1.0;
        for (i = 0; i < n; i++) {
            if (procs[i].completed == 0) {
                float rr = (current_time - procs[i].arrival_time + procs[i].burst_time) / procs[i].burst_time;
                if (rr > highest_rr_value) {
                    highest_rr_value = rr;
                    highest_rr_index = i;
                }
            }
        }

        // If no process is found, exit the loop
        if (highest_rr_index == -1) {
            break;
        }

        // Update waiting time and turnaround time for the selected process
        procs[highest_rr_index].waiting_time = current_time - procs[highest_rr_index].arrival_time;
        procs[highest_rr_index].turnaround_time = procs[highest_rr_index].waiting_time + procs[highest_rr_index].burst_time;

        // Update the average waiting time and average turnaround time
        average_waiting_time += procs[highest_rr_index].waiting_time;
        average_turnaround_time += procs[highest_rr_index].turnaround_time;

        // Mark the selected process as completed
        procs[highest_rr_index].completed = 1;

        // Print the results for the selected process
        printf("P%d\t%d\t%d\t%d\t%d\n", procs[highest_rr_index].pid,
               procs[highest_rr_index].arrival_time,
               procs[highest_rr_index].burst_time,
               procs[highest_rr_index].waiting_time,
               procs[highest_rr_index].turnaround_time);

        // Move the current time forward to the end of the selected process
        current_time += procs[highest_rr_index].burst_time;
    }

    // Calculate the average waiting time and average turnaround time
    average_waiting_time /= n;
    average_turnaround_time /= n;

    // Print the final results
    printf("Average Waiting Time: %f\n", average_waiting_time);
    printf("Average Turnaround Time: %f\n", average_turnaround_time);
}

int main()
{
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process *procs = (struct process*)malloc(n * sizeof(struct process));

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &procs[i].arrival_time, &procs[i].burst_time);
        procs[i].pid = i + 1;
    }
    calculate_waiting_time(procs, n);

    return 0;
}
