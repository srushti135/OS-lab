#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10

typedef struct 
{
    int id, arrival_time, burst_time, priority, remaining_time, completion_time, waiting_time, turnaround_time;
    bool completed;
}Process;

void sort_by_arrival(Process p[], int n) 
{
    for(int i=0; i<n-1; i++) 
    {
        for(int j=0; j<n-i- 1; j++)
        {
            if(p[j].arrival_time > p[j + 1].arrival_time) 
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void non_preemptive_priority(Process p[], int n) 
{
    sort_by_arrival(p, n);
    int time = 0, completed = 0;

    while(completed < n) 
    {
        int highest_priority = -1, index = -1;
        for(int i=0; i<n; i++) 
        {
            if(!p[i].completed && p[i].arrival_time <= time) 
            {
                if(highest_priority == -1 || p[i].priority < highest_priority) 
                {
                    highest_priority = p[i].priority;
                    index = i;
                }
            }
        }

        if(index == -1)
            time++;
        else 
        {
            p[index].completion_time = time + p[index].burst_time;
            p[index].turnaround_time = p[index].completion_time - p[index].arrival_time;
            p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;
            p[index].completed = true;
            time += p[index].burst_time;
            completed++;
        }
    }
}

void preemptive_priority(Process p[], int n) 
{
    sort_by_arrival(p, n);
    int time = 0, completed = 0;

    while(completed < n) 
    {
        int highest_priority = -1, index = -1;
        for(int i=0; i<n; i++) 
        {
            if(!p[i].completed && p[i].arrival_time <= time) 
            {
                if(highest_priority == -1 || p[i].priority < highest_priority)
                {
                    highest_priority = p[i].priority;
                    index = i;
                }
            }
        }

        if (index == -1) 
            time++;
        else 
        {
            p[index].remaining_time--;
            time++;
            if(p[index].remaining_time == 0) 
            {
                p[index].completion_time = time;
                p[index].turnaround_time = p[index].completion_time - p[index].arrival_time;
                p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;
                p[index].completed = true;
                completed++;
            }
        }
    }
}

void print_processes(Process p[], int n) 
{
    printf("\nID  AT  BT  Priority  CT  TAT  WT\n");
    for(int i=0; i<n; i++) 
    {
        printf("P%d  %d   %d   %d\t      %d   %d   %d\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
}

int main() 
{
    int n, choice;
    Process p[MAX_PROCESSES];
    char ch;

    do 
    {
        printf("Enter number of processes: ");
        scanf("%d", &n);

        if(n<=0)
            printf("No processes are there to be executed !!\n");
        
        else
        {        
            printf("Enter process details (ID, Arrival Time, Burst Time, Priority):\n");
            for(int i=0; i<n; i++) 
            {
                scanf("%d %d %d %d", &p[i].id, &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
                p[i].remaining_time = p[i].burst_time;
                p[i].completed = false;
            }

            printf("Choose Scheduling Algorithm:");
            printf("\n1. Non-Preemptive Priority Scheduling");
            printf("\n2. Preemptive Priority Scheduling\n");
            scanf("%d", &choice);
   
            if(choice == 1)
            {
                non_preemptive_priority(p, n);
                print_processes(p, n);
            }
            else if(choice == 2) 
            {
                preemptive_priority(p, n);
                print_processes(p, n);
            }
            else
            {
                printf("Invalid Choice, Try Again !!\n");
                return 1;
            }
        }
        printf("Do you want to run again (Y/N)? ");
        fflush(stdin);
        ch = getchar();
    }while(ch=='Y' || ch=='y');

    return 0;
}