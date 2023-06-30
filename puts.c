#include "shell.h"

/**
 * _eputchar - putchar
 * @c: char
 * Return: int
 */
int _eputchar(char c)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 * _eputs - puts
 * @str: string
 */
void _eputs(char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
		_eputchar(str[i]);
}

/**
 * _putfd - put
 * @c: char
 * @fd: descript
 * Return: int
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[1024];

	if (c == 1 || i >= 1024)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - put
 * @str: str
 * @fd: descript
 * Return: int
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
		i += _putfd(*str++, fd);
	return (i);
}
