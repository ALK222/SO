#include <stdio.h>
/**** TAREAS ********
 * Compila el codigo, ejecutalo y responde a las cuestiones
 * 1. ¿Por qué el primer printf() imprime valores distintos para 'a'?
 * El primer %d imprime enteros y en %c busca el caracter ASCII 127 (no representable)
 * 2. ¿Cuánto ocupa un tipo de datos char? 1 byte
 * 3. ¿Por qué el valor de 'a' cambio tanto al incrementarlo en una unidad?
 * (la  respuesta está relacionada con la cuestión anterior)
 * Overflow en el valor binario
 * 4. Si un "long" y un "double" ocupan lo mismo, ¿por qué hay 2 tipos de datos diferentes?
 * Representan distintos tipos de valores, long siendo valores mayores y double valores en coma flotante
 * */
char a = 127;
int b = 41;
int main()
{

	printf("a = %d a = %c \n", a, a);
	a++;
	printf("a = %d a = %c b=%d  b=%c\n", a, a, b, b);
	printf("Size of int: %lu\n", sizeof(int));
	printf("Size of char: %lu\n", sizeof(char));
	printf("Size of float: %lu\n", sizeof(float));
	printf("Size of double: %lu\n", sizeof(double));
	printf("Size of long: %lu\n", sizeof(long));
	printf("Size of short: %lu\n", sizeof(short));
	printf("Size of void*: %lu\n", sizeof(void *));
}
