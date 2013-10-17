#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float main(int argc, char **argv){

  if(argc!= 5){

    printf("El número de parámetros de entrada no es el adecuado");
    exit(1);
  }

  //Condiciones iniciales para el centro de masa
  float x0_cm=atof(argv[1]);
  float y0_cm=atof(argv[2]);
  float v0x_cm=atof(argv[3]);
  float v0y_cm=atof(argv[4]);

  //Espacio entre estrellas para cada orbita

  int theta1=30;
  int theta2=20;
  int theta3=15;
  int theta4=12;
  int theta5=10;

  //Número de posiciones necesarias

  int n=101;

  //Apartando espacio para arreglos de id, posiciones iniciales y velocidades iniciales

  float *x0, *y0, *v0x, *v0y,*id;

  x0=malloc(n*sizeof(float));
  y0=malloc(n*sizeof(float));
  v0x=malloc(n*sizeof(float));
  v0y=malloc(n*sizeof(float));
  id=malloc(n*sizeof(int));

  int i;
  
  //Llenando los id 
  for(i=0;i<101;i++){

    id[i]=i-1;

  }

  

}  
