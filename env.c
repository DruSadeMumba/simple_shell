#include "shell.h"

/**
 * _getenviron - get environ
 * @data: data
 * Return: 0
 */
char **_getenviron(data_t *data)
{
	if (!data->environ || data->cenv)
	{
		data->environ = _ltostr(data->env);
		data->cenv = 0;
	}
	return (data->environ);
}

/**
 * _unsetenv - unset
 * @data: data
 * @var: var
 * Return: 0
 */
int _unsetenv(data_t *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = _firstchar(node->str, var);
		if (p && *p == '=')
		{
			data->cenv = _deletenode(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->cenv);
}

/**
 * _setenv - set env
 * @data: data
 * @var: var
 * @val: value
 * Return: 0
 */
int _setenv(data_t *data, char *var, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !val)
		return (0);
	buf = malloc(strlen(var) + strlen(val) + 2);
	if (!buf)
		return (1);
	strcpy(buf, var);
	strcat(buf, '=');
	strcat(buf, val);
	node = dat->env;
	while (node)
	{
		p = _firstchar(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			data->cenv = 1;
			return (0);
		}
		node = node->next;
	}
	_addendnode(&(data->env), buf, 0);
	free(buf);
	data->cenv = 1;
	return (0);
}
