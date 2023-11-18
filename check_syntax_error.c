#include "shell.h"

/**
 * repeated_char - counts the repetitions of  characters. 
 *
 * @input: input string
 * @in: represents an index. 
 * Return: returns repetitions
 */
int repeated_char(char *input, int in)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, in + 1));

	return (in);
}

/**
 * error_sep_ops - finds syntax errors
 *
 * @input: represents input string
 * @index: represents index
 * @last: last character read
 * Return: returns index of error,0
 * otherwise 
 */
int error_sep_ops(char *input, int in, char last)
{
	int digit_count;

	digit_count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_ops(input + 1, in + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (in);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (in);

		if (last == '|')
		{
			digit_count = repeated_char(input, 0);
			if (digit_count == 0 || digit_count > 1)
				return (in);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (in);

		if (last == '&')
		{
			digit_count = repeated_char(input, 0);
			if (digit_count == 0 || digit_count > 1)
				return (in);
		}
	}

	return (error_sep_ops(input + 1, in + 1, *input));
}

/**
 * first_char - finds index of the first character 
 *
 * @input: represents input string
 * @in: index
 * Return: returns 1 if on error. 0 otherwise 
 */
int first_char(char *input, int *in)
{

	for (*in = 0; input[*in]; *in += 1)
	{
		if (input[*in] == ' ' || input[*in] == '\t')
			continue;

		if (input[*in] == ';' || input[*in] == '|' || input[*in] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @dataSh: represents data structures
 * @input: represents input string
 * @in: index of the error
 * @boolean: controls msg error
 * Return: nothing to return
 */
void print_syntax_error(data_shell *dataSh, char *input, int in, int boolean)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[in] == ';')
	{
		if (boolean == 0)
			msg = (input[in + 1] == ';' ? ";;" : ";");
		else
			msg = (input[in - 1] == ';' ? ";;" : ";");
	}

	if (input[in] == '|')
		msg = (input[in + 1] == '|' ? "||" : "|");

	if (input[in] == '&')
		msg = (input[in + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(dataSh->digit_counter);
	length = _strlen(dataSh->argv[0]) + _strlen(digit_counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(digit_counter);
		return;
	}
	_strcpy(error, dataSh->av[0]);
	_strcat(error, ": ");
	_strcat(error, digit_counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(digit_counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	i = error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_error(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
