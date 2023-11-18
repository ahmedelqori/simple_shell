#include "shell.h"

/**
 * get_len - Gets the lenght of a number.
 * @nn:  integer number.
 * Return: Lenght of the number.
 */
int get_len(int nn) 
{
	unsigned int nn1;
	int lenght = 1;

	if (nn < 0)
	{
		lenght++;
		nn1 = nn * -1;
	}
	else
	{
		nn1 = nn;
	}
	while (nn1 > 9)
	{
		lenght++;
		nn1 = nn1 / 10;
	}

	return (lenght);
}
/**
 * aux_itoa - converts a string to an integer. 
 * @nn: integer number
 * Return: String.
 */
char *aux_itoa(int nn)
{
	unsigned int nn1;
	int lenght = get_len(nn);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (nn < 0)
	{
		nn1 = nn * -1;
		buffer[0] = '-';
	}
	else
	{
		nn1 = nn;
	}

	lenght--;
	do {
		*(buffer + lenght) = (nn1 % 10) + '0';
		nn1 = nn1 / 10;
		lenght--;
	}
	while (nn1 > 0)
		;
	return (buffer);
}

/**
 * _atoi - converts a string to an integer.
 * @s: represents input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int digit_count = 0, size = 0, rs = 0, sg = 1, m = 1, i;

	while (*(s + digit_count) != '\0')
	{
		if (size > 0 && (*(s + digit_count) < '0' || *(s + digit_count) > '9'))
			break;

		if (*(s + digit_count) == '-')
			sg *= -1;

		if ((*(s + digit_count) >= '0') && (*(s + digit_count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		digit_count++;
	}

	for (i = digit_count - size; i < digit_count; i++)
	{
		rs = rs + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (rs * sg);
}
