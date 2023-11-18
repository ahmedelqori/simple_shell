#include "shell.h"

/**
 * rev_string - reverses a string.
 * @s: represents input string.
 * Return: nothing to return.
 */
void rev_string(char *s)
{
	int digit_count = 0, i, j;
	char *str, temp;

	while (digit_count >= 0)
	{
		if (s[digit_count] == '\0')
			break;
		digit_count++;
	}
	str = s;

	for (i = 0; i < (digit_count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
