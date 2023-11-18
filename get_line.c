#include "shell.h"

/**
 * bring_line - assigns the line variable for getline. 
 * @lineptr: Buffer that store the input string. 
 * @buffer: string that is been called to line
 * @e: represents size of line. 
 * @b: represents size of buffer. 
 */
void bring_line(char **lineptr, size_t *e, char *buffer, size_t b)
{

	if (*lineptr == NULL)
	{
		if  (b > BUFSIZE)
			*e = b;

		else
			*e = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*e < b)
	{
		if (b > BUFSIZE)
			*e = b;
		else
			*e = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Reads  input  from the  stream
 * @lineptr: buffer that stores the input
 * @e: size of lineptr
 * @stream: stream to read from
 * Return: returns number of bytes
 */
ssize_t get_line(char **lineptr, size_t *e, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t rtnval;
	char *buffer;
	char l = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (l != '\n')
	{
		i = read(STDIN_FILENO, &l, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, e, buffer, input);
	rtnval = input;
	if (i != 0)
		input = 0;
	return (rtnval);
}
