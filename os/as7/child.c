#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>	

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define BUFFER_SIZE 1024

// Function to get the total number of bytes in the directory using popen
long get_directory_size(const char *dirname) {
    char command[BUFFER_SIZE];

    // Construct the command to get the directory size using 'du' and 'cut'
    snprintf(command, sizeof(command), "du -sb %s | cut -f1", dirname);
    
    // Open a pipe to execute the command and read its output
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        // Check if popen failed, print an error message, and exit with failure status
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Buffer to store the output of the command
    char result[BUFFER_SIZE];

    // Read the output of the command from the pipe
    if (fgets(result, sizeof(result), fp) != NULL) {
        // If successful, close the pipe, convert the result to a long integer, and return it
        pclose(fp);
        return atol(result);
    } else {
        // If no output was read, close the pipe and return -1 to indicate failure
        pclose(fp);
        return -1;
    }
}


int main() {
    // Child process
    char dirname[BUFFER_SIZE];
    int fd1 = open(FIFO1, O_RDONLY);
    if (fd1 == -1) {
        perror("open FIFO1");
        exit(EXIT_FAILURE);
    }

    // Read directory name from the parent
    ssize_t bytesRead = read(fd1, dirname, BUFFER_SIZE);
    if (bytesRead == -1) {
        perror("read from FIFO1");
        close(fd1);
        exit(EXIT_FAILURE);
    }
    close(fd1);

    // Get the total size of the directory
    long total_size = get_directory_size(dirname);

    // Send the result back to the parent
    int fd2 = open(FIFO2, O_WRONLY);
    if (fd2 == -1) {
        perror("open FIFO2");
        exit(EXIT_FAILURE);
    }

    char result[BUFFER_SIZE];
    snprintf(result, sizeof(result), "%ld", total_size);
    if (write(fd2, result, strlen(result) + 1) == -1) {
        perror("write to FIFO2");
        close(fd2);
        exit(EXIT_FAILURE);
    }
    close(fd2);

    return 0;
}

