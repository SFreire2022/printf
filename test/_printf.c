#include "main.h"
#include <stdio.h>

/**
 * _printf - Prints any variadic arguments.
 * @format: a list of types of arguments passed to the function.
 * Return: Void.
 */
int _printf(const char *format, ...)
{
	va_list ap;
	int i = 0, c_count = 0;
	char *string;

	va_start(ap, format);
	while (format && format[i])
	{
		if (format[i] != '%')
		{
			_putchar(format[i]);
			c_count++;
		}
		else
		{
			i++;
			switch (format[i])
			{
			case 'c':
				_putchar(va_arg(ap, int));
				c_count++;
				break;
			case 'i':
				printf("%d", va_arg(ap, int));
				break;
			case 'f':
				printf("%f", va_arg(ap, double));
				break;
			case 's':
				string = va_arg(ap, char *);
				if (!string)
				{
					printf("%p", string);
					break;
				}
				_puts(string);
				break;
			default:
				return (-1);
			}
		}
		i++;
	}
	va_end(ap);
	return (c_count);
}
