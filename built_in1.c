#include "shell.h"

/**
 * my_history - displays history
 * @info: structure input
 *  Return: Always 0
 */
int my_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: structure input
 * @str: string input
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *i, c;
	int del;

	i = _strchr(str, '=');
	if (!i)
		return (1);
	c = *i;
	*i = 0;
	del = deleteNode_byIndex(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*i = c;
	return (del);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *i;

	i = _strchr(str, '=');
	if (!i)
		return (1);
	if (!*++i)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (addNodeEnd(&(info->alias), str, 0) == NULL);
}

/**
 * alias_print - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_print(list_t *node)
{
	char *i = NULL, *a = NULL;

	if (node)
	{
		i = _strchr(node->str, '=');
		for (a = node->str; a <= i; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(i + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @info: structure input
 *  Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node_ptr = NULL;

	if (info->argc == 1)
	{
		node_ptr = info->alias;
		while (node_ptr)
		{
			alias_print(node_ptr);
			node_ptr = node_ptr->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			alias_print(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
