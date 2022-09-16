1. Examina el makefile, identifica las variables definidas, los objetivos(targets) y las regalas.

   - Variables:

     - CC: compilador de C
     - CFLAGS: flags parra el compilador
     - LIBS: librerías necesarias

   - Objetivos:

     - %.o : Compila todos los archivos \*.o con las variables anteriores

   - Reglas:
     - all: compila aux e init
     - clean: limpia todos los \*.o y prueba

2. Ejecuta make en la linea de comandos y comprueba las ordenes que ejecuta para construir el proyecto.

```
gcc -Wall -g -c -o aux.o aux.c
gcc -Wall -g -c -o init.o init.c
gcc -Wall -g -o prueba aux.o init.o -lm
```

3. Marca el fichero aux.c como modificado ejecutando touch aux.c. Después
   ejecuta de nuevo make. ¿Qué diferencia hay con la primera vez que lo
   ejecutaste? ¿Por qué?

   No compila init.o porque no ha sido modificado

   ```
   gcc -Wall -g -c -o aux.o aux.c
   gcc -Wall -g -o prueba aux.o init.o -lm
   ```

4. Ejecuta la orden make clean. ¿Qué ha sucedido? Observa que el objetivo clean
   está marcado como phony en la orden .PHONY: clean. ¿por qué? Para comprobarlo
   puedes comentar dicha línea del makefile, compilar de nuevo haciendo make, y
   después crear un fichero en el mismo directorio que se llame clean, usando el
   comando touch clean. Ejecuta ahora make clean, ¿qué pasa?

   Al ejecutar make clean se borran todos los archivos de compilación. Si se crea el archivo clean y se comenta la línea make clean intenta compilar el archivo

5. Comenta la linea LIBS = -lm poniendo delante una almoadilla (#). Vuelve a
   contruir el proyecto ejecutando make (haz un clean antes si es necesario).
   ¿Qué sucede? ¿Qué etapa es la que da problemas?

   ```
   gcc -Wall -g -c -o aux.o aux.c
   gcc -Wall -g -c -o init.o init.c
   gcc -Wall -g -o prueba aux.o init.o
   /usr/bin/ld: aux.o: en la función `senGrados':
   /home/_alk/Documentos/SO/Laboratorios/Labo-1/ejercicio1/2-Make/aux.c:7: referencia a `sin' sin definir
   /usr/bin/ld: aux.o: en la función `cosGrados':
   /home/_alk/Documentos/SO/Laboratorios/Labo-1/ejercicio1/2-Make/aux.c:12: referencia a `cos' sin definir
   collect2: error: ld devolvió el estado de salida 1
   make: *** [makefile:9: all] Error 1
   ```

   No compila porque no tiene las funciones de la librería math. Este error se produce en la etapa de compilación.
