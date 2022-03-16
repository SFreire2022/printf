#include "main.h"
/**
 * p_str - Write to buffer va_list argument poiter
 * @ap: va_list argument poiter
 * @buffer: Buffer holding string to print
 * @length: Position in buffer
 * Return: Count of chars written to buffer
 */
int p_str(va_list ap, char *buffer, int *length)
{
	char *string;
	int count = 0;

	string = va_arg(ap, char *);
	if (string == NULL)
		return (0);
/*		string = "(null)";for debug*/
	count = adds2buff(string, buffer, length);
	return (count);
}
