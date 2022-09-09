#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


struct _tipo_{
	double b;
	int a;
	char c[10];
	short d;
} var;
 
int main(int argc, char **argv) {
   FILE *sal;
   int x , y; 	 
   int i;
 	
	     
  if (argc !=2 ) {
	fprintf(stderr,"Error: se debe usar indicando un nombre de fichero\n");
	exit(-1);
   }
    	sal = fopen(argv[1], "r+");     /* crea el archivo de salida */
    	if (sal < 0){
        	perror("creat");    
		exit(-1);
     	}	   

	// AHora escribo el valor de x e y pero en BINARIO
	 if (fread( &x, sizeof(int),1,sal) < 1) { 
            		perror("write");
			fclose(sal);
            		exit(-1);
       	 }
	 if (fread( &y, sizeof(int),1,sal) < 1)  {
            		perror("write");
			fclose(sal);
            		exit(-1);
	}

	 if (fread( &var, sizeof(var),1,sal) < 1)  {
            		perror("write");
			fclose(sal);
            		exit(-1);
	}
        fclose(sal);

	printf("Valor leido de x: %d. y: %d\n",x,y);
	printf("Valos del campo a: %d del campo b: %f campo d: %d\n",var.a,var.b,var.d);
    	exit(0);
}

