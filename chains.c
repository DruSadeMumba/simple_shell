#include "shell.h"

/**
 * _ischain - chain
 * @data: data
 * @buf: buf
 * @p: size
 * Return: 1
 */
int _ischain(data_t *data, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data->cbt = 1;
	} else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->cbt = 2;
	} else if (buf[j] == ';')
	{
		buf[j] = 0;
		data->cbt = 3;
	} else
		return (0);
	*p = j;
	return (1);
}

/**
 * _checkchain - check chain
 * @data: dat
 * @buf: buf
 * @p: size
 * @i: size
 * @len: size
 */
void _checkchain(data_t *data, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (data->cbt == 2)
	{
		if (data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (data->cbt == 1)
	{
		if (!data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * _changechains - change
 * @data: data
 * Return: int
 */
int _changechains(data_t *data)
{
	int i;
	list_t *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;
		if (!strcmp(data->argv[i], "$?"))
			_changestrings(&(data->argv[i]),
					strdup(_convertint(data->status, 10, 0)));
		continue;
		if (!strcmp(data->argv[i], "$$"))
		{
			_changestrings(&(data->argv[i]),
					strdup(_convertint(getpid(), 10, 0)));
			continue;
		}
		node = _nodestart(data->env, &data->argv[i][1], '=');
		if (node)
		{
			_changestrings(&(data->argv[i]),
					strdup(strchr(node->str, '=') + 1));
			continue;
		}
		_changestrings(&data->argv[i], strdup(""));
	}
	return (0);
}

/**
 * _changestrings - change
 * @old: str
 * @new: new
 * Return: 1
 */
int _changestrings(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
