#include <stdio.h>
#include <stdlib.h>

void calculateNeed(int n, int m, int **need, int **max, int **allocation);
int isSafe(int n, int m, int *available, int **allocation, int **max, int **need);

int main() {
    int n, m;
    char ch = 'Y';

    do
    {
        printf("Enter number of processes: ");
        scanf("%d", &n);
        printf("Enter number of resources: ");
        scanf("%d", &m);

        // Dynamically allocate memory for matrices
        int **allocation = (int **)malloc(n * sizeof(int *));
        int **max = (int **)malloc(n * sizeof(int *));
        int **need = (int **)malloc(n * sizeof(int *));
        int *available = (int *)malloc(m * sizeof(int));
        
        for (int i = 0; i < n; i++) {
            allocation[i] = (int *)malloc(m * sizeof(int));
            max[i] = (int *)malloc(m * sizeof(int));
            need[i] = (int *)malloc(m * sizeof(int));
        }

        // Input the available resources
        printf("Enter available resources:\n");
        for (int i = 0; i < m; i++) {
            printf("Resource %d: ", i);
            scanf("%d", &available[i]);
        }

        // Input the allocation matrix
        printf("Enter allocation matrix:\n");
        for (int i = 0; i < n; i++) {
            printf("Process %d:\n", i);
            for (int j = 0; j < m; j++) {
                printf("Resource %d: ", j);
                scanf("%d", &allocation[i][j]);
            }
        }

        // Input the max matrix
        printf("Enter maximum matrix:\n");
        for (int i = 0; i < n; i++) {
            printf("Process %d:\n", i);
            for (int j = 0; j < m; j++) {
                printf("Resource %d: ", j);
                scanf("%d", &max[i][j]);
            }
        }

        // Calculate the need matrix
        calculateNeed(n, m, need, max, allocation);

        // Check system safety
        if (isSafe(n, m, available, allocation, max, need)) {
            printf("The system is in a safe state.\n");
        } else {
            printf("The system is not in a safe state.\n");
        }

        // Free allocated memory
        for (int i = 0; i < n; i++) {
            free(allocation[i]);
            free(max[i]);
            free(need[i]);
        }
        free(allocation);
        free(max);
        free(need);
        free(available);

        printf("Do you want to run it again (Y/N) ? ");
        fflush(stdin);
        ch = getchar();

    }while(ch=='Y' || ch=='y');

    return 0;
}

void calculateNeed(int n, int m, int **need, int **max, int **allocation) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe(int n, int m, int *available, int **allocation, int **max, int **need) {
    int *work = (int *)malloc(m * sizeof(int));
    int *finish = (int *)malloc(n * sizeof(int));
    int *safeSequence = (int *)malloc(n * sizeof(int));
    int count = 0;

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    while (count < n) {
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[p][k];
                    }
                    finish[p] = 1;
                    safeSequence[count++] = p;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("The system is in an unsafe state.\n");
            free(work);
            free(finish);
            free(safeSequence);
            return 0;
        }
    }

    // Print the safe sequence
    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    free(work);
    free(finish);
    free(safeSequence);
    return 1;
}
