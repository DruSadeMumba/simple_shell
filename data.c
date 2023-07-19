#include "shell.h"

/**
 * _cleardata - clear
 * @data: data
 */
void _cleardata(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * _setdata - set
 * @data: data
 * @av: str
 */
void _setdata(data_t *data, char **av)
{
	int i;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = _strtok(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;
		_changealias(data);
		_changechains(data);
	}
}

/**
 * _freedata - free
 * @data: data
 * @all: all
 */
void _freedata(data_t *data, int all)
{
	_free(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmdbuf)
			free(data->arg);
		if (data->env)
			_freelist(&(data->env));
		if (data->hist)
			_freelist(&(data->hist));
		if (data->alias)
			_freelist(&(data->alias));
		_free(data->environ);
		data->environ = NULL;

		__free((void **)data->cmdbuf);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(-1);
	}
}
