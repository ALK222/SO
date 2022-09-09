#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE		512

int main(int argc, char **argv) {
   FILE *sal;
   int x = 7, y = 8; 	

    char buffer[BUFSIZE] = "Hola. Esto es una simple cadena de caracteres";
	     
  if (argc !=2 ) {
	fprintf(stderr,"Error: se debe usar indicando un nombre de fichero\n");
	exit(-1);
   }
    	sal = fopen(argv[1], "w+");     /* crea el archivo de salida */
    	if (sal < 0){
        	perror("creat");    
		exit(-1);
     	}	   

 	// Escribo usando fwrite
        if (fwrite( buffer, sizeof(char),strlen(buffer),sal) <strlen(buffer))  {
            		perror("write");
			fclose(sal);
            		exit(-1);
       	 }

	// Escribo usando fprintf
	fprintf(sal,"\nLa cadena en buffer es: %s y tienen %lu caracteres.\n",buffer,strlen(buffer));

	// Escribo variables enteras (pero en ASCII)
	fprintf(sal,"x vale %d  y vale %d\n",x,y);
        fclose(sal);
    	exit(0);
}

