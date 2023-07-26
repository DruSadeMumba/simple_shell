#include "shell.h"

/**
 * _exithandler - exit
 * @data: data
 * Return: 0
 */
int _exithandler(data_t *data)
{
	int exitstatus;

	if (data->argv[1])
	{
		exitstatus = atoi(data->argv[1]);
		if (exitstatus == 0 && strcmp(data->argv[1], "0") != 0)
		{
			printf("Invalid input: enter  int\n");
			return (0);
		}
		else if (exitstatus == -1)
		{
			data->status = 2;
			_printerr(data, "Error: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}
		data->errnum = atoi(data->argv[1]);
		return (-2);
	}
	data->errnum = -1;
	return (-2);
}
