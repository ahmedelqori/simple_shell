#include "shell.h"

/**
 * exec_line - finds builtins and commands
 *
 * @datash: relevant data for arguments 
 * Return: returns 1 on success.
 */
int exec_line(data_shell *dataSh)
{
	int (*builtin)(data_shell *dataSh);

	if (dataSh->args[0] == NULL)
		return (1);

	builtin = get_builtin(dataSh->args[0]);

	if (builtin != NULL)
		return (builtin(dataSh));

	return (cmmd_exec(dataSh));
}
