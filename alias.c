#include "shell.h"

/**
 * _changealias - change
 * @data: data
 * Return: 1
 */
int _changealias(data_t *data)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _nodestart(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = strchr(node->str, '=');
		if (!p)
			return (0);
		p = strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * _unsetalias - unset
 * @data: data
 * @str: string
 * Return: int
 */
int _unsetalias(data_t *data, char *str)
{
	char *p, c;
	int ret;

	p = strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = _deletenode(&(data->alias),
			_getnode(data->alias, _nodestart(data->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _setalias - set
 * @data: data
 * @str: str
 * Return: 0
 */
int _setalias(data_t *data, char *str)
{
	char *p;

	p = strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_unsetalias(data, str));
	_unsetalias(data, str);
	return (_addendnode(&(data->alias), str, 0) == NULL);
}

/**
 * _printalias - print
 * @node: node
 * Return: 1
 */
int _printalias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - alias
 * @data: data
 * Return: 0
 */
int _alias(data_t *data)
{
	int i;
	char *p = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			_printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		p = strchr(data->argv[i], '=');
		if (p)
			_setalias(data, data->argv[i]);
		else
			_printalias(_nodestart(data->alias, data->argv[i], '='));
	}
	return (0);
}

