#include "main.h"
/**
 * p_char - write given chatr to buffer
 * @ap: char
 * @buffer: Buffer holding string to print
 * @length: Position in buffer
 * Return: number of chars written to buffer
 */
int p_char(va_list ap, char *buffer, int *length)
{
	char c;
	int count = 0;

	c = va_arg(ap, int); /* declare as int to print special chars */
	count = addc2buff(c, buffer, length);

	return (count);
}
