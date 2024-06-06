#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h> // Include errno.h for error handling

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define BUFFER_SIZE 1024

int main() {
    // Create the FIFOs if they don't exist
    if (mkfifo(FIFO1, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo FIFO1");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(FIFO2, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo FIFO2");
        exit(EXIT_FAILURE);
    }

    char dirname[BUFFER_SIZE];
    printf("Enter directory name: ");
    scanf("%s", dirname);

    // Send directory name to the child
    int fd1 = open(FIFO1, O_WRONLY);
    if (fd1 == -1) {
        perror("open FIFO1");
        exit(EXIT_FAILURE);
    }

    // Write directory name to FIFO1
    if (write(fd1, dirname, strlen(dirname) + 1) == -1) {
        perror("write to FIFO1");
        close(fd1);
        exit(EXIT_FAILURE);
    }
    close(fd1);

    // Wait for the result from the child
    int fd2 = open(FIFO2, O_RDONLY);
    if (fd2 == -1) {
        perror("open FIFO2");
        exit(EXIT_FAILURE);
    }

    char result[BUFFER_SIZE];
    ssize_t bytesRead = read(fd2, result, BUFFER_SIZE);
    if (bytesRead == -1) {
        perror("read from FIFO2");
        close(fd2);
        exit(EXIT_FAILURE);
    }
    close(fd2);

    // Print the result received from the child
    printf("Total size of all files in directory '%s': %s bytes\n", dirname, result);

    // Clean up
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}

