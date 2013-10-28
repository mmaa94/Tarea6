#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
Módulo que contiene la función para calcular el número de líneas en un archivo.
Autores:Nathalie Agudelo Dueñas y  María M. Ariza Acero 
Fecha de creación: Oct  24 03:14:34 COT 2013
**/

int count_lines(char *filename){

  /**
   Input: NOmbre del archivo en el que se quiere contar el número de líneas
   Output: Número de líneas
  **/

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
