#include "shell.h"

/**
 * _strdup - duplicates a string in heap memory.
 * @s: char pointer string 
 * Return: duplicated string
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - Returns the lenght of a string.
 * @s: char pointer string 
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * comp_chars - compare characters of strings
 * @str: represents input string.
 * @delim: represents delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int comp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by delimiter.
 * @str: represents input string.
 * @delim: represents  delimiter.
 *
 * Return: spitted string. 
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitt, *str_end;
	char *str_start;
	unsigned int i, boolean;

	if (str != NULL)
	{
		if (comp_chars(str, delim))
			return (NULL);
		splitt = str; /*Stores first address*/
		i = _strlen(str);
		str_end = &str[i]; /*Stores last address*/
	}
	str_start = splitt;
	if (str_start == str_end) /*Reached the end*/
		return (NULL);

	for (boolean = 0; *splitt; splitt++)
	{
		/*Breaking loop and finding the next token*/
		if (splitt != str_start)
			if (*splitt && *(splitt - 1) == '\0')
				break;
		/*Replacing delimiter for null character*/
		for (i = 0; delim[i]; i++)
		{
			if (*splitt == delim[i])
			{
				*splitt = '\0';
				if (splitt == str_start)
					str_start++;
				break;
			}
		}
		if (boolean == 0 && *splitt) /*Str != Delim*/
			boolean = 1;
	}
	if (boolean == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - defines if the string passed is a number
 *
 * @s: represents input string
 * Return: 1 if string is a number. 0 otherwise. 
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
