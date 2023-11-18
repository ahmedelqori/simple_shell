#include "shell.h"

/**
 * get_help - function that retrieves help messages according builtin command. 
 * @dataSh: data structure arguments and input. 
 * Return: Returns  0
*/
int get_help(data_shell *dataSh)
{

	if (dataSh->args[1] == 0)
		aux_help_general();
	else if (_strcmp(dataSh->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(dataSh->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(dataSh->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(dataSh->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(dataSh->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(dataSh->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(dataSh->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, dataSh->args[0],
		      _strlen(dataSh->args[0]));

	dataSh->status = 0;
	return (1);
}
