#include "shell.h"

void shell()
{
	char buffer[BUFFER_SIZE];

	while(1)
	{
		write(1, "$ ", 2);
		char* input = _getline();
		strcpy(buffer, input);
		_strtok(input);

		_fork(input);
		free(input);
	}
}
