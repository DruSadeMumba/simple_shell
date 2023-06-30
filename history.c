#include "shell.h"

/**
 * _gethistory - get hist
 * @data: data
 * Return: char
 */
char *_gethistory(data_t *data)
{
	char *buf, *dir;

	dir = _getenv(data, "HOME=");
	buf = malloc(sizeof(char) * (strlen(dir) + strlen("HIstory") + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	strcpy(buf, dir);
	strcar(buf, "/");
	strcat(buf, "HIstory");
	return (buf);
}

/**
 * _writehistory - write
 * @data: data
 * Return: 0
 */
int _writehistory(dat_t *data)
{
	ssize_t fd;
	char *filename = _gethistory(data);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = data->hist; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(-1, fd);
	close(fd);
	return (1);
}

/**
 * _historynums - num
 * @data: data
 * Return: int
 */
int _historynums(data_t *data)
{
	list_t *node = data->hist;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (data->histcount = i);
}

/**
 * _historylist - list
 * @data: data
 * @buf: buf
 * @linecount: count
 * Return: int
 */
int _historylist(data_t *data, char *buf, int linecount)
{
	list_t *node = NULL;

	if (data->hist)
		node = data->hist;
	_addendnode(&node, buf, linecount);

	if (!data->hist)
		data->hist = node;
	return (0);
}

/**
 * _readhistory - read
 * @data: data
 * Return: 1
 */
int _readhistory(data_t *data)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = _gethistory(data);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			_historylist(data, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		_historylist(data, buf + last, linecount++);
	free(buf);
	data->histcount = linecount;
	while (data->histcount-- >= 4096)
		_deletenode(&(data->hist), 0);
	_historynums(data);
	return (data->histcount);
}

