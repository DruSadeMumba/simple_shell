#include "shell.h"

/**
 * __free - free
 * @ptr: ptr
 * Return: 0
 */
int __free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _free - free
 * @pp: char
 */
void _free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp++)
		free(*pp++);
	free(a);
}

/**
 * _realloc - realloc
 * @ptr: ptr
 * @osize: old
 * @nsize: new
 * Return: p
 */
void *_realloc(void *ptr, unsigned int osize, unsigned int nsize)
{
	char *p;

	if (!ptr)
		return (malloc(nsize));
	if (!nsize)
		return (free(ptr), NULL);
	if (nsize == osize)
		return (ptr);
	p = malloc(nsize);
	if (!p)
		return (NULL);
	osize = osize < nsize ? osize : nsize;
	while (osize--)
		p[osize] = ((char *)ptr)[osize];
	free(ptr);
	return (p);
}
