#include "shell.h"

/**
 * exit_shell - exits the shell
 *
 * @datash: relevant data  for status and arguments
 * Return: returns 0 on success.
 */
int exit_shell(data_shell *dataSh)
{
	unsigned int urstatus;
	int is_digit;
	int str_len;
	int lar_number;

	if (dataSh->args[1] != NULL)
	{
		urstatus = _atoi(dataSh->args[1]);
		is_digit = _isdigit(dataSh->args[1]);
		str_len = _strlen(dataSh->args[1]);
		lar_number = urstatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || lar_number)
		{
			get_error(dataSh, 2);
			dataSh->status = 2;
			return (1);
		}
		dataSh->status = (urstatus % 256);
	}
	return (0);
}
