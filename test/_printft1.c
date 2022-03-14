#include "main.h"

/**
 * get_func - Returns needed function
 * @c: Modificator for function
 * Return: Pointer to needed function
 */
char* (*get_func(char c))(va_list)
{
	int i = 0;

	modif selector[] = {
		{'b', p_itob},
		{'c', p_char},
		{'d', p_double},
		{'i', p_double},
		{'o', p_int2oct},
		{'p', p_addr},
		{'r', p_rev_str},
		{'R', p_rot13},
		{'s', p_str},
		{'S', p_STR},
		{'x', p_hex},
		{'X', p_HEX},
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
 * @ap: va_list
 */
void write_buffer(char *buffer, int length, va_list ap)
{
	write(1, buffer, length); /* Print whole buffer in 1 syscall */
	free(buffer);
	va_end(ap);/* Frees whole heap memory allocation by function _printf  */
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

	if (length > 1022) /* Check if full and flush to stdo if true */
	{
		write(1, buffer, length); /* Print whole buffer in 1 syscall */
		length = 0; /* Reset buffer position */
	}
	for (i = 0; string != '\0'; i++)
	{
		buffer[length] = string[i];
		length++;
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
	if (length > 1022) /* If full, flush to stdo */
	{
		write(1, buffer, length); /* Print whole buffer in 1 syscall */
		length = 0; /* Reset buffer position */
	}
	buffer[length] = c;
	length++;
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
	int* (*func)(va_list); /*Decl pointer to function func and argtype va_list */
	int count = 0;
	char *string;

	if (c == '\0')
	{
		va_end(ap);
		free(buffer);
		return (-1);/* See if needed */
	}
	if (c == '%')
		count = addc2buff('%', buffer, length);
	func = get_func(c); /* Grab function */
	if (func == NULL)  /*Handle fake id, write % followed by nextchar in format*/
	{
		count = addc2buff('%', buffer, length);
		count += addc2buff(c, buffer, length);
	}
	else
	{
		count = func(ap, buffer, length); /* Set count with func returned value */
		if (str == NULL)
		{
			va_end(list);
			free(buffer);
			return (-1);
		}
	}
	return (count);
}

/**
 * _printf - Prints any variadic arguments.
 * @format: a list of types of arguments passed to the function.
 * Return: Void.
 */
int _printf(const char *format, ...)
{
	va_list ap;
	int i = 0, c_count = 0, length = 0;
	char *string, *buffer;

	if (format == NULL) /* If no arg passed to _printf return -1 */
		return (-1);
	buffer = create_buffer(); /* Point to new allocated 1024 bytes buffer*/
	if (buffer == NULL)
		return (-1); /* If error allocating buffer return -1 */
	va_start(ap, format); /* initialize variadic arguments starting from format */
	while (format[i] != '\0')
	{
		if (format[i] != '%') /* set format[i] into buffer until '%' */
			c_count += addc2buff(format[i], buffer, length);
			i++;
		else /* if %, find function */
		{
			i++;
			count = handle_modificators(format[i], length, ap, buffer);
			if (count == -1) /* If error retturn -1 and exit form _printf function */
				return (-1);/* check if need to frees memory before exit */
			c_count += count;
	}
	write_buffer(buffer, length, ap);
	return (c_count);
}