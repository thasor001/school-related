#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	printf("Number of arguments : %i\n", argc);
	int rc;	 	// Child PID

	// For loop that goes through all the arguments.
	for(int i = 1; i < argc; i++) {
		rc = fork();
		// rc < 0 means that the fork failed.
		if (rc < 0) {
			printf("Fork failed\n");
			exit(1);
		// rc == 0, means that it is the child that is running.
		} else if (rc == 0) {
			// running program cowsay with arguments, argv[i].
			char *myargs[3];
			myargs[0] = strdup("cowsay");
			myargs[1] = argv[i];
			myargs[2] = NULL;
			execvp(myargs[0], myargs);
		// else means that rc > 0, this means that it is a parent process.
		} else {
			// wait(NULL) waits for the child process of the parent to finish.
			wait(NULL);
		}
	}

	return 0;
}
