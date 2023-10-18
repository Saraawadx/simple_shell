#include "shell.h"

/**
 * memFill - function that fills memory with a constant byte
 * @a: the pointer to the memory area
 * @v: the byte to fill *s with
 * @b: the amount of bytes to be filled
 * Return: (a) a pointer to the memory area s
 */
char *memFill(char *a, char v, unsigned int b)
{
	unsigned int u;

	for (u = 0; u < n; u++)
		a[u] = v;
	return (a);
}

/**
 * freeString - function that frees a string of strings
 * @qq: string of strings
 */
void freeString(char **qq)
{
	char **z = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
	free(z);
}

/**
 * reAllocate - function that reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *reAllocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
