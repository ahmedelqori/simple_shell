#include "shell.h"

/**
 * free_data - frees the  data structure
 *
 * @dataSh: represents data structure
 * Return: nothing to return
 */
void free_data(data_shell *dataSh)
{
	unsigned int i;

	for (i = 0; dataSh->_environ[i]; i++)
	{
		free(dataSh->_environ[i]);
	}

	free(dataSh->_environ);
	free(datash->pid);
}

/**
 * set_data - Initializes the data structure
 *
 * @dataSh: represents the data structure
 * @argv: represents the argument vector
 * Return: nothing to return
 */
void set_data(data_shell *dataSh, char **argv)
{
	unsigned int i;

	dataSh->argv = argv;
	dataSh->input = NULL;
	dataSh->args = NULL;
	dataSh->status = 0;
	dataSh->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	dataSh->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		dataSh->_environ[i] = _strdup(environ[i]);
	}

	dataSh->_environ[i] = NULL;
	dataSh->pid = aux_itoa(getpid());
}

/**
 * main - Entry point/starting point
 *
 * @acnt: argument count
 * @argv: argument vector
 *
 * Return: returns 0 on success.
 */
int main(int acnt, char **argv)
{
	data_shell dataDh;
	(void) acnt;

	signal(SIGINT, get_sigint);
	set_data(&dataSh, arv);
	shell_loop(&dataSh);
	free_data(&dataSh);
	if (dataSh.status < 0)
		return (255);
	return (dataSh.status);
}
