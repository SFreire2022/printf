#include "main.h"

/**
 * get_func - Returns needed function
 * @c: Modificator for function
 * Return: Pointer to needed function
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
 * create_buffer - Creates buffer to hold string until it's ready for print
 * Return: Pointer to buffer created
 */
char *create_buffer(void)
{
	char *buffer;

	buffer = malloc(sizeof(char) * 1024);
	if (buffer == NULL)
		return (NULL);
	return (buffer);
}

/**
 * write_buffer - Prints buffer, then frees it and frees va_list
 * @buffer: Buffer holding print-ables
 * @length: Length of print-able string
 */
void write_buffer(char *buffer, int length)
{
	write(1, buffer, length); /* Print whole buffer in 1 syscall */
	free(buffer);
}

/*crear 1 o 2 func más para agre caract al buffer (ver desplazam en fortmat)*/
/**
 * adds2buff - Check if buffer is full, if true, print everything then revert
 * length back to 0 to write at buffer start
 * @string: String to add2buff
 * @buffer: Buffer holding string to print
 * @length: Position in buffer
 * Return: The position to coninue writing to buffer
 */
int adds2buff(char *string, char *buffer, int *length)
{
	int i;

	if ((*length) > 1022) /* Check if full and flush to stdo if true */
	{
		write(1, buffer, (*length)); /* Print whole buffer in 1 syscall */
		*length = 0; /* Reset buffer position */
	}
	for (i = 0; string[i] != '\0'; i++)
	{
		buffer[(*length)] = string[i];
		(*length)++;
	}
	return (i);
}

/**
 * addc2buff - Check if buffer is full, if true, print everything then revert
 * length back to 0 to write at buffer start
 * @c: Char to add2buff
 * @buffer: Buffer holding string to print
 * @length: Position in buffer
 * Return: return increment
 */
int addc2buff(char c, char *buffer, int *length)
{
	if ((*length) > 1022) /* If full, flush to stdo */
	{
		write(1, buffer, (*length)); /* Print whole buffer in 1 syscall */
		*length = 0; /* Reset buffer position */
	}
	buffer[(*length)] = c;
	(*length)++;
	return (1);
}

/**
 * handle_modificators - Check modificators, to handle exceptions,
 * if no exceprions found, call
 * @c: Character from format to check
 * @length: Position in buffer
 * @ap: Argument pointer
 * @buffer: Buffer holding string to print
 * Return: The number of characters written to buff, if error return flag -1
 */
int handle_modificators(char c, int *length, va_list ap, char *buffer)
{
	int (*func)(va_list, char *, int *); /* point to func and argtype va_list */
	int count = 0;

	if (c == '\0')
	{
		va_end(ap);
		free(buffer);
		return (-1);/* See if needed */
	}
	if (c == '%')
	{
		count = addc2buff('%', buffer, length);
		return (count);
	}
	func = get_func(c); /* Grab function */
	if (func == NULL)  /*Handle fake id, write % and return*/
	{
		count = addc2buff('%', buffer, length);
		return (count);
	}
	else
	{
		count = func(ap, buffer, length); /* Set count with func returned value */
		if (count == 0)
		{
			va_end(ap);
			free(buffer);
			return (-1);
		}
	}
	return (count);
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
	int *length = &buff_pos;

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
			h_count = handle_modificators(format[i], length, ap, buffer);
			if (h_count == -1) /* If error retturn -1 and exit form _printf function */
				return (-1);/* check if need to frees memory before exit */
			c_count += h_count;
			i++;
		}
	}
	write_buffer(buffer, buff_pos);
	va_end(ap);/* Frees the last heap memory allocation by function _printf  */
	return (c_count);
}
