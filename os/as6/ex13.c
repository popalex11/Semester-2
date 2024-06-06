#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define COMMAND_SIZE 2048

int main() {
    int pipe1[2], pipe2[2]; // Two pipes for communication between parent and child
    pid_t pid;
    char dir_name[BUFFER_SIZE]; // Buffer to store the directory name
    char buffer[BUFFER_SIZE]; // Buffer to store data read from pipes
    FILE *fp;
    long long total_bytes;
    double total_mb;

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // Parent process
        close(pipe1[0]); // Close reading end of pipe1
        close(pipe2[1]); // Close writing end of pipe2

        // Get directory name from user
        printf("Enter directory name: ");
        fgets(dir_name, BUFFER_SIZE, stdin);
        dir_name[strcspn(dir_name, "\n")] = 0; // Remove newline character

        // Send directory name to child
        write(pipe1[1], dir_name, strlen(dir_name) + 1);
        close(pipe1[1]); // Close writing end of pipe1

        // Wait for child process to finish
        wait(NULL);

        // Read total bytes from child
        read(pipe2[0], buffer, BUFFER_SIZE);
        total_bytes = atoll(buffer); // Use atoll for long long int conversion
        total_mb = total_bytes / (1024.0 * 1024.0); // Convert bytes to MB

        // Print results
        printf("Total bytes in directory '%s': %lld\n", dir_name, total_bytes);
        printf("Total megabytes in directory '%s': %.2f MB\n", dir_name, total_mb);

        close(pipe2[0]); // Close reading end of pipe2
    } else {
        // Child process
        close(pipe1[1]); // Close writing end of pipe1
        close(pipe2[0]); // Close reading end of pipe2

        // Read directory name from parent
        read(pipe1[0], dir_name, BUFFER_SIZE);
        close(pipe1[0]); // Close reading end of pipe1

        // Compute total bytes using shell command
        char command[COMMAND_SIZE];
        snprintf(command, sizeof(command), "du -sb '%s' | cut -f1", dir_name);

        // Open a pipe to the shell command
        fp = popen(command, "r");
        if (fp == NULL) {
            perror("popen");
            exit(EXIT_FAILURE);
        }

        // Get the result from the command and send it to the parent
        if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
            write(pipe2[1], buffer, strlen(buffer) + 1);
        }
        pclose(fp);
        close(pipe2[1]); // Close writing end of pipe2

        exit(EXIT_SUCCESS);
    }

    return 0;
}

