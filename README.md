# Printf

## Technologies
* C files are compiled using `gcc 9.3.0`
* C files are written according to the standard C89 with GNU extensions
* Tested on Ubuntu 20.04 LTS

## Tasks
Programs written in C:

| Filename | Description |
| -------- | -----------|
| `printf` | function that produces output according to a format functions %c %s |
| `c` | int argument is converted to an unsigned char, then the resulting character is written. |
| `s | the const char * argument is expected to be a pointer to an array of character type (pointer to a string). Characters from the array are written up to a terminating null byte, but do ot include the terminating null byte. |
| % | a '%' is written but no argument is converted. The complete version specification is '%%'.|
| d, i | The int argument is converted to signed decimal notation|

## Examples

*String
Input: _printf("%s\n", 'This is a string.');
Output: This is a string.Input: _printf("%s\n", 'This is a string.');

*Character
Input: _printf("The first letter in the alphabet is %c\n", 'A');
Output: The first letter in the alphabet is A

*Integer
Input: _printf("There are %i dozens in a gross\n", 12);
Output: There are 12 dozens in a gross
