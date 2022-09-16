#include "aux.h"
#include <stdio.h>

extern double pi;

int main() {
int grados;
double rad;

printf("Introduce un angulo expresado en grados: ");
scanf("%d",&grados);
printf("\n");

rad = (grados*pi)/180;
printf("%d grados son %f radianes\n", grados, rad);

printf("sen(%d) = %f. cos(%d) = %f\n",grados, senGrados(grados), grados, cosGrados(grados));	
return 0;
}
