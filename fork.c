#include "shell.h"

void _fork(char* buffer)
{
        buffer[strcspn(buffer, "\n")] = '\0';

	if (strlen(buffer) == 0 || strspn(buffer, " \t\n") == strlen(buffer))
	{
		_print("Nothing was entered\n");
		exit(EXIT_SUCCESS);
	}

	if (strcmp(buffer, "exit") == 0)
	{
		printf("you exited\n");
		exit(EXIT_SUCCESS);
	}

        pid_t pid = fork();

        if (pid < 0){
            fprintf(stderr, "Fork Failed");
        }

        else if(pid == 0)
	{
            execlp(buffer, buffer, NULL);
            fprintf(stderr, "Command '%s' not availabe\n", buffer);
            exit(EXIT_FAILURE);
        }
        else{
            int status;
            waitpid(pid, &status, 0);
        }
}
