#include <stdio.h>
#include <string.h>

/********* TAREAS ************
 * Compila y ejecuta el código. Responde a las siguientes cuestiones:
 * 1. El código de "copia" no funciona. ¿Por qué?
 * 2. Usa ahora la función copia2() (descomenta la línea correspondiente). ¿Funciona la copia?
 * 3. Propón una implementación correcta de la copia.
 * 4. ¿Qué hace la funcióbn "mod"? ¿Por qué funciona?
 * 5. Descomenta la última llamada a la función "mod". Compila y ejecuta. ¿Por qué se produce el error?
 ************** */

void copia2(char* org, char** dst)
{
	*dst = org;
}

void copia(char* org, char* dst)
{
	dst = org;
}

void mod(char* org, char* dst)
{
	int i;

	for (i=0;i<strlen(org);i++)
		dst[i] = org[i] - 32;
}

int main()
{
	char* cad1 = "original";
	char* cad2 = "otra";
	char cad3[32];

	copia(cad1,cad2);
	//copia2(cad1, &cad2);
	printf("cad1 %s cad2 %s\n", cad1, cad2);

	mod(cad1, cad3);
	printf("cad1 %s cad3 %s\n", cad1,cad3);

	//mod(cad1, cad1);
	return 0;
}

