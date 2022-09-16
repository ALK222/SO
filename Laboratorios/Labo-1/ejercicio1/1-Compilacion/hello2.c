#include <stdio.h>

/******** TAREAS *****
* 1. Compila el siguiente código y ejecútalo
  $ gcc hello2.c -o hello2.out
  output:
    Hello world      a= 7 b= 9
    Hello world      a= 8 b= 9
    Hello world      a= 9 b= 9
    Hello world      a= 9 b= 9
    Hello world      a= 9 b= 9
* 2. Posteriormente, obtén la salida de la etapa de pre-procesado (opción -E o
*    la opción --save-temps para obtener la salida de todas las etapas
*    intermedias) y en un fichero hello2.i
* 3. ¿Qué ha ocurruido con la "llamada a min()" en hello2.i?
  Se ha sustitudio por un condicional
* 4. ¿Qué efecto ha tenido la directiva #include <stdio.h>?
  La directiva ha resultado en la inclusión de distintas variables, funciones y macros antes solo presentes
  en la biblioteca directamente en el código
*****************/

#define N 5

#define min(x, y) ((x < y) ? x : y)
int a = 7;
int b = 9;
int main()
{

  char *cad = "Hello world";
  int i;

  for (i = 0; i < N; i++)
  {
    printf("%s \t a= %d b= %d\n", cad, a, b);
    a++;
    a = min(a, b);
  }
  return 0;
}
