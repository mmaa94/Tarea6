#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define G 4.6*(pow(10,(-6)) //Valor de la constante de gravitación universal en kpc*km^2*s^-2*Mo^-1
#define PI 3.14159

float main(int argc, char **argv){

  if(argc != 5){

    printf("El número de parámetros de entrada no es el requerido");
    exit(1);
  }

  //Condiciones iniciales para el centro de la galaxia y las constantes a usar en los cálculos

  float x0_c = atof(argv[1]);
  float y0_c = atof(argv[2]);
  float v0x_c = atof(argv[3]);
  float v0y_c = atof(argv[4]);
  int M = pow(10,12);
  int R = 50;
  int r = 10;
  int v_t = 0;

  //Espacio entre estrellas para cada orbita (en grados)

  int theta1 = PI/6;
  int theta2 = PI/9;
  int theta3 = PI/12;
  int theta4 = PI/15;
  int theta5 = PI/18;

  //Número de posiciones a encontrar

  int n=121;

  //Apartando espacio para arreglos de id, posiciones iniciales y velocidades iniciales

  float *xi, *yi, *vix, *viy,*id;

  xi=malloc(n*sizeof(float));
  yi=malloc(n*sizeof(float));
  vix=malloc(n*sizeof(float));
  viy=malloc(n*sizeof(float));
  id=malloc(n*sizeof(int));

  int i;
  
  //Llenando los id 
  
  for(i=0;i<121;i++){

    id[i] = i-1;

  }
  
  //Calculando las velocidades en x
  
  vix[0] = v0x_c;
  
  for(i=1;i<121;i++){
    
    if(i < 13){
      
      v_t = pow(((G*M)/r),0.5);
      vix[i] = v_t*sin(n*theta1) + v0x_c;
      viy[i] = v_t*cos(n*theta1) + v0y_c;
      xi = r*cos(n*theta1) + x0_c;
      yi = r*sin(n*theta1) + y0_c;

    }

    if(13 <= i && i < 31){
      
      v_t = (G*M)/2r;

    }

    if(31 <= i && i < 55){
      
      v_t = (G*M)/3r;

    }

    if(55 <= i && i < 85){
      
      v_t = (G*M)/4r;

    }

    if(85 <= i && i < 121){
      
      v_t = (G*M)/5r;

    }

  } 

  output = fopen("condiciones_iniciales.txt","w");

}  
