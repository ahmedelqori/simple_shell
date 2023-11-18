#include "shell.h"

/**
 * cd_shell - changes to current directory
 *
 * @dataSh: relevant data 
 * Return: returns 1 on success
 */
int cd_shell(data_shell *dataSh)
{
	char *dir;
	int isshome, isshome2, issddash;

	dir = dataSh->args[1];

	if (dir != NULL)
	{
		isshome = _strcmp("$HOME", dir);
		isshome2 = _strcmp("~", dir);
		issddash = _strcmp("--", dir);
	}

	if (dir == NULL || !isshome || !isshome2 || !issddash)
	{
		cd_to_home(dataDh);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(dataSh);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(dataSh);
		return (1);
	}

	cd_to_dir(dataSh);

	return (1);
}
