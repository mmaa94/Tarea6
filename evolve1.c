#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "count_lines.h"
#include "sec_order.h"

/**
Módulo que con[iene la función main para analizar los datos de un archivo de puntos y hacer la solución usando Runge Kutta de cuarto orden.
Autores:Nathalie Agudelo Dueñas y  María M. Ariza Acero 
Fecha de creación: Oct  24 02:53:49 COT 2013
**/

float main(int argc, char **dots){

  //Comprobar el número de parámetros

  if(argc!=2){
	      printf("Se requieren 2 parámetros de entrada");
	      exit(1);
	    }

  //Archivo a leer

  FILE *dot;
  dot = fopen(dots[1],"r");

  if(!(dot=fopen(dots[1],"r"))){
    printf("Problema abriendoel archivo %s\n",dots[1]);
    exit(1);
  }

  //Número de objetos a analizar
  
  int n_stellar = count_lines(dot);
  
  //Número de galaxias
  
  int n_galaxy = n_stars/121;

  //Número de estrellas

  int n_stars=n_stellar - n_galaxy;

  //Arreglos que guardan las coordenadas los ID, posiciones y velocidades inciales en el archivo de entrada
  
  float *id, *x0, *y0, *v0x, *v0y;

  //Separación de espacio para guardar los datos de las condiciones inciales  
  
  id = malloc(n_stellar*sizeof(float));
  x0 = malloc(n_stellar*sizeof(float));
  y0 = malloc(n_stellar*sizeof(float));
  v0x = malloc(n_stellar*sizeof(float));
  v0y = malloc(n_stellar*sizeof(float));

  //Entero para recorrer un ciclo

  int i;

  //Intervalo entre cada punto de tiempo en Byr
  
  float h = pow(10,-6);
  
  //Número de puntos de tiempo

  float time = 5;/*En miles de millones años*/
  int n_points = ((time + h)/h);

  //Ciclo para guardar los datos en los arreglos anteriores

  for(i=0; i < n_points; i++){

    scanf(dot,"%f %f %f %f %f \n",&id[i],&x0[i],&y0[i],&v0x[i],&v0y[i]);
  }
  fclose(dot);

  //Arreglos para de los resultados obtenidos para x, y, V_x, V_y para los tiempos t = 1, 2, 3, 4, 5 (t está en Byr)

  float *t1_X,*t2_X,*t3_X,*t4_X,*t5_X;
  float *t1_y,*t2_y,*t3_y,*t4_y,*t5_y;
  float *t1_Vx,*t2_Vx,*t3_Vx,*t4_Vx,*t5_Vx;
  float *t1_Vy,*t2_Vy,*t3_Vy,*t4_Vy,*t5_Vy;

  t1_X=malloc(n_stellar*sizeof(float));
  t1_y=malloc(n_stellar*sizeof(float));
  t1_Vx=malloc(n_stellar*sizeof(float));
  t1_Vy=malloc(n_stellar*sizeof(float));

  t2_X=malloc(n_stellar*sizeof(float));
  t2_y=malloc(n_stellar*sizeof(float));
  t2_Vx=malloc(n_stellar*sizeof(float));
  t2_Vy=malloc(n_stellar*sizeof(float));

  t3_X=malloc(n_stellar*sizeof(float));
  t3_y=malloc(n_stellar*sizeof(float));
  t3_Vx=malloc(n_stellar*sizeof(float));
  t3_Vy=malloc(n_stellar*sizeof(float));

  t3_X=malloc(n_stellar*sizeof(float));
  t3_y=malloc(n_stellar*sizeof(float));
  t3_Vx=malloc(n_stellar*sizeof(float));
  t3_Vy=malloc(n_stellar*sizeof(float));

  t4_X=malloc(n_stars*sizeof(float));
  t4_y=malloc(n_stars*sizeof(float));
  t4_Vx=malloc(n_stars*sizeof(float));
  t4_Vy=malloc(n_stars*sizeof(float));

  t5_X=malloc(n_stellar*sizeof(float));
  t5_y=malloc(n_stellar*sizeof(float));
  t5_Vx=malloc(n_stellar*sizeof(float));
  t5_Vy=malloc(n_stellar*sizeof(float));

  

	//Arreglos para guardar las posiciones y velocidades de la i-ésima estrella durante los 5000 millones de años

	float *Xi;
	Xi = malloc(n_points*sizeof(float));

	float *Yi;
	Yi = malloc(n_points*sizeof(float));

	float *Vxi;
	Vxi = malloc(n_points*sizeof(float));

	float *Vyi;
	Vyi = malloc(n_points*sizeof(float));

	//Arreglo para el tiempo
	float *t;
	t = malloc(n_points*sizeof(float));

	//Condiciones iniciales 

	t[0]=0;
	Xi[0]=x0[i];
	Yi[0]=y0[i];
	Vxi[0]=v0x[i];
	Vyi[0]=v0y[i];

	//Ciclo para terminar de llenar los arreglos anteriores, resultado de aplicar el método de Runge Kutta de 4to orden

	int j;

	
  
  
  //Escritura del primer archivo

    FILE *in1;
    char filename1[25]="t1_output.dat";

    in1 = fopen(filename1,"w");

    if(!in1){
    printf("problems opening the file %s\n",filename1);
    exit(1);
    }

    for(i=0;i<n_points;i++){
      fprintf(in1, "%d\n", i);
    }
    
    fclose(in1);

  //Escritura del segundo archivo
    
    FILE *in2;
    char filename2[25]="t2_output.dat";

    in2 = fopen(filename2,"w");

    if(!in2){
    printf("problems opening the file %s\n", filename2);
    exit(1);
    }

    for(i=0;i<n_points;i++){
      fprintf(in2, "%d\n", i);
    }
    
    fclose(in2);

  //Escritura del tercer archivo

    FILE *in3;
    char filename3[25]="t3_output.dat";

    in3 = fopen(filename3,"w");

    if(!in3){
    printf("problems opening the file %s\n", filename3);
    exit(1);
    }

    for(i=0;i<n_points;i++){
      fprintf(in3, "%d\n", i);
    }
    
    fclose(in3);

  //Escritura del cuarto  archivo

    FILE *in4;
    char filename4[25]="t4_output.dat";

    in4 = fopen(filename4,"w");

    if(!in4){
    printf("problems opening the file %s\n", filename4);
    exit(1);
    }

    for(i=0;i<n_points;i++){
      fprintf(in4, "%d\n", i);
    }
    
    fclose(in4);

  //Escritura del quinto archivo

    FILE *in5;
    char filename5[25]="t5_output.dat";
    
    in5 = fopen(filename5,"w");

    if(!in5){
    printf("problems opening the file %s\n", filename5);
    exit(1);
    }

    for(i=0;i<n_points;i++){
      fprintf(in5, "%d\n", i);
    }
    
    fclose(in5);

  //Liberar espacio

    free(id);
    free(x0);
    free(y0);
    free(v0x);
    free(v0y);

  return 0;
}  
