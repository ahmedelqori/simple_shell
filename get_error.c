#include "shell.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @dataSh: data structure that contains arguments
 * @errval: represent error value
 * Return: returns error
 */
int get_error(data_shell *dataSh, int errval)
{
	char *error;

	switch (errval)
	{
	case -1:
		error = error_env(dataSh);
		break;
	case 126:
		error = error_path_126(dataSh);
		break;
	case 127:
		error = error_not_found(dataSh);
		break;
	case 2:
		if (_strcmp("exit", dataSh->args[0]) == 0)
			error = error_exit_shell(dataSh);
		else if (_strcmp("cd", dataSh->args[0]) == 0)
			error = error_get_cd(dataSh);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = errval;
	return (errval);
}
