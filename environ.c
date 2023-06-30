#include "shell.h"

/**
 * _env - env
 * @data: data
 * Return: 0
 */
int _env(data_t *data)
{
	_printslists(data->env);
	return (0);
}

/**
 * _getenv - getenv
 * @data: data
 * @name: env name
 * Return: char
 */
char *_getenv(data_t *data, const char *name)
{
	list_t *node = data->env;
	char *p;

	while (node)
	{
		p = _firstchar(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setsenv - set
 * @data: data
 * Return: 1
 */

int _setsenv(data_t *data)
{
	if (data->argc != 3)
	{
		_eputs("Error: ");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetsenv - unset
 * @data: data
 * Return: 0
 */
int _unsetsenv(data_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_eputs("Error");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		_unsetenv(data, data->argv[i]);
	return (0);
}

/**
 * _envlist - list
 * @data: data
 * Return: 0
 */
int _envlist(data_t *data)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_addendnode(&node, environ[i], 0);
	data->env;
	return (0);
}
