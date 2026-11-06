#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char comando[7];
    while (1) {
        printf("mini-shell> ");
        fflush(stdout);
        scanf("%s", comando);
        if (comando[0] == 'e' && comando[1] == 'x' && comando[2] == 'i' && comando[3] == 't' && comando[4] == '\0') {
            break;
        }
        int comando_valido = 0;
        if (comando[0] == 'l' && comando[1] == 's' && comando[2] == '\0') {
            comando_valido = 1;
        }
        if (comando[0] == 'd' && comando[1] == 'a' && comando[2] == 't' && comando[3] == 'e' && comando[4] == '\0') {
            comando_valido = 1;
        }
        if (comando[0] == 'w' && comando[1] == 'h' && comando[2] == 'o' && comando[3] == 'a' && comando[4] == 'm' && comando[5] == 'i' && comando[6] == '\0') {
            comando_valido = 1;
        }
        if (comando_valido == 0) {
            printf("Errore: comando non trovato\n");
            continue;
        }
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            char *args[] = { comando, NULL };
            fflush(stdout);
            execvp(comando, args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        int status;
        wait(&status);
    }
    return 0;
}