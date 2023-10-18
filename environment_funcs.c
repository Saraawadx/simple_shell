#include "shell.h"

/**
 * my_env - prints the current environment
 * @info: structure input
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @info: structure input
 * @name: environment name
 *
 * Return: NULL or value
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *i;

	while (node)
	{
		i = starts_with(node->str, name);
		if (i && *i)
			return (i);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initialize or modify environment variable
 * @info: structure input
 *  Return: Always 0
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int my_unsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * add_env_list - a function to populate environment liked list
 * @info: structure input
 * Return: Always 0
 */
int add_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
