#include "shell.h"

/**
 * isCharChain - Function that test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @q: address of current position in buffer
 *
 * Return: 1 if char is chain delimeter, 0 otherwise
 */
int isCharChain(info_t *info, char *buff, size_t *q)
{
	size_t k = *q;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buff[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[k] == '&' && buff[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0 nul
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = k;
	return (1);
}

/**
 * ifCheckChain - function that chains when checked based on last
 * status
 * @info: the parameter struct
 * @buff: the char buffer
 * @q: address of current position in buffer
 * @u: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void ifCheckChain(info_t *info, char *buff, size_t *q, size_t u, size_t len)
{
	size_t k = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[u] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[u] = 0;
			k = len;
		}
	}

	*q = k;
}

/**
 * replaceAlias - Function that replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(info_t *info)
{
	int u;
	list_t *node;
	char *q;

	for (u = 0; u < 10; u++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		q = _strchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * replaceVars - function that replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVars(info_t *info)
{
	int u = 0;
	list_t *node;

	for (u = 0; info->argv[u]; u++)
	{
		if (info->argv[u][0] != '$' || !info->argv[u][1])
			continue;

		if (!_strcmp(info->argv[u], "$?"))
		{
			replaceString(&(info->argv[u]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[u], "$$"))
		{
			replaceString(&(info->argv[u]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[u][1], '=');
		if (node)
		{
			replaceString(&(info->argv[u]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[u], _strdup(""));

	}
	return (0);
}

/**
 * replaceString - Function that replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
