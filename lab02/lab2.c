#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter programs to run.\n"
           "> ");
    // Read the user input using getline.
    ssize_t nread = getline(&line, &len, stdin);

    // Linefeed: \n.getline() mess up execl().
    if (line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
    }

    pid_t pid = fork();
    // Child process
    // If execl() succeeds, become the new program
    if (pid == 0) {
      execl(line, line, NULL);
      printf("Exec failure");
      exit(1);
    } else {
      // Parent process
      // Waits for the child to finish to loop.
      waitpid(pid, NULL, 0);
    }
  }
  free(line);
  return 0;
}
