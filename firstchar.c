#include "shell.h"

/**
 * _firstchars - first char in string
 * @str: string
 * Return: char
 */
char _firstchars(const char *str)
{
	if (str != NULL)
		return (*str);
	return ('\0');
}
