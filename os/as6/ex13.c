#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

void calculate_total_bytes(const char* dir_name) {
    // Prepare the command to get the total bytes using 'du -sb'
    execlp("du", "du", "-sb", dir_name, NULL);
    // If execlp fails
    perror("execlp");
    exit(EXIT_FAILURE);
}

int main() {
    int pipe_fds1[2], pipe_fds2[2];
    pid_t pid;
    char dir_name[BUFFER_SIZE] = "/home/aponmywrist/Desktop/UNI AI/Semester-2/Graphs"; // Replace with the desired directory path
    char buffer[BUFFER_SIZE];
    
    // Create pipes
    if (pipe(pipe_fds1) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    if (pipe(pipe_fds2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    // Fork the process
    pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) { // Parent process
        // Close unnecessary pipe ends
        close(pipe_fds1[0]); // Close read end of first pipe
        close(pipe_fds2[1]); // Close write end of second pipe
        
        // Write the directory name to the pipe
        write(pipe_fds1[1], dir_name, strlen(dir_name) + 1);
        
        // Close the write end of the first pipe after sending the data
        close(pipe_fds1[1]);
        
        // Wait for the child process to finish
        wait(NULL);
        
        // Read the total number of bytes from the second pipe
        int n = read(pipe_fds2[0], buffer, BUFFER_SIZE - 1);
        if (n > 0) {
            buffer[n] = '\0'; // Null-terminate the string
        } else {
            buffer[0] = '\0';
        }
        
        // Extract and print the number of bytes
        char* token = strtok(buffer, "\t");
        if (token) {
            printf("Total number of bytes in directory '%s': %s\n", dir_name, token);
        } else {
            printf("Failed to read the directory size\n");
        }
        
        // Close the read end of the second pipe
        close(pipe_fds2[0]);
        
    } else { // Child process
        // Close unnecessary pipe ends
        close(pipe_fds1[1]); // Close write end of first pipe
        close(pipe_fds2[0]); // Close read end of second pipe

        // Read the directory name from the first pipe
        read(pipe_fds1[0], dir_name, BUFFER_SIZE);
        
        // Redirect stdout to the write end of the second pipe
        dup2(pipe_fds2[1], STDOUT_FILENO);
        
        // Close the pipe ends after duplication
        close(pipe_fds1[0]);
        close(pipe_fds2[1]);

        // Calculate the total number of bytes and send it back to the parent
        calculate_total_bytes(dir_name);
        
        // Exit the child process
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}

