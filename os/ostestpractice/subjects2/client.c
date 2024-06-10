#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
    char* myfifo1 = "./myfifo1";
    char* myfifo2 = "./myfifo2";
    int fd1 = open(myfifo1, O_WRONLY);
    int fd2 = open(myfifo2, O_RDONLY);
    char msg[256];
    while(1) {
        fgets(msg, 256, stdin);
        write(fd1, msg, sizeof(msg));
        read(fd2, msg, 256);
        printf("%s", msg);
    }
    return 0;
}