#include "shell.h"

/**
 * _exithandler - exit
 * @data: data
 * Return: 0
 */
int _exithandler(data_t *data)
{
	int exitstatus;

	if (strcmp(data->argv[0], "exit") == 0)
	{
		if (data->argc > 2)
		{
			printf("Invalid num of args\n");
			return (0);
		}
		else if (data->argc == 2)
		{
			exitstatus = atoi(data->argv[1]);
			if (exitstatus == 0 && strcmp(data->argv[1], "0") == 0)
				exit(exitstatus);
		}
		else
			exit(0);
	}
	return (0);
}
