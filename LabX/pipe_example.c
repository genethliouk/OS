#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char writeMsg[] = "Hello from parent to child!";
    char readMsg[100];

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        close(fd[1]); // Close unused write end
        read(fd[0], readMsg, sizeof(readMsg));
        printf("Child received: %s\n", readMsg);
        close(fd[0]);
    } else {
        close(fd[0]); // Close unused read end
        write(fd[1], writeMsg, strlen(writeMsg) + 1);
        printf("Parent sent: %s\n", writeMsg);
        close(fd[1]);
    }

    return 0;
}
 
