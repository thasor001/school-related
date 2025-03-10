#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Recursion using Fork, where the recursions wait for their children.
int main(int argc, char *argv[]) {
	// Start the recursion.
	int pid = fork();


	if (pid < 0) {
		printf("\n\nFork Failed\n\n");
		exit(EXIT_FAILURE); // Exit Program
	}

	int level = 1; // set the level

	// First Porgram only has argc = 1.
	// We dont want to use argv[1] which does not exist for level 1 parent.
	// So this only runs for the children of level 1 parent.
	if (argc > 1) {
		level = atoi(argv[1]) + 1;
	}

	printf("This is level %i with pid :%d\n", level, (int) getpid());

	if (level < 5) {
		// Set the level to be char
		char lvl[2];
		lvl[0] = level + '0';
		lvl[1] = '\0';

		// Set new arguments, execvp takes first, the program name; argv[0] so we send that as a argument.
		// Then we send in our own argument, lvl, which is the level of recursion.
		// Finally execvp needs NULL to signify the end of the arguments.
		char *new_argv[] = {argv[0], lvl, NULL};

		// First parameter program to be run, seccond parameter is the arguments that the program takes.
		execvp(argv[0], new_argv);

	}

	return 0;
}



