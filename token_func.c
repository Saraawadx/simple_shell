#include "shell.h"

/**
 * **strSplit - function that splits a string into words.
 * Repeat delimiters are ignored
 * @str: the input string
 * @s: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int u, k, l, n, numwords = 0;
	char **a;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!s)
		s = " ";
	for (u = 0; str[u] != '\0'; u++)
		if (!is_delim(str[u], s) && (is_delim(str[u + 1], s) || !str[u + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	a = malloc((1 + numwords) * sizeof(char *));
	if (!a)
		return (NULL);
	for (u = 0, k = 0; k < numwords; k++)
	{
		while (is_delim(str[u], s))
			u++;
		l = 0;
		while (!is_delim(str[u + l], s) && str[u + l])
			l++;
		a[k] = malloc((l + 1) * sizeof(char));
		if (!a[k])
		{
			for (l = 0; l < k; l++)
				free(a[l]);
			free(a);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			a[k][n] = str[u++];
		a[k][n] = 0;
	}
	a[k] = NULL;
	return (a);
}

/**
 * **strSplit_toWords - function that splits a string into words
 * @str: the input string
 * @s: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strSplit_toWords(char *str, char s)
{
	int u, k, l, n, numwords = 0;
	char **a;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (u = 0; str[u] != '\0'; u++)
		if ((str[u] != s && str[u + 1] == s) ||
				    (str[u] != s && !str[u + 1]) || str[u + 1] == s)
			numwords++;
	if (numwords == 0)
		return (NULL);
	a = malloc((1 + numwords) * sizeof(char *));
	if (!a)
		return (NULL);
	for (u = 0, k = 0; k < numwords; k++)
	{
		while (str[u] == s && str[u] != s)
			u++;
		l = 0;
		while (str[u + l] != s && str[u + l] && str[u + l] != s)
			l++;
		a[k] = malloc((l + 1) * sizeof(char));
		if (!a[k])
		{
			for (l = 0; l < k; l++)
				free(a[l]);
			free(a);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[k][n] = str[u++];
		s[k][n] = 0;
	}
	a[k] = NULL;
	return (a);
}
