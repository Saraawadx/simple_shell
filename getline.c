#include "shell.h"

char* _getline()
{
	char* buffer = NULL;
	size_t size = 0;

	getline(&buffer, &size, stdin);
	return (buffer);
}
