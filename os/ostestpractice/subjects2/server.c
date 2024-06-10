#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    char* myfifo1 = "./myfifo1";
    char* myfifo2 = "./myfifo2";
    mkfifo(myfifo1, 0666);
    mkfifo(myfifo2, 0666);
    int fd1 = open(myfifo1, O_RDONLY);
    int fd2 = open(myfifo2, O_WRONLY);
    char msg[256];
    char* ptr;
    while (1) {
        read(fd1, msg, 256);
        char command[81];
        printf("Received %s", msg);
        sprintf(command, "./2.sh %s", msg);
        if (fork() == 0) {
            FILE* file = popen(command, "r");
            fgets(msg, 256, file);
            write(fd2, msg, sizeof(msg));
            exit(0);
        }
    }
    return 0;
}