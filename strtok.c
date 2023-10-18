#include "shell.h"

char* _strtok(char* input)
{
	char* str = input;
	char* delim = " ";
	char* token;

	token = strtok(str, delim);
	while (token)
	{
		printf("%s", token);
		token = strtok(NULL, delim);
	}
	return (str);
}
