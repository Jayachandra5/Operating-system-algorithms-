#include<stdio.h>

int main() {
    int n, i, j, temp, current_time = 0, completed = 0, smallest_bt_index = 0;
    float avg_wt = 0, avg_tat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], wt[n], tat[n], rt[n], remaining_processes = n;

    for(i=0; i<n; i++) {
        printf("Enter the Arrival Time, Burst Time, and Process ID of process %d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &pid[i]);
        rt[i] = bt[i];
    }

    while(remaining_processes != 0) {
        smallest_bt_index = -1;
        int smallest_bt = 99999;
        for(i=0; i<n; i++) {
            if(at[i] <= current_time && rt[i] > 0) {
                if(rt[i] < smallest_bt) {
                    smallest_bt_index = i;
                    smallest_bt = rt[i];
                }
            }
        }

        if(smallest_bt_index == -1) {
            current_time++;
            continue;
        }

        rt[smallest_bt_index]--;

        if(rt[smallest_bt_index] == 0) {
            remaining_processes--;
            tat[smallest_bt_index] = current_time + 1 - at[smallest_bt_index];
            wt[smallest_bt_index] = tat[smallest_bt_index] - bt[smallest_bt_index];
            if(wt[smallest_bt_index] < 0) {
                wt[smallest_bt_index] = 0;
            }
            avg_wt += wt[smallest_bt_index];
            avg_tat += tat[smallest_bt_index];
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
