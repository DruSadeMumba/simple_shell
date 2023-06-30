#include "shell.h"

/**
 * _cmd - cmd
 * @data: data
 * @path: path
 * Return: 0
 */
int _cmd(data_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * _dup - dup
 * @pathstr: str
 * @start: start
 * @stop: stop
 * Return: buf
 */
char *_dup(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i, k;

	for (k = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}
	buf[k] = 0;
	return (buf);
}

/**
 * _path - path
 * @data: data
 * @pathstr: str
 * @cmd: cmd
 * Return: char
 */
char *_path(data_t *data, char *pathstr, char *cmd)
{
	int i = 0, x = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((strlen(cmd) > 2) && _firstchar(cmd, "./"))
	{
		if (_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _dup(pathstr, x, i);
			if (!*path)
				strcat(path, cmd);
			else
			{
				strcat(path, "/");
				strcat(path, cmd);
			}
			if (_cmd(data, path))
				return (path);
			if (!pathstr[i])
				break;
			x = i;
		}
		i++;
	}
	return (NULL);
}

