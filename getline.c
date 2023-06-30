#include "shell.h"

/**
 * _input - input
 * @data: data
 * @buf: buf
 * @len: len
 * Return: n
 */
ssize_t _input(data *data, char **buf, size_t *len)
{
	ssize_t n = 0;
	size_t lens = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _handler);
#if GET_LINE
		n = getline(buf, &lens, stdin);
#else
		n = _getline(data, buf, &lens);
#endif
		if (n > 0)
		{
			if ((*buf)[n - 1] == '\n')
			{
				(*buf)[n - 1] = '\0';
				n--;
			}
			data->lineflags = 1;
			_comments(*buf);
			_historylist(data, *buf, data->histcount++);
			*len = n;
			data->cmdbuf = buf;
		}
	}
	return (n);
}

/**
 * _getinput - getinput
 * @data: data
 * Return: n
 */
ssize_t _getinput(data_t *data)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t n;
	char **buf_p = &(data->arg), *p;

	_putchar(-1);
	n = _input(data, &buf, &len);
	if (n == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		_checkchain(data, buf, &j, i, len);
		while (j < len)
		{
			if (_ischain(data, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->cbt = 0;
		}
		*buf_p = p;
		return (strlen(p));
	}
	*buf_p = buf;
	return (n);
}

/**
 * _read - read
 * @data: *data
 * @buf: buf
 * @i: i
 * Return: n
 */
ssize_t _read(data_t *data, char *buf, size_t *i)
{
	ssize_t n;

	if (*i)
		return (0);
	n = read(data->readfd, buf, 1024);
	if (n >= 0)
		*i = n;
	return (n);
}

/**
 * _getline - getline
 * @data: data
 * @ptr: ptr
 * @lens: len
 * Return: 0
 */
int _getline(data_t *data, char **ptr, size_t *lens)
{
	static char buf[1024];
	static size_t i, len;
	size_t k;
	ssize_t n, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && lens)
		s = *lens;
	if (i == len)
		i = len = 0;
	n = _read(data, buf, &len);
	if (n == -1 || (n == 0 && len == 0))
		return (-1);
	c = strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		strncat(new_p, buf + i, k - i);
	else
		strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (lens)
		*lens = s;
	*ptr = p;
	return (s);
}

/**
 * _handler - handler
 * @num: num
 */
void _handler(int num)
{
	(void)num;
	printf("\n#cisfun$ ");
	_putchar(-1);
}
