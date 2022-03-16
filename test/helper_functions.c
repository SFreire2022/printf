#include "main.h"

/**
 * create_buffer - Creates buffer to hold string until it's ready for print
 * Return: Pointer to buffer created
 */
char *create_buffer(void)
{
	char *buffer;

	buffer = malloc(sizeof(char) * 1028);
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
	buffer[length + 1] = '\0';
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

	for (i = 0; string[i] != '\0'; i++)
	{
		if ((*length) > 1024) /* Check if full and flush to stdo if true */
		{
			write(1, buffer, (*length)); /* Print whole buffer in 1 syscall */
			*length = 0; /* Reset buffer position */
		}
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
	if ((*length) > 1024) /* If full, flush to stdo */
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
 * @i: General va_list string format index
 * Return: The number of characters written to buff, if error return flag -1
 */
int handle_modificators(char c, int *length, va_list ap,
	char *buffer, unsigned int *i)
{
	int (*func)(va_list, char *, int *); /* point to func and argtype va_list */
	int count = 0;

	if (c == '\0')
	{
		return (0);
	}
	if (c == '%')
	{
		count = addc2buff('%', buffer, length);
		(*i)++;
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
		(*i)++;
	}
	return (count);
}
