#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    char *fifo12 = "./fifo12";
    char *fifo21 = "./fifo21";
    mkfifo(fifo12, 0666);
    mkfifo(fifo21, 0666);

    int pid = fork();
    if (pid == 0)
    {
        int fd1 = open(fifo12, O_RDONLY);

        ssize_t sizeof1, sizeof2;
        char file1[50], file2[50];

        read(fd1, &sizeof1, sizeof(ssize_t));
        read(fd1, file1, sizeof1);
        // printf("File 1: $%s$%ld$\n", file1, sizeof1);
        read(fd1, &sizeof2, sizeof(ssize_t));
        read(fd1, file2, sizeof2);
        close(fd1);
        // printf("File 2: $%s$%ld$\n", file2, sizeof2);

        int fd2 = open(fifo21, O_WRONLY);
        char command[300];

        snprintf(command, 300, "grep -Fxv -f %s %s", file2, file1);
        // printf("$%s$\n", command);
        FILE *fp = popen(command, "r");
        char buffer[100];
        while (fgets(buffer, 100, fp))
        {
            // buffer[strlen(buffer) - 1] = '\0';
            //  printf("Buffer:$%s$\n", buffer);
            write(fd2, buffer, strlen(buffer) + 1);
        }
        pclose(fp);
        snprintf(command, 300, "grep -Fxv -f %s %s", file1, file2);
        // printf("$%s$\n", command);
        FILE *fp2 = popen(command, "r");
        while (fgets(buffer, 100, fp2))
        {
            // buffer[strlen(buffer) - 1] = '\0';
            //  printf("Buffer:$%s$\n", buffer);
            write(fd2, buffer, strlen(buffer) + 1);
        }
        pclose(fp2);
        close(fd2);
        exit(0);
    }

    {
        // this part writes from parent to child
        int fd1 = open(fifo12, O_WRONLY);
        ssize_t sizeof1 = strlen(argv[1]) + 1;
        ssize_t sizeof2 = strlen(argv[2]) + 1;
        // printf("Parent:%s\n%s\n", argv[1], argv[2]);
        write(fd1, &sizeof1, sizeof(ssize_t));
        write(fd1, argv[1], strlen(argv[1]) + 1);
        // printf("Parent wrote $%s$%ld$\n", argv[1], sizeof1);
        write(fd1, &sizeof2, sizeof(ssize_t));
        write(fd1, argv[2], strlen(argv[2]) + 1);
        // printf("Parent wrote $%s$%ld$\n", argv[2], sizeof2);
        close(fd1);
        // printf("Parent has finished writing.\n");
    }

    int fd2 = open(fifo21, O_RDONLY);
    ssize_t n;
    char buffer[100];
    while ((n = read(fd2, buffer, 100)) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        printf("%s\n", buffer);
    }

    wait(NULL);
    close(fd2);
    unlink(fifo12);
    unlink(fifo21);
}