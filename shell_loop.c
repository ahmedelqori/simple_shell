#include "shell.h"

/**
 * without_comment - deletes comments from the input string. 
 *
 * @in: represents input string
 * Return: returns input without comments
 */
char *without_comment(char *in)
{
	int i, upt_to;

	upt_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				upt_to = i;
		}
	}

	if (upt_to != 0)
	{
		in = _realloc(in, i, upt_to + 1);
		in[upt_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Loop of the shell
 * @datash: relevant for argv, input and arguments. 
 *
 * Return: nothing to return.
 */
void shell_loop(data_shell *dataSh)
{
	int lup, i_eof;
	char *input;

	lup = 1;
	while (lup == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(dataSh, input) == 1)
			{
				dataSh->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, dataSh);
			lup = split_commands(dataSh, input);
			dataSh->counter += 1;
			free(input);
		}
		else
		{
			lup = 0;
			free(input);
		}
	}
}
