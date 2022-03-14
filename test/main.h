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
	char* (*func)(va_list);
} modif; /* alias name to refere the deta type struct modificators */

/* Prototype for _printf (entry point for function)*/
int _printf(const char *format, ...);
/* Prototype helper functions */
char* (*get_func(char c))(va_list);
char *create_buffer(void);
void write_buffer(char *buffer, int length, va_list ap);
int adds2buff(char *string, char *buffer, int *length);
int addc2buff(char c, char *buffer, int *length);
int handle_modificators(char c, int *length, va_list ap, char *buffer);
/* Prototype modificator functions */
char *p_itob(va_list ap);
int p_char(va_list ap, int *buffer, int *length);
char *p_double(va_list ap);
char *p_int2oct(va_list ap);
char *p_addr(va_list ap);
char *p_rev_str(va_list ap);
char *p_rot13(va_list ap);
int p_str(va_list ap, int *buffer, int *length);
char *p_STR(va_list ap);
char *p_hex(va_list ap);
char *p_HEX(va_list ap);

#endif
