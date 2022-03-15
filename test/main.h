#ifndef _main_h_
#define _main_h_
/* Protect for double inclusion */
#include <stdarg.h> /* Variadic function dependences */
#include <stdlib.h> /* Memory allocation dependences */
#include <unistd.h> /* Syscall write dependences */

/**
 * struct modificators - Struct to store id asociated to a funcion
 * @id: identifier of type to print (e.g. c means char)
 * @func: ptr to functions that print according to identifier (e.g. print_c)
 */
typedef struct modificators
{
	char id;
	int (*func)(va_list, char *, int *);
} modif; /* alias name to refere the deta type struct modificators */

/* Prototype for _printf (entry point for function)*/
int _printf(const char *format, ...);
/* Prototype helper functions */
int (*get_func(char c))(va_list, char *, int *);
char *create_buffer(void);
void write_buffer(char *buffer, int length);
int adds2buff(char *string, char *buffer, int *length);
int addc2buff(char c, char *buffer, int *length);
int handle_modificators(char c, int *length, va_list ap, char *buffer);
/* Prototype modificator functions */
/* int p_itob(va_list ap, char *buffer, int *length); Res for future use */
int p_char(va_list ap, char *buffer, int *length);
int p_dec(va_list ap, char *buffer, int *length);
/* int p_int2oct(va_list ap, char *buffer, int *length); Res for future use */
/* int p_addr(va_list ap, char *buffer, int *length); Res for future use */
/* int p_rev_str(va_list ap, char *buffer, int *length); Res for future use */
/* int p_rot13(va_list ap, char *buffer, int *length); Res for future use */
int p_str(va_list ap, char *buffer, int *length);
/* int p_STR(va_list ap, char *buffer, int *length); Res for future use */
/* int p_hex(va_list ap, char *buffer, int *length); Res for future use */
/* int p_HEX(va_list ap, char *buffer, int *length); Res for future use */

#endif
