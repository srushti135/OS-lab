#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int pid;      // Process ID
    int bt;       // Burst Time
    int at;       // Arrival Time
    int ct;       // Completion Time
    int wt;       // Waiting Time
    int tat;      // Turnaround Time
}Process;

// Function prototypes (optional, since we are defining function body before invoking main function) 
void input(Process*, int);
void sort(Process*, int);
void calculate(Process*, int, float*, float*);
void display(Process*, int, float, float);

// Function to input arrival time and burst time
void input(Process *p, int n) 
{
 for(int i=0; i<n; i++) 
    {
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &p[i].at);  // Arrival time
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);  // Burst time
        p[i].pid = i + 1;  // Process ID
    }
}

// Function to sort processes based on burst time and arrival time
void sort(Process *p, int n) 
{
    for(int i=0; i<n; i++) 
    {
        for(int j=i+1; j<n; j++) 
        {
            // Sort by burst time, and if equal, by arrival time
            if(p[j].bt<p[i].bt || (p[j].bt==p[i].bt && p[j].at<p[i].at)) 
            {
                // Swap process data(burst time and arrival time)
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Function to calculate average waiting time and average turnaround time
void calculate(Process *p, int n, float *avg_wt, float *avg_tat) 
{
    int total_wt = 0, total_tat = 0;
    
    // Calculate Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT)
    int current_time = 0;
    for(int i=0; i<n; i++) 
    {
        // Update the completion time for each process
        if(current_time<p[i].at) 
        {
            current_time = p[i].at;  // If the current time is less than the arrival time, set it to the arrival time
        }
        p[i].ct = current_time + p[i].bt;  // Completion time = current time + burst time
        current_time = p[i].ct;  // Update the current time to the completion time of this process

        // Calculate Turnaround Time (TAT) = Completion Time - Arrival Time
        p[i].tat = p[i].ct - p[i].at;

        // Calculate Waiting Time (WT) = Turnaround Time - Burst Time
        p[i].wt = p[i].tat - p[i].bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Calculate average waiting time and average turnaround time
    *avg_wt = (float)total_wt / n;
    *avg_tat = (float)total_tat / n;
}

// Function to display the process details
void display(Process *p, int n, float avg_wt, float avg_tat)
{
    printf("Process  Arrival Time  Burst Time  Waiting Time  Turnaround Time\n");
    for(int i=0; i<n; i++) 
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

// Main function
int main() 
{
    int n;
    float avg_wt, avg_tat;
    char ch;

    do
    {
        // Dynamic memory allocation for processes
        printf("Enter number of processes: ");
        scanf("%d", &n);

        if(n<=0)
            printf("No Processses are there to be executed !!\n");
        else
        {
            Process *p = (Process *)malloc(n * sizeof(Process));

            if(p==NULL) 
            {
                printf("Memory allocation failed\n");
                return -1;  // Exit if memory allocation fails
            }

            // Input arrival and burst times
            input(p,n);

            // Sort processes based on burst time and arrival time
            sort(p,n);

            // Calculate waiting times and turnaround times
            calculate(p,n,&avg_wt,&avg_tat);

            // Display process details and averages
            display(p,n,avg_wt,avg_tat);

            // Free dynamically allocated memory
            free(p);
        }

        printf("Do you want to run again (Y/N) ? ");
        fflush(stdin);
        ch=getchar();
    }while(ch=='Y' || ch=='y');

    return(0);
}
