#include "main.h"

/**
 * _puts - Print each char of a pointer to
 * addres of given string.
 *
 * @str: The pointer to addres of given string as a param.
 *
 * Return: void.
 */
void _puts(char *str)
{
	int i = 0;

	while (*(str + i) != '\0')
	{
		_putchar(*(str + i));
		i++;
	}
}
