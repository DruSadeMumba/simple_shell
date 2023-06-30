#include "shell.h"

/**
 * _printd - print
 * @input: int
 * @fd: descriptor
 * Return: int
 */
int _printd(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int j, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		j = -input;
		__putchar('-');
		count++;
	}
	else
		j = input;
	current = j;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (j / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * _printerr - print
 * @data: data
 * @str: str
 */
void _printerr(data_t *data, char *str)
{
	_eputs(data->fname);
	_eputs(": ");
	_printd(data->count, STDERR_FILENO);
	_eputs(": ");
	_eputs(data->argv[0]);
	_eputs(": ");
	_eputs(str);
}

/**
 * _convertint - convert
 * @num: num
 * @base: int
 * @flags: int
 * Return: char
 */
char *_convertint(long int num, int base, int flags)
{
	static char *str, buffer[50];
	char sign = 0, *ptr;
	unsigned long n = num;

	if (!(flags & 2) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	str = flags & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = str[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
