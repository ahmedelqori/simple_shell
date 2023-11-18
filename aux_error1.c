#include "shell.h"

/**
 * strcat_cd - Function to concatenate error message for 'cd'. 
 *
 * @dataSh: relevant data (directory). 
 * @msg: message to be printed. 
 * @error: output message. 
 * @rev_str: line counter. 
 * Return: returns error message. 
 */
char *strcat_cd(data_shell *dataSh, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, dataSh->argv[0]);
	_strcat(error, ": ");
	_strcat(error, rev_str);
	_strcat(error, ": ");
	_strcat(error, dataSh->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = dataSh->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, dataSh->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - Error message for 'cd' command in get_cd. 
 * @dataSh: relevant (directory)
 * Return: returns error message
 */
char *error_get_cd(data_shell *dataSh)
{
	int length, len_id;
	char *error, *rev_str, *msg;

	rev_str = aux_itoa(dataSh->counter);
	if (dataSh->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(dataSh->args[1]);
	}

	length = _strlen(dataSh->av[0]) + _strlen(dataSh->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(rev_str);
		return (NULL);
	}

	error = strcat_cd(dataSh, msg, error, rev_str);

	free(rev_str);

	return (error);
}

/**
 * error_not_found - generic error message for command not found. 
 * @datash: relevant data (counter, arguments)
 * Return: returns error message
 */
char *error_not_found(data_shell *dataSh)
{
	int length;
	char *error;
	char *rev_str;

	rev_str = aux_itoa(dataSh->counter);
	length = _strlen(dataSh->argv[0]) + _strlen(rev_str);
	length += _strlen(dataSh->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(rev_str);
		return (NULL);
	}
	_strcpy(error, dataSh->argv[0]);
	_strcat(error, ": ");
	_strcat(error, rev_str);
	_strcat(error, ": ");
	_strcat(error, dataSh->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(rev_str);
	return (error);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @datash: relevant data (counter and arguments)
 *
 * Return: returns error message
 */
char *error_exit_shell(data_shell *dataSh)
{
	int length;
	char *error;
	char *rev_str;

	rev_str = aux_itoa(dataSh->counter);
	length = _strlen(dataSh->argv[0]) + _strlen(rev_str);
	length += _strlen(dataSh->args[0]) + _strlen(dataSh->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(rev_str);
		return (NULL);
	}
	_strcpy(error, dataSh->argv[0]);
	_strcat(error, ": ");
	_strcat(error, rev_str);
	_strcat(error, ": ");
	_strcat(error, dataSh->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, dataSh->args[1]);
	_strcat(error, "\n\0");
	free(rev_str);

	return (error);
}
