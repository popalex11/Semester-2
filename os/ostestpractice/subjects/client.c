#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char* myfifo1 = "./myfifo1";
    char* myfifo2 = "./myfifo2";

    int fd1 = open(myfifo1, O_WRONLY);
    int fd2 = open(myfifo2, O_RDONLY);

    char msg[80];
    while (1) {
        fgets(msg, 80, stdin);
        printf("Sent %s", msg);
        msg[strlen(msg) - 1] = '\0';
        write(fd1, msg, sizeof(msg));
        read(fd2, msg, 80);
        printf("%s", msg);
    }
}