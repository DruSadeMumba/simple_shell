#include "shell.h"

/**
 * _cd - cd
 * @data: data
 * Return: 1
 */
int _cd(data_t *data)
{
	char *s, dir, buffer[1024];
	int x;
	char *home = _getenv(data, "HOME="), *oldpwd = _getenv(data, "OLDPWD=");
	char *pwd = _getenv(data, "PWD=");

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("Error: \n");
	if (!data->argv[1] || strcmp(dat->argv[1], "~") == 0)
	{
		dir = home;
		if (!dir)
			x = chdir((dir = pwd) ? dir : "/");
		else
			x = chdir(dir);
	} else if (strcmp(data->argv[1], "-") == 0)
	{
		if (!olpwd)
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(oldpwd), _putchar('\n');
		x = chdir(dir);
	} else
		x = chdir(data->argv[1]);
	if (x == -1)
	{
		_printerr(data, "Error: ");
		_eputs(data->argv[1]), _eputchar('\n');
	} else
	{
		_setenv(data, "OLDPWD", pwd);
		_setenv(data, "PWD", getcwd(buffer, 1024));
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
	printf("**COMMAND**\n"
			"cd\n"
			"ls\n"
			"exit\n"
			"env\n"
			"pwd\n"
			"unsetenv\n"
			"setenv\n"
			"history\n");
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
