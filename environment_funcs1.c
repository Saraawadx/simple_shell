#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listTo_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_env - Remove an environment variable
 * @info: structure input
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int unset_env(info_t *info, char *var)
{
	list_t *node_ptr = info->env;
	size_t i = 0;
	char *ptr;

	if (!node_ptr || !var)
		return (0);

	while (node_ptr)
	{
		ptr = needleStarts(node_ptr->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = deleteNode_byIndex(&(info->env), i);
			i = 0;
			node_ptr = info->env;
			continue;
		}
		node_ptr = node_ptr->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_env - initialize or modify environment
 * @info: structure input
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buffer = malloc(stringLen(var) + stringLen(value) + 2);
	if (!buffer)
		return (1);
	copyString(buffer, var);
	concatStrings(buffer, "=");
	concatStrings(buffer, value);
	node = info->env;
	while (node)
	{
		p = needleStarts(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
