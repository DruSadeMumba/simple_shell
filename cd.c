#include "shell.h"

/**
 * _cd - cd
 * @data: data
 * Return: 1
 */
int _cd(data_t *data)
{
	char *s, *dir = NULL, buffer[1024];
	int x;
	char *home = _getenv(data, "HOME="), *oldpwd = _getenv(data, "OLDPWD=");

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("Error 3\n");
	if (!data->argv[1] || strcmp(data->argv[1], "~") == 0)
	{
		dir = home;
		if (!dir)
			x = chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			x = chdir(dir);
	} else if (strcmp(data->argv[1], "-") == 0)
	{
		if (!oldpwd)
		{
			_puts(s);
			putchar('\n');
			return (1);
		}
		_puts(oldpwd);
		putchar('\n');
		x = chdir((dir = oldpwd) ? dir : "/");
	} else
		x = chdir(data->argv[1]);
	if (x == -1)
	{
		_printerr(data, "can't cd to ");
		_eputs(data->argv[1]), _eputchar('\n');
	} else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", s);
	}
	return (0);
}

/**
 * _help - help
 * @data: data
 * Return: 0
 */
int _help(data_t *data)
{
	(void)data;
	printf("**COMMAND LIST**\n"
			"alias\n"
			"cd\n"
			"env\n"
			"exit\n"
			"history\n"
			"ls\n"
			"pwd\n"
			"setenv\n"
			"unsetenv\n");
	return (0);
}

/**
 * _history - hist
 * @data: data
 * Return: 0
 */
int _history(data_t *data)
{
	_printlist(data->hist);
	return (0);
}

/**
 * _comments - #
 * @buf: char
 */
void _comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
