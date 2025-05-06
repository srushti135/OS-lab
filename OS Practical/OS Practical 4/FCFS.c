#include<stdio.h>
#include<stdlib.h>

// Structure for Process
struct Process
{
    int id, at, bt, ct, tat, wt;
};

// Function prototypes (optional, since we are defining function body before invoking main function) 
void input(struct Process*, int);
void sort(struct Process*, int);
void calc(struct Process*, int, float*, float*);
void show(struct Process*, int, float, float);

// Function to take input for arrival and burst times
void input(struct Process *p, int n) 
{
    for(int i=0; i<n; i++) 
    {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].id = i + 1;
    }
}

// Function to sort processes based on arrival times
void sort(struct Process *p, int n) 
{
    for(int i=0; i<n-1; i++) 
    {
        for(int j=0; j<n-i-1; j++) 
        {
            if(p[j].at>p[j + 1].at) 
            {
                // Sorting burst times
                int temp = p[j].bt;
                p[j].bt = p[j + 1].bt;
                p[j + 1].bt = temp;

                // Sorting arrival times
                temp = p[j].at;
                p[j].at = p[j + 1].at;
                p[j + 1].at = temp;

                // Sorting process IDs
                temp = p[j].id;
                p[j].id = p[j + 1].id;
                p[j + 1].id = temp;
            }
        }
    }
}

// Function to calculate waiting time, turn-around time, and completion time
void calc(struct Process *p, int n, float *avg_wt, float *avg_tat) 
{   
    int total_wt = 0, total_tat = 0;
    int sum = 0;
    sum = sum + p[0].at;
    
    for(int i=0; i<n; i++) 
    {
        sum = sum + p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;  
        
        if (sum<p[i + 1].at) 
        {
            int t = p[i + 1].at - sum;
            sum = sum + t;
        } 
    }
    *avg_wt = (float)total_wt / n;
    *avg_tat = (float)total_tat / n;
}

// Function to display process details
void show(struct Process *p, int n, float avg_wt, float avg_tat) 
{
    printf("Process  Arrival Time  Burst Time  Waiting Time  Turnaround Time\n");
    for(int i=0; i<n; i++) 
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
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
        printf("Enter the number of processes: ");
        scanf("%d", &n);

        if(n<=0)
            printf("No Processes are there to be executed !!\n");
        else
        {        
            // Dynamically allocate memory for n processes
            struct Process *p = (struct Process*)malloc(n * sizeof(struct Process));
            
            // Input process details
            input(p, n);
            
            // Sort processes based on arrival time
            sort(p, n);
            
            // Calculate waiting time, turn-around time, and completion time
            calc(p, n, &avg_wt, &avg_tat);
            
            // Display process details
            show(p, n, avg_wt, avg_tat);
            
            // Free dynamically allocated memory
            free(p);
        }

        printf("Do you want to run again (Y/N) ? ");
        fflush(stdin);
        ch=getchar();
    }while(ch=='Y' || ch=='y');
    
    return 0;
}
