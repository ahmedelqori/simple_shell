#include "shell.h"

/**
 * copy_info - copies the  information to create
 * a new env or alias
 * @name: name of env or alias
 * @value: value of env or alias
 *
 * Return: returns new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @dataSh: data structure for environ
 * Return: nothing to return
 */
void set_env(char *name, char *value, data_shell *dataSh)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; dataSh->_environ[i]; i++)
	{
		var_env = _strdup(dataSh->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(dataSh->_environ[i]);
			dataSh->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	dataSh->_environ = _reallocdpr(dataSh->_environ, i, sizeof(char *) * (i + 2));
	dataSh->_environ[i] = copy_info(name, value);
	dataSh->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares environment variables names
 * with the name passed.
 * @dataSh: relevant for env name and value
 *
 * Return: returns 1 on success.
 */
int _setenv(data_shell *dataSh)
{

	if (dataSh->args[1] == NULL || dataSh->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(dataSh->args[1], dataSh->args[2], dataSh);

	return (1);
}

/**
 * _unsetenv - deletes an environment variable
 *
 * @datash: relevant data for env name
 *
 * Return: returns 1 on success.
 */
int _unsetenv(data_shell *datash);
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (dataSh->args[1] == NULL)
	{
		get_error(dataSh, -1);
		return (1);
	}
	k = -1;
	for (i = 0; dataSh->_environ[i]; i++)
	{
		var_env = _strdup(dataSh->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, dataSh->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(dataSh, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; dataSh->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = dataSh->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(dataSh->_environ[k]);
	free(dataSh->_environ);
	dataSh->_environ = realloc_environ;
	return (1);
}
