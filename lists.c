#include "shell.h"

/**
 * _llen - len
 * @h: list
 * Return: size
 */
size_t _llen(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _ltostr - str
 * @head: list
 * Return: str
 */
char **_ltostr(list_t *head)
{
	list_t *node = head;
	size_t i = _llen(head), j;
	char **strs, *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * _printlist - print
 * @h: list
 * Return: size
 */
size_t _printlist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		puts(_convertint(h->num, 10, 0));
		putchar(':');
		putchar(' ');
		puts(h->str ? h->str : "(null)");
		puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _printslists - print
 * @h: list
 * Return: size
 */
size_t _printslists(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(null)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _freelist - free
 * @ptr: pointer
 */
void _freelist(list_t **ptr)
{
	list_t *node, *next_node, *head;

	if (!ptr || !*ptr)
		return;
	head = ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ptr = NULL;
}
