#include <stdio.h>
#include <unistd.h>

main () {
	fork();
	printf("PID: %d ParentPID: %d\n", getpid(), getppid());

}
