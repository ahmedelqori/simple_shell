#include "shell.h"

/**
 * _strcat - concatenate two strings
 * @dest: char pointer the destination of the copied string
 * @src: char pointer the source of string
 * Return: the destination string
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string pointed to by the source. 
 * @dest: char pointer the destination of the copied string. 
 * @src:char pointer the source of string
 * Return: the destination string. 
 */
char *_strcpy(char *dest, char *src)
{

	size_t b;

	for (b = 0; src[b] != '\0'; b++)
	{
		dest[a] = src[b];
	}
	dest[b] = '\0';

	return (dest);
}
/**
 * _strcmp - compares two strings.
 * @s1: string1 for  comparison. 
 * @s2: string2 for comparison
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character string,
 * @s: represents tring.
 * @c: returns character.
 * Return: returns pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: represent initial segment.
 * @accept: Accepted bytes.
 * Return: returns number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int i, j, boolean;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		boolean = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				boolean = 0;
				break;
			}
		}
		if (boolean == 1)
			break;
	}
	return (i);
}
