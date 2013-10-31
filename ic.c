#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define G 4.80475E-6 //Valor de la constante de gravitación universal en kpc^3*Gyr^-2*Mo^-1, donde Byr son billones de años
#define PI 3.14159

/*
El programa calcula las condiciones iniciales para 120 estrellas en una galaxia con 5 órbitas.
Autores: Nathalie Agudelo Dueñas y  María M. Ariza Acero 
Fecha de creación: Oct/17/2013
*/

float main(int argc, char **argv){

  if(argc != 5){

    printf("El número de parámetros requerido es 4");
    exit(1);
  }
  
  //Condiciones iniciales para el centro de la galaxia y las constantes a usar en los cálculos

  float x0_c = atof(argv[1]);
  float y0_c = atof(argv[2]);
  float v0x_c = atof(argv[3]);
  float v0y_c = atof(argv[4]);
  float M = 1.0E12;
  float R = 50.0;
  float r = 10.0;
  float v_t = 0.0;
  
  //Espacio entre estrellas para cada orbita (en radianes)
  
  float theta1 = PI/6;
  float theta2 = PI/9;
  float theta3 = PI/12;
  float theta4 = PI/15;
  float theta5 = PI/18;

  //Número de posiciones a encontrar

  int n = 121;

  //Apartando espacio para arreglos de id, posiciones iniciales y velocidades iniciales

  float *xi, *yi, *vix, *viy,*id;

  xi = malloc(n*sizeof(float));
  yi = malloc(n*sizeof(float));
  vix = malloc(n*sizeof(float));
  viy = malloc(n*sizeof(float));
  id = malloc(n*sizeof(int));

  int i;
  
  //Llenando los id 
  
  for(i = 0; i < n; i++){

    id[i] = i-1;

  }
  
  //Calculando las condiciones iniciales

  //Para el centro de la galaxia

  xi[0] = x0_c;
  yi[0] = y0_c;
  vix[0] = v0x_c;
  viy[0] = v0y_c;
  
  for(i = 1; i < n; i++){
    
    //Para cada órbita, se calculan las condiciones iniciales, variando el ángulo para cada estrella

    if(i < 13){
   
      v_t = sqrt(G*M/r);
      vix[i] = -v_t*sin(i*theta1) + v0x_c;
      viy[i] = v_t*cos(i*theta1) + v0y_c;
      xi[i] = r*cos(i*theta1) + x0_c;
      yi[i] = r*sin(i*theta1) + y0_c;
      
    }

    if(13 <= i && i < 31){
      
      v_t = sqrt((G*M)/(2*r));
      vix[i] = -v_t*sin((i-12)*theta2) + v0x_c;
      viy[i] = v_t*cos((i-12)*theta2) + v0y_c;
      xi[i] = 2*r*cos((i-12)*theta2) + x0_c;
      yi[i] = 2*r*sin((i-12)*theta2) + y0_c;

    }

    if(31 <= i && i < 55){
      
      v_t = sqrt((G*M)/(3*r));
      vix[i] = -v_t*sin((i-30)*theta3) + v0x_c;
      viy[i] = v_t*cos((i-30)*theta3) + v0y_c;
      xi[i] = 3*r*cos((i-30)*theta3) + x0_c;
      yi[i] = 3*r*sin((i-30)*theta3) + y0_c;

    }

    if(55 <= i && i < 85){
      
      v_t = sqrt((G*M)/(4*r));
      vix[i] = -v_t*sin((i-54)*theta4) + v0x_c;
      viy[i] = v_t*cos((i-54)*theta4) + v0y_c;
      xi[i] = 4*r*cos((i-54)*theta4) + x0_c;
      yi[i] = 4*r*sin((i-54)*theta4) + y0_c;

    }

    if(85 <= i && i < 121){
      
      v_t = sqrt((G*M)/(5*r));
      vix[i] = -v_t*sin((i-84)*theta5) + v0x_c;
      viy[i] = v_t*cos((i-84)*theta5) + v0y_c;
      xi[i] = 5*r*cos((i-84)*theta5) + x0_c;
      yi[i] = 5*r*sin((i-84)*theta5) + y0_c;

    }
    
  } 

  //Creando un archivo de texto con las condiciones iniciales calculadas

  FILE *output;
  output = fopen("condiciones_iniciales.txt","w");
  
  for(i = 0; i < n; i++){

    //El archivo imprime 5 columnas con 121 filas, correspondiendo a los datos del centro y las 120 estrellas de la galaxia

    fprintf(output, "%f %f %f %f %f\n", id[i], xi[i], yi[i], vix[i], viy[i]);

  }
  
  fclose(output);
  
}

