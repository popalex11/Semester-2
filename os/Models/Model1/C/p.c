#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
int main(int argc, char *argv[])
{
    int pipe12[2]; // talks from parent to child
    pipe(pipe12);
    int pipe21[2]; // talks from child to parent
    pipe(pipe21);
    int pid = fork();
    if (pid == 0)
    {
        // this is the server presumably
        close(pipe21[0]);
        close(pipe12[1]);

        char path[100], rights[5];
        ssize_t sizeofpath, sizeofrights;
        read(pipe12[0], &sizeofpath, sizeof(ssize_t));
        read(pipe12[0], path, sizeofpath);
        read(pipe12[0], &sizeofrights, sizeof(ssize_t));
        read(pipe12[0], rights, sizeofrights);
        close(pipe12[0]);
        // printf("Path read:$%s$\n", path);

        char command[200];
        snprintf(command, 200, "stat %s | grep \"Uid\" | cut -d' ' -f 2 | sed \"s/\(//g\" | cut -d'/' -f 1", path);
        FILE *fp = popen(command, "r");
        char buffer[50];
        fgets(buffer, 50, fp);
        pclose(fp);
        buffer[strlen(buffer) - 1] = '\0';
        // printf("Buffer:$%s$\n", buffer);
        if (strcmp(buffer, rights) == 0)
        {
            write(pipe21[1], "DA", strlen("DA") + 1);
        }
        write(pipe21[1], "NU", strlen("NU") + 1);
        close(pipe21[1]);
        exit(0);
    }
    // this is the client
    close(pipe21[1]);
    close(pipe12[0]);

    ssize_t sizeofpath = strlen(argv[1]) + 1, sizeofrights = strlen(argv[2]) + 1;
    write(pipe12[1], &sizeofpath, sizeof(ssize_t));
    write(pipe12[1], argv[1], strlen(argv[1]) + 1);
    write(pipe12[1], &sizeofrights, sizeof(ssize_t));
    write(pipe12[1], argv[2], strlen(argv[2]) + 1);
    close(pipe12[1]);

    char answer[3];
    read(pipe21[0], answer, 3);
    printf("%s\n", answer);
    wait(NULL);
    close(pipe21[0]);
}