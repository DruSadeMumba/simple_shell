#include "shell.h"

/**
 * _isdelimiter - delimiter
 * @c: char
 * @del: delim
 * Return: 0
 */
int _isdelimiter(char c, char *del)
{
	while (*del)
		if (*del++ == c)
			return (1);
	return (0);
}

/**
 * _firstchar - first char
 * @c: char
 * @a: char
 * Return: char
 */
char *_firstchar(const char *c, const char *a)
{
	while (*a)
		if (*a++ != *c++)
			return (NULL);
	return ((char *)c);
}

/**
 * _puts - puts
 * @str: string
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - putchar
 * @c: char
 * Return: int
 */
int _putchar(char c)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 * _strtok - split string
 * @str: string
 * @d: char
 * Return: char
 */
char **_strtok(char *str, char *d)
{
	int i, j, k, m, num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_isdelimiter(str[i], d) && (_isdelimiter(str[i + 1], d) || !str[i + 1]))
			num++;
	if (num == 0)
		return (NULL);
	s = malloc(sizeof(char *) * (1 + num));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (_isdelimiter(str[i], d))
			i++;
		k = 0;
		while (!_isdelimiter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc(sizeof(char) * (k + 1));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
