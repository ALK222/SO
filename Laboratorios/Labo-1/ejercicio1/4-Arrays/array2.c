#include <stdio.h>

/************ TAREAS
 * Compila y ejecuta el código. Contesta a las cuestiones:
 *  1. ¿La copia del array se realiza correctamente? ¿Por qué?
 *  2. Si no es correcto, escribe un código que sí realice la copia correctamente.
 *  3. Descomenta la llamada a la fución "tmo" en la función main(). Compila de nuevo y ejecuta.
 *  4. El problema que se produce, ¿es de compilación o de ejecución? ¿Por qué se produce?
 *  5. Encuentra un valor de MAXVALID superior a 4 con el que no se dé el problema. ¿Se está escribiendo
 *     más allá del tamaño del array? Si es así, ¿por qué funciona el código?
*******************/

#define N 10
#define MAXELEM 5000
#define MAXVALID 100

// funcion que imprime por pantalla el conteniod del array v de tam. size
void imprimeArray(int v[],int size)
{
	int i;
	printf("-------------------\n");
	for (i=0;i<size;i++)
		printf("%d ",v[i]);
	printf("\n\n");
}

// funcion que copia el contenido de un array en otro
void copyArray(int src[],int dst[],int size)
{
 	dst = src;
}

/*
void tmo()
{
	int x = -1;
	int a[4] = {0,1,2,3};
	int b = 10000;
	int c = -1;
	int i;

	for  (i=4;i<MAXVALID;i++)
		a[i]=i;

	printf("x %d b %d c %d\n", x,b,c);
}
*/

int main()
{
	int A[N] = {4,3,8,5,6,9,0,1,7,2};
	int B[N];

	//tmo();
	copyArray(A,B,N);
	imprimeArray(B,N);
}
