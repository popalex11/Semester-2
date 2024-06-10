#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int pid;
    char* myfifo1 = "./myfifo1";
    char* myfifo2 = "./myfifo2";
    mkfifo(myfifo1, 0666);
    mkfifo(myfifo2, 0666);
    int fd1 = open(myfifo1, O_RDONLY);
    int fd2 = open(myfifo2, O_WRONLY);
    char msg[160];
    while (1) {
        read(fd1, msg, 80);
        printf("Received %s\n", msg);
        char command[80];
        sprintf(command, "diff %s", msg);
        FILE* file = popen(command, "r");
        msg[0] = '\0';
        char lmsg[80];
        while (fgets(lmsg, 80, file)) {
            strcat(msg, lmsg);
            strcat(msg, "\n");
        }
        write(fd2, msg, sizeof(msg));
    }
    return 0;
}