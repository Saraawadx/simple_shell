#include "shell.h"

/**
 * copyString - function that copies a string
 * @dest: points to the destination
 * @src: points to the source
 *
 * Return: pointer to destination
 */
char *copyString(char *dest, char *src)
{
	int u = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[u])
	{
		dest[u] = src[u];
		u++;
	}
	dest[u] = 0;
	return (dest);
}

/**
 * dupString - function that duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *dupString(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 * inputString - function that prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void inputString(char *str)
{
	int u = 0;

	if (!str)
		return;
	while (str[u] != '\0')
	{
		_putchar(str[u]);
		u++;
	}
}

/**
 * inputChar - function that writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and err is set.
 */
int inputChar(char c)
{
	static int u;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(1, buff, u);
		u = 0;
	}
	if (c != BUF_FLUSH)
		buff[u++] = c;
	return (1);
}
