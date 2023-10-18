#include "shell.h"

char *_print(char *argv)
{
	size_t count = strlen(argv);

	write(1, argv, count);

	return (argv);
}
