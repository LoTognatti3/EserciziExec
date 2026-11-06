#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Errore pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("Errore fork 1");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        char *args1[] = { "ls", "/tmp", NULL };
        fflush(stdout);
        execvp("ls", args1);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("Errore fork 2");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0) {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        char *args2[] = { "wc", "-l", NULL };
        fflush(stdout);
        execvp("wc", args2);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}