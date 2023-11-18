#include "shell.h"

/**
 * error_env - error message for env in get_env.
 * @dataSh: relevant data (counter and arguments). 
 * Return: returns error message.
 */
char *error_env(data_shell *dataSh)
{
	int length;
	char *error;
	char *rev_str;
	char *msg;

	rev_str = aux_itoa(dataSh->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(dataSh->argv[0]) + _strlen(rev_str);
	length += _strlen(dataSh->args[0]) + _strlen(msg) + 4;
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
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_126 - error message for path  failure and denied permission.
 * @datash: relevant data (counter and arguments).
 *
 * Return: returns error string.
 */
char *error_path_126(data_shell *dataSh)
{
	int length;
	char *rev_str;
	char *error;

	rev_str = aux_itoa(dataSh->counter);
	length = _strlen(dataSh->av[0]) + _strlen(rev_str);
	length += _strlen(dataSh->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(rev_str);
		return (NULL);
	}
	_strcpy(error, dataSh->av[0]);
	_strcat(error, ": ");
	_strcat(error, rev_str);
	_strcat(error, ": ");
	_strcat(error, dataSh->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(rev_str);
	return (error);
}
