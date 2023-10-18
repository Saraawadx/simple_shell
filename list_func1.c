#include "shell.h"

/**
 * listLen - function that determines length of linked list
 * @j: pointer to first node
 *
 * Return: size of list
 */
size_t listLen(const list_t *j)
{
	size_t u = 0;

	while (j)
	{
		j = j->next;
		u++;
	}
	return (u);
}

/**
 * listTo_strings - function that returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listTo_strings(list_t *head)
{
	list_t *node = head;
	size_t u = listLen(head), k;
	char **strs;
	char *str;

	if (!head || !u)
		return (NULL);
	strs = malloc(sizeof(char *) * (u + 1));
	if (!strs)
		return (NULL);
	for (u = 0; node; node = node->next, u++)
	{
		str = malloc(stirngLen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < u; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = copyString(str, node->str);
		strs[i] = str;
	}
	strs[u] = NULL;
	return (strs);
}


/**
 * printList - prints all elements of a list_t linked list
 * @j: pointer to first node
 *
 * Return: size of list
 */
size_t printList(const list_t *j)
{
	size_t u = 0;

	while (j)
	{
		inputString(convert_number(h->num, 10, 0));
		inputChar(':');
		inputChar(' ');
		inputString(h->str ? h->str : "(nil)");
		inputString("\n");
		j = j->next;
		u++;
	}
	return (u);
}

/**
 * nodeStarts_pre - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodeStarts_pre(list_t *node, char *prefix, char c)
{
	char *q = NULL;

	while (node)
	{
		q = neddleStarts(node->str, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * nodeIndex - funtion that gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t nodeIndex(list_t *head, list_t *node)
{
	size_t u = 0;

	while (head)
	{
		if (head == node)
			return (u);
		head = head->next;
		u++;
	}
	return (-1);
}
