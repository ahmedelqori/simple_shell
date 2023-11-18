#include "shell.h"

/**
 * is_ckdir - checks ":" if is in the current directory.
 * @path: char pointer character. 
 * @in:  integer pointer of index.
 * Return: returns 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_ckdir(char *path, int *in) 
{
	if (path[*in] == ':')
		return (1);

	while (path[*in] != ':' && path[*in])
	{
		*in += 1;
	}

	if (path[*in])
		*in += 1;

	return (0);
}

/**
 * _which - locates a command
 *
 * @cmd: represents the command name
 * @_environ: global environment variable
 * Return: returns location of the command.
 */
char *_which(char *cmmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmmd, in;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmmd = _strlen(cmmd);
		token_path = _strtok(ptr_path, ":");
		in = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &in))
				if (stat(cmmd, &st) == 0)
					return (cmmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmmd, &st) == 0)
			return (cmmd);
		return (NULL);
	}
	if (cmmd[0] == '/')
		if (stat(cmmd, &st) == 0)
			return (cmmd);
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 *
 * @dataSh: represents data structurse
 * Return: returns 0 if is not an executable, otherwise other number if it does
 */
int is_executable(data_shell *dataSh)
{
	struct stat st;
	int in;
	char *input;

	input = dataSh->args[0];
	for (in = 0; input[in]; in++)
	{
		if (input[in] == '.')
		{
			if (input[in + 1] == '.')
				return (0);
			if (input[in + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && in != 0)
		{
			if (input[in + 1] == '.')
				continue;
			in++;
			break;
		}
		else
			break;
	}
	if (in == 0)
		return (0);

	if (stat(input + in, &st) == 0)
	{
		return (in);
	}
	get_error(dataSh, 127);
	return (-1);
}

/**
 * check_error_cmmd - verifies if user has permissions to access
 *
 * @dir: destination of the directory
 * @dataSh: data structures
 * Return: returns 1 if there is an error, 0 otherwise 
 */
int check_error_cmmd(char *dir, data_shell *dataSh)
{
	if (dir == NULL)
	{
		get_error(dataSh, 127);
		return (1);
	}

	if (_strcmp(dataSh->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(dataSh, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(dataSh->args[0], X_OK) == -1)
		{
			get_error(dataSh, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmmd_exec - executes commands lines
 *
 * @datash: relevant data (args and input)
 * Return: returns 1 on success.
 */
int cmmd_exec(data_shell *datash)
{
	pid_t ppd;
	pid_t wtpd;
	int state;
	int exec;
	char *dir;
	(void) wtpd;

	exec = is_executable(dataSh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(dataSh->args[0], dataSh->_environ);
		if (check_error_cmmd(dir, dataSh) == 1)
			return (1);
	}

	ppd = fork();
	if (ppd == 0)
	{
		if (exec == 0)
			dir = _which(dataSh->args[0], dataSh->_environ);
		else
			dir = dataSh->args[0];
		execve(dir + exec, dataSh->args, dataSh->_environ);
	}
	else if (ppd < 0)
	{
		perror(dataSh->argv[0]);
		return (1);
	}
	else
	{
		do {
			wtpd = waitpid(ppd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	dataSh->status = state / 256;
	return (1);
}
