#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int product(int* arr, int size) {
    if (size == 1) {
        return arr[0];
    }

    int mid = size / 2;
    int left_arr[mid];
    int right_arr[size - mid];

    for (int i = 0; i < mid; i++) {
        left_arr[i] = arr[i];
    }
    for (int i = 0; i < size - mid; i++) {
        right_arr[i] = arr[mid + i];
    }

    int pipe_left[2];
    int pipe_right[2];
    pipe(pipe_left);
    pipe(pipe_right);

    pid_t pid_left = fork();
    if (pid_left == 0) {
        close(pipe_left[0]);
        int left_product = product(left_arr, mid);
        write(pipe_left[1], &left_product, sizeof(left_product));
        close(pipe_left[1]);
        exit(0);
    } else {
        pid_t pid_right = fork();
        if (pid_right == 0) {
            close(pipe_right[0]);
            int right_product = product(right_arr, size - mid);
            write(pipe_right[1], &right_product, sizeof(right_product));
            close(pipe_right[1]);
            exit(0);
        } else {
            close(pipe_left[1]);
            close(pipe_right[1]);

            waitpid(pid_left, NULL, 0);
            waitpid(pid_right, NULL, 0);

            int left_result, right_result;
            read(pipe_left[0], &left_result, sizeof(left_result));
            read(pipe_right[0], &right_result, sizeof(right_result));

            close(pipe_left[0]);
            close(pipe_right[0]);

            return left_result * right_result;
        }
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);

    int result = product(array, size);
    printf("The product of the array is: %d\n", result);

    return 0;
}

