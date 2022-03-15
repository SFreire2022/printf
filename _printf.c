#include "main.h"

/**
 * get_func - Returns needed function
 * @c: Modificator for function
 * Return: Pointer to selected function
 */
int (*get_func(char c))(va_list, char *, int *)
{
	int i = 0;

	modif selector[] = {
/*		{'b', p_itob}, Reserved for future use */
		{'c', p_char},
		{'d', p_dec},
		{'i', p_dec},
/*		{'o', p_int2oct}, Reserved for future use */
/*		{'p', p_addr}, Reserved for future use */
/*		{'r', p_rev_str}, Reserved for future use */
/*		{'R', p_rot13}, Reserved for future use */
/*		{'u', p_unsig}, Reserved for future use */
		{'s', p_str},
/*		{'S', p_STR}, Reserved for future use */
/*		{'x', p_hex}, Reserved for future use */
/*		{'X', p_HEX}, Reserved for future use */
		{'\0', NULL}
	};

	while (selector[i].id != '\0')
	{
		if (selector[i].id == c)
			return (selector[i].func);
		i++;
	}
	return (NULL);
}

/**
 * _printf - Prints any variadic arguments.
 * @format: a list of types of arguments passed to the function.
 * Return: The amount of chars printed, otherwise -1.
 */
int _printf(const char *format, ...)
{
	va_list ap;
	int i = 0, c_count = 0, buff_pos = 0, h_count = 0;
	char *buffer;
	int *length = &buff_pos, *inc = &i;

	if (format == NULL) /* If no arg passed to _printf return -1 */
		return (-1);
	buffer = create_buffer(); /* Point to new allocated 1024 bytes buffer*/
	if (buffer == NULL)
		return (-1); /* If error allocating buffer return -1 */
	va_start(ap, format); /* initialize variadic arguments starting from format */
	while (format[i] != '\0')
	{
		if (format[i] != '%') /* set format[i] into buffer until '%' */
		{
			c_count += addc2buff(format[i], buffer, length);
			i++;
		}
		else /* if %, hanlde nextchar */
		{
			i++;
			h_count = handle_modificators(format[i], length, ap, buffer, inc);
			if (h_count == -1) /* If error retturn -1 and exit form _printf function */
				return (-1);/* check if need to frees memory before exit */
			c_count += h_count;
		}
	}
	write_buffer(buffer, buff_pos);
	va_end(ap);/* Frees the last heap memory allocation by function _printf  */
	return (c_count);
}
