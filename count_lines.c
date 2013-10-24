#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int contarlineas(char *filename){

	FILE *in;
	int n_lineas;
	int c;
	if (!(in=fopen(filename,"r"))){
		printf("El archivo %s no se puede abrir\n",  filename);
		exit (1);
	}
	
	n_lineas=0;
	
	do{
		c=fgetc(in);
		if(c=='\n'){
			n_lineas ++;
		}
	}while(c!=EOF);

	fclose(in);
	return n_lineas;
}
