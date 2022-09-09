#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE		512

int main(int argc, char **argv) {
    int  n_read;
   FILE* ent, *sal;
   	
    char buffer[BUFSIZE];
    
    	ent = fopen(argv[1], "r"); /* abre el archivo de entrada */	
	if (ent == NULL){
        	perror("fopen");
	   	exit(-1);
    	}
    

    	sal = fopen(argv[2], "w+");     /* crea el archivo de salida */
    	if (sal < 0){
        	fclose(ent);
        	perror("creat");    
		exit(-1);
     	}	   

    /* bucle de lectura del archivo de entrada */
    	while ( (n_read = fread(buffer,sizeof(char), BUFSIZE ,ent)) == BUFSIZE)  {    
        	/* escribir el buffer al archivo de salida */
        	if (fwrite( buffer, sizeof(char),n_read,sal) < n_read)  {
            		perror("write");
            		fclose(ent); 
			fclose(sal);
            		exit(-1);
       	 	}
    	}
	// hemos salido del bucle. Puede que hayamos llegado al final o que haya habido error
	if (feof(ent)) {
		// final de fichero. Hacemos la ultima escritura de n_read bytes
		// porque la ultima no se hizo
		printf("Completo los ultimos %d bytes\n", n_read);
	        if (fwrite( buffer, sizeof(char),n_read,sal) < n_read)  {
                        perror("write");
                        fclose(ent);
                        fclose(sal);
                        exit(-1);
                }	
	} 
	else { 
        	perror("read");
        	fclose(ent); fclose(sal);
        	exit(-1);
    	} 
        fclose(ent); 
		fclose(sal);
    	exit(0);
}

