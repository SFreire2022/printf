#include "main.h"

/**
 * p_unsig - Add given unsigned int number to buffer
 * @ap: char
 * @buffer: Buffer holding string to print
 * @length: Position in buffer
 * Return: number of chars written to buff
 */
int p_unsig(va_list ap, char *buffer, int *length)
{
	unsigned int a, b, c, d, f;
	unsigned int n;
	int count = 0;

	n = va_arg(ap, unsigned int);
	if (n < 0)
	{
		count = addc2buff('-', buffer, length);
		n = n * -1;
	}
	b = n;
	c = 1;
	for (a = 1 ; b > 9 ; a++)
	{
		b = b / 10;
		c = c * 10;
	}
	for (f = 1; f <= a; f++)
	{
		d = n / c;
		n = n % c;
		c = c / 10;
		count += addc2buff(d + '0', buffer, length);
	}
	return (count);
}
