#include <stdio.h>

/******** TAREAS *****
 * Compila el código y trata de ejecutarlo. Contesta a las cuestiones
 * 1. ¿Tenemos un problema de compilación o de ejecución?
 * 	Compilación
 * 2. ¿Por qué se da el problema?. Soluciónalo, compila y ejecuta de nuevo.
 * 	Porque se intenta definir el tamaño de un array con una variable
 * 3. a,b,c, y x están declaradas de forma consecutiva. ¿Sus direcciones son concesutivas?
 * No tienen porqué ser consecutivas
 * 4. ¿Qué significa el modificar "%lu" en printf()?
 * 	entero sin signo (long unsigned)
 * 5. ¿A qué dirección apunta "pc"? ¿Coincide con la de alguna variable anteriormente declarada? Si es así,
 * ¿Coinciden los tamaños de ambas?
 * 0x55b0e1e08088, coincide con x pero no tienen el mismo tamaño.
 * 6. ¿Coincide el valor del tamaño de "array1" con el número de elementos del array? ¿Por qué?
 * No porque está indicando el tamaño del tipo de datos del array
 * 7. ¿Coinciden las direcciones a la que apunta cadena1 con la de cadena2?
 * No
 * 8. ¿Por qué los tamaños (según sizeof()) de cadena1 y cadena2 son diferentes?
 * Porque uno ajusta al tamaño de cadena y el  otro al tamaño del array
 ***************/

#define ARRAY_SIZE 10
#define MYARRAY_SIZE 7 // Solución apartado 2

int a = 7;
unsigned long b = 8;
short c;
char x;
char *pc;

int array1[ARRAY_SIZE];
int array2[MYARRAY_SIZE];

char *cadena1 = "CADENA DE CARACTERES";
char cadena2[] = "CADENA DE CARACTERES";
int main()
{
	pc = &x;
	a = 16;
	printf("Direccion de a: %p Tam: %lu \n", &a, sizeof(a));
	printf("Direccion de b: %p Tam: %lu \n", &b, sizeof(b));
	printf("Direccion de c: %p Tam: %lu \n", &c, sizeof(c));
	printf("Direccion de x: %p Tam: %lu \n", &x, sizeof(x));
	printf("Direccion de pc: %p Direccion a la que apunta pc: %p Tam: %lu \n",
		   &pc, pc, sizeof(pc));
	printf("Direccion de array: %p Direccion del elem 0: %p Tam de array: %lu \n",
		   array1, &array1[0], sizeof(array1));
	printf("Direccion de cadena1: %p Direccion a la que apunta: %p Tam: %lu \n",
		   &cadena1, cadena1, sizeof(cadena1));
	printf("Direccion de cadena2: %p Direccion a la que apunta: %p Tam: %lu \n",
		   &cadena2, cadena2, sizeof(cadena2));
	return 0;
}
