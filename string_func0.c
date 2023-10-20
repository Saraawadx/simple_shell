#include "shell.h"

/**
 * stringLen - function that returns the length of a string
 * @a: the string whose length to check
 *
 * Return: integer length of string
 */
int stringLen(char *a)
{
	int u = 0;

	if (!a)
		return (0);

	while (*a++)
		u++;
	return (u);
}

/**
 * stringComp - function that performs comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: int
 */
int stringComp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * needleStarts - function that checks if needle starts with haystack
 * @hay_stack: pointer to string to search
 * @needle: the substring to find
 *
 * Return: address of next char of hay_stack or NULL
 */
char *needleStarts(const char *hay_stack, const char *needle)
{
	while (*needle)
		if (*needle++ != *hay_stack++)
			return (NULL);
	return ((char *)hay_stack);
}

/**
 * concatStrings - function that concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *concatStrings(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
