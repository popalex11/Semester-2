#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define DIR_FIFO "/tmp/dir_fifo"    // FIFO for sending directory name
#define SIZE_FIFO "/tmp/size_fifo"  // FIFO for receiving total size
#define BUF_SIZE 256                // Buffer size for reading and writing

// Function to print error message and exit
void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    // Create the FIFO for directory name communication
    if (mkfifo(DIR_FIFO, 0666) == -1 && errno != EEXIST) {
        error_exit("mkfifo DIR_FIFO");
    }
    // Create the FIFO for size communication
    if (mkfifo(SIZE_FIFO, 0666) == -1 && errno != EEXIST) {
        error_exit("mkfifo SIZE_FIFO");
    }

    // Fork to create a child process
    pid_t pid = fork();
    if (pid < 0) {
        error_exit("fork");
    } else if (pid == 0) {
        // In child process, replace it with the "child" executable
        execl("./child", "child", NULL);
        error_exit("execl");
    }

    // In parent process
    // Open the FIFO for writing the directory name
    int dir_fd = open(DIR_FIFO, O_WRONLY);
    if (dir_fd == -1) {
        error_exit("open DIR_FIFO");
    }

    // Read the directory name from user input
    char dir_name[BUF_SIZE];
    printf("Enter directory name: ");
    scanf("%s", dir_name);

    // Send the directory name to the child process through the FIFO
    if (write(dir_fd, dir_name, strlen(dir_name) + 1) == -1) {
        error_exit("write DIR_FIFO");
    }

    close(dir_fd); // Close the directory FIFO after writing

    // Open the FIFO for reading the total size from the child process
    int size_fd = open(SIZE_FIFO, O_RDONLY);
    if (size_fd == -1) {
        error_exit("open SIZE_FIFO");
    }

    // Read the total size from the FIFO
    char size_str[BUF_SIZE];
    if (read(size_fd, size_str, BUF_SIZE) == -1) {
        error_exit("read SIZE_FIFO");
    }

    close(size_fd); // Close the size FIFO after reading

    // Print the total size of files in the directory
    printf("Total bytes in directory '%s': %s\n", dir_name, size_str);

    // Cleanup the FIFOs
    unlink(DIR_FIFO);
    unlink(SIZE_FIFO);

    return 0;
}

