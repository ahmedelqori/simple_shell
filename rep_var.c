#include "shell.h"

/**
 * check_env - checks if the typed variable is an environment variable
 *
 * @he: head of linked list
 * @in: represents input string
 * @data: representsdata structure
 * Return: nothing to return
 */
void check_env(rd_var **he, char *in, data_shell *data)
{
	int row, chhr, b, lenval;
	char **_env;

	_env = data->_environ;
	for (row = 0; _env[row]; row++)
	{
		for (b = 1, chr = 0; _envr[row][chhr]; chhr++)
		{
			if (_env[row][chhr] == '=')
			{
				lenval = _strlen(_env[row] + chhr + 1);
				add_rdvar_node(he, b, _env[row] + chhr + 1, lenval);
				return;
			}

			if (in[b] == _env[row][chhr])
				n++;
			else
				break;
		}
	}

	for(b = 0; in[b]; b++)
	{
		if (in[b] == ' ' || in[b] == '\t' || in[b] == ';' || in[b] == '\n')
			break;
	}

	add_rdvar_node(h, j, NULL, 0);
}

/**
 * check_vars - check if the variable typed is $$ or $?
 *
 * @he: head of the linked list
 * @in: represents input string
 * @sts: last status of the Shell
 * @data:represents data structure
 * Return: nothing to return
 */
int check_vars(rd_var **he, char *in, char *sts, data_shell *data)
{
	int i, lsts, lpd;

	lsts = _strlen(sts);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rdvar_node(h, 2, st, lsts), i++;
			else if (in[i + 1] == '$')
				add_rdvar_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rdvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rdvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rdvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rdvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rdvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: represents input string
 * @new_input: replaced input string. 
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(rd_var **head, char *input, char *new_input, int nlen)
{
	rd_var *index;
	int i, j, k;

	index = *head;
	for (b = i = 0; i < nlen; i++)
	{
		if (input[b] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_input[i] = input[j];
				b++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					b++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					new_input[i] = index->value[k];
					i++;
				}
				b += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_input[i] = input[j];
			b++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into variables 
 *
 * @input: input string
 * @datash: data structure
 * Return: returns eplaced string
 */
char *rep_var(char *input, data_shell *dataSh)
{
	rd_var *head, *index;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(dataSh->status);
	head = NULL;

	olen = check_vars(&head, input, status, dataSh);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	nlen = 0;

	while (index != NULL)
	{
		nlen += (index->len_val - index->len_var);
		index = index->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
