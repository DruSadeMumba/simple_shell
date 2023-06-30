#include "shell.h"

/**
 * main - entry
 * @args: count
 * @argv: vector
 * Return: 0
 */
int main(int args, char **argv)
{
	data_t data[] = { DATA_INIT};
	int fd;

	if (args == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs("Error: ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fd;
	}
	_envlist(data);
	_readhistory(data);
	handlers(data, argv);
	return (EXIT_SUCCESS);
}
