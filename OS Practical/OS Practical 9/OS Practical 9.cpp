#!/bin/bash

echo "Welcome to Basic Shell Script!"

echo "Current directory is:"
pwd

echo "List of files:"
ls -l

echo "Current date and time:"
date

echo "Content of a file (test.txt):"
cat test.txt

Code:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CMD_LEN 1024

int main() {
    char command[MAX_CMD_LEN];

    while (1) {
        printf("myshell> ");
        fgets(command, MAX_CMD_LEN, stdin);

        // Remove newline character at the end
        command[strcspn(command, "\n")] = 0;

        // If the user types "exit", break the loop
        if (strcmp(command, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        // Fork and execute the command
        pid_t pid = fork();
        if (pid == 0) {
            // In child process
            execlp(command, command, (char *)NULL);
            // If execlp fails
            printf("Command not found: %s\n", command);
            exit(1);
        } else {
            // In parent process
            wait(NULL);
        }
    }
    return 0;
}

output:
chmod +x myscript.sh   # make it executable
./myscript.sh

