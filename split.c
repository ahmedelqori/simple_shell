#include "shell.h"

/**
 * swap_char - swaps | and & for non-printed characters. 
 *
 * @input: represents input string
 * @boolean: type of swap
 * Return: swapped string
 */
char *swap_char(char *input, int boolean) 
{
	int i;

	if (boolean == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators and command lines in the singly linked lists
 *
 * @head_sl: head of separator list
 * @head_ls: head of command lines list
 * @input: input string
 * Return: nothing to return
 */
void add_nodes(sep_list **head_sl, line_list **head_ls, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_sl, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_sl, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_ls, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - goes to the next command line stored
 *
 * @list_sl: separator list
 * @list_ls: command line list
 * @dataSh: data structure
 * Return: no return
 */
void go_next(sep_list **list_sl, line_list **list_ls, data_shell *dataSh)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && lup_sep)
	{
		if (dataSh->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				lup_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				lup_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !lup_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and then executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: returns 0 to exit and 1 to continue
 */
int split_commands(data_shell *dataSh, char *input)
{

	sep_list *head_sl, *list_s;
	line_list *head_ls, *list_l;
	int lup;

	head_sl = NULL;
	head_ls = NULL;

	add_nodes(&head_sl, &head_ls, input);

	list_s = head_sl;
	list_l = head_ls;

	while (list_l != NULL)
	{
		dataSh->input = list_l->line;
		dataSh->args = split_line(dataSh->input);
		lup = exec_line(dataSh);
		free(dataSh->args);

		if (lup == 0)
			break;

		go_next(&list_s, &list_l, dataSh);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_sl);
	free_line_list(&head_ls);

	if (lup == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: returns spitted string.
 */
char **split_line(char *input)
{
	size_t bffsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOKEN_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bffsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOKEN_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bffsize)
		{
			bsize += TOKEN_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bffsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKEN_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
