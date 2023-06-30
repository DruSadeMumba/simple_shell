#include "shell.h"

/**
 * _getnode - get
 * @head: head
 * @node: node
 * Return: int
 */
ssize_t _getnode(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * _nodestart - start
 * @node: node
 * @prev: previous
 * @c: char
 * Return: list
 */
list_t *_nodestart(list_t *node, char *prev, char c)
{
	char *p = NULL;

	while (node)
	{
		p = _firstchar(node->str, prev);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _addendnode - add
 * @head: head
 * @str: string
 * @num: int
 * Return: list
 */
list_t *_addendnode(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * _deletenode - delete
 * @head: head
 * @pos: int
 * Return: int
 */
int _deletenode(list_t **head, unsigned int pos)
{
	list_t *node, *prev;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!pos)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == pos)
		{
			prev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev = node;
		node = node->next;
	}
	return (0);
}
