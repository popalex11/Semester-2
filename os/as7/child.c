#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define DIR_FIFO "/tmp/dir_fifo"    // FIFO for receiving directory name
#define SIZE_FIFO "/tmp/size_fifo"  // FIFO for sending total size
#define BUF_SIZE 1024               // Increased buffer size for handling longer paths

// Function to print error message and exit
void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

// Function to calculate the total size of files in the given directory
off_t calculate_directory_size(const char *dir_name) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    off_t total_size = 0;
    char file_path[BUF_SIZE];

    // Open the directory
    if (!(dir = opendir(dir_name))) {
        perror("opendir");
        return -1;
    }

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // If the entry is a regular file
            // Construct the full path of the file
            if (snprintf(file_path, sizeof(file_path), "%s/%s", dir_name, entry->d_name) >= sizeof(file_path)) {
                fprintf(stderr, "Path length exceeds buffer size\n");
                continue;
            }
            // Get file statistics
            if (stat(file_path, &file_stat) == 0) {
                // Add file size to total size
                total_size += file_stat.st_size;
            } else {
                perror("stat");
            }
        }
    }

    closedir(dir); // Close the directory
    return total_size;
}

int main() {
    // Open the FIFO for reading the directory name
    int dir_fd = open(DIR_FIFO, O_RDONLY);
    if (dir_fd == -1) {
        error_exit("open DIR_FIFO");
    }

    // Read the directory name from the FIFO
    char dir_name[BUF_SIZE];
    if (read(dir_fd, dir_name, BUF_SIZE) == -1) {
        error_exit("read DIR_FIFO");
    }

    close(dir_fd); // Close the directory FIFO after reading

    // Calculate the total size of files in the directory
    off_t total_size = calculate_directory_size(dir_name);

    // Open the FIFO for writing the total size
    int size_fd = open(SIZE_FIFO, O_WRONLY);
    if (size_fd == -1) {
        error_exit("open SIZE_FIFO");
    }

    // Convert the total size to a string and write it to the FIFO
    char size_str[BUF_SIZE];
    snprintf(size_str, sizeof(size_str), "%ld", total_size);

    if (write(size_fd, size_str, strlen(size_str) + 1) == -1) {
        error_exit("write SIZE_FIFO");
    }

    close(size_fd); // Close the size FIFO after writing

    return 0;
}

