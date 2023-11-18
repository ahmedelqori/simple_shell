#include "shell.h"

/**
 * get_builtin - builtin that pais the command in the arguments
 * @cmmd: represents a command
 * Return: returns function pointer of the builtin command
 */
int (*get_builtin(char *cmmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmmd) == 0)
			break;
	}

	return (builtin[i].f);
}
