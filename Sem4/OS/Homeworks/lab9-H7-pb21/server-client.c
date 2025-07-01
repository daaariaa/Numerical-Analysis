#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <sys/wait.h>

#define MAX_BUF 256

int main() {
    // declarăm două pipe-uri pentru comunicare bidirecțională
    // pipe_client_to_server: client scrie, server citește
    // pipe_server_to_client: server scrie, client citește
    int pipe_client_to_server[2];
    int pipe_server_to_client[2];

    // verificăm dacă au fost create corect
    if (pipe(pipe_client_to_server) == -1) {
        perror("pipe client_to_server");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipe_server_to_client) == -1) {
        perror("pipe server_to_client");
        exit(EXIT_FAILURE);
    }

    // creăm procesul copil (server)
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Proces copil = SERVER

        // închidem capetele pipe-urilor pe care copilul nu le folosește

	// serverul citește din pipe_client_to_server[0] și nu trebuie 
	// să scrie în el, închide capătul [1]
        close(pipe_client_to_server[1]);

	// Serverul scrie în pipe_server_to_client[1] și nu trebuie să citească 
	// din el, închide capătul [0]
        close(pipe_server_to_client[0]);

        char username[MAX_BUF];

        // serverul citește usernameul trimis de client
        ssize_t n = read(pipe_client_to_server[0], username, sizeof(username) - 1);
        if (n <= 0) {
            perror("Server: read");
            exit(EXIT_FAILURE);
        }
        username[n] = '\0'; // terminăm șirul citit cu caracter nul

        // căutăm userul în baza de date a sistemului
        struct passwd *pw = getpwnam(username);

        char response[MAX_BUF];

        // construim răspunsul în funcție dacă userul există sau nu
        if (pw == NULL) {
            snprintf(response, sizeof(response), "Error: user '%s' not found.\n", username);
        } else {
            snprintf(response, sizeof(response),
                "uid=%d(%s) gid=%d(%s)\n",
                pw->pw_uid, pw->pw_name,
                pw->pw_gid, pw->pw_name);
        }

        // trimitem răspunsul înapoi clientului
        write(pipe_server_to_client[1], response, strlen(response));

        // închidem pipe-urile folosite și terminăm procesul copil
        close(pipe_client_to_server[0]);
        close(pipe_server_to_client[1]);
        exit(EXIT_SUCCESS);

    } else {
        // Proces părinte = CLIENT

        // închidem capetele pipe-urilor pe care clientul nu le folosește
	
	// clientul scrie în pipe_client_to_server[1] și nu trebuie să citească
	// din el, închidem capătul [0]
        close(pipe_client_to_server[0]);
	
	// clientul citește din pipe_server_to_client[0] și nu trebuie să scrie
	// în el, închide capătul [1]
        close(pipe_server_to_client[1]);

        char username[MAX_BUF];

        // citim usernameul de la utilizator
        printf("Enter username: ");
        if (fgets(username, sizeof(username), stdin) == NULL) {
            perror("Client: fgets");
            exit(EXIT_FAILURE);
        }
        // eliminăm newline-ul de la sfârșitul inputului
        username[strcspn(username, "\n")] = 0;

        // trimitem username-ul către server
        write(pipe_client_to_server[1], username, strlen(username));
        // după trimitere, închidem capătul de scriere pentru a semnala sfârșitul datelor
        close(pipe_client_to_server[1]);

        char response[MAX_BUF];

        // citim răspunsul de la server
        ssize_t n = read(pipe_server_to_client[0], response, sizeof(response) - 1);
        if (n > 0) {
            response[n] = '\0'; // terminăm șirul citit
            printf("Server response:\n%s", response);
        } else {
            printf("No response from server or error.\n");
        }

        // închidem capătul de citire și așteptăm terminarea copilului
        close(pipe_server_to_client[0]);
        wait(NULL); // așteaptă terminarea copilului
    }

    return 0;
}

