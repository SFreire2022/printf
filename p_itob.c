#include "main.h"
/**
 * p_itob - Write to buffer converted Int to bin
 * @ap: va_list argument poiter
 * @buffer: Buffer holding string to print
 * @length: Position in buffer
 * Return: Count of chars written to buffer
 */
int p_itob(va_list ap, char *buffer, int *length)
{
	int i, k, j = 0, twos = 1, c = 0;
	char str_bin[32];

	k = va_arg(ap, int);
	i = k;
	/* account for negative numbers with '1' at index 0 */
	if (k < 0)
	{
		str_bin[0] = 1 + '0';
		j++;
		k *= -1;
		i *= -1;
	}
	/* find biggest power of 2 it's divisible by */
	while (k > 1)
	{
		k /= 2;
		twos *= 2;
	}
	/* divide down and store binary num */
	while (twos > 0)
	{
		str_bin[j++] = (i / twos + '0');
		i %= twos;
		twos /= 2;
	}
	str_bin[j] = '\0';
	c = adds2buff(str_bin, buffer, length);
	return (c);
}
