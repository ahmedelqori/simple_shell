#include "shell.h"

/**
 * comp_env_name - compares environmental variables names
 * with the name passed.
 * @nmenv: represents name of the environment variable
 * @name: represents name passed
 *
 * Return: returns 0 if are not equal, otherwise another value if they available.
 */
int comp_env_name(const char *nmenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nmenv[i] != nmame[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - gets an environment variable
 * @name:represents name of the environment variable
 * @_environ: represents environment variable
 *
 * Return: returns value of the environment variable if its found, 
 * Otherwise, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, move;

	/* Initialize pointer ptr_env value */
	ptr_env = NULL;
	move = 0;
	/* Compares all environment variables */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		move = comp_env_name(_environ[i], name);
		if (move)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + move);
}

/**
 * _env - prints the evironment variables
 *
 * @dataSh: relevant data .
 * Return: returns 1 on success.
 */
int _env(data_shell *dataSh)
{
	int i, j;

	for (i = 0; dataSh->_environ[i]; i++)
	{

		for (j = 0; dataSh->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, dataSh->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	dataSh->status = 0;

	return (1);
}
