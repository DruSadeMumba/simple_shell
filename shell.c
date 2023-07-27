#include "shell.h"

/**
 * mode - mode
 * @data: data
 * Return: int
 */
int mode(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * _findbic - find
 * @data: data
 * Return: int
 */
int _findbic(data_t *data)
{
	int i, ret = -1;
	bic_t bt[] = {
		{"exit", _exithandler},
		{"env", _env},
		{"help", _help},
		{"history", _history},
		{"setenv", _setsenv},
		{"unsetenv", _unsetsenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};
	for (i = 0; bt[i].type; i++)
		if (strcmp(data->argv[0], bt[i].type) == 0)
		{
			data->count++;
			ret = bt[i].func(data);
			break;
		}
	return (ret);
}

/**
 * _forkcmd - fork
 * @data: dat
 */
void _forkcmd(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("not found\n");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, _getenviron(data)) == -1)
		{
			_freedata(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				_printerr(data, "not found\n");
		}
	}
}

/**
 * _findcmd- fnd
 * @data: data
 */
void _findcmd(data_t *data)
{
	char *apath = NULL, *paths = _getenv(data, "PATH=");
	int i, k;

	data->path = data->argv[0];
	if (data->lineflags == 1)
	{
		data->count++;
		data->lineflags = 0;
	}
	for (i = 0, k = 0; data->arg[i]; i++)
	{
		if (!_isdelimiter(data->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;
	apath = _path(data, paths, data->argv[0]);
	if (apath)
	{
		data->path = apath;
		_forkcmd(data);
	} else
	{
		if ((mode(data) || paths || data->argv[0][0] == '/')
				&& _cmd(data, data->argv[0]))
			_forkcmd(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			_printerr(data, "not found\n");
		}
	}
}

/**
 * handlers - handles
 * @data: data
 * @av: vector
 * Return: int
 */
int handlers(data_t *data, char **av)
{
	ssize_t n = 0;
	int ret = 0;

	while (n != -1 && ret != -2)
	{
		_cleardata(data);
		if (mode(data))
			_eputs("#cisfun$ ");
		_eputchar(-1);
		n = _getinput(data);
		if (n != -1)
		{
			_setdata(data, av);
			ret = _findbic(data);
			if (ret == -1)
				_findcmd(data);
		}
		else if (mode(data))
			putchar('\n');
		_freedata(data, 0);
	}
	_writehistory(data);
	_freedata(data, 1);
	if (!mode(data) && data->status)
		exit(data->status);
	if (ret == -2)
	{
		if (data->errnum == -1)
			exit(data->status);
		exit(data->errnum);
	}
	return (ret);
}

