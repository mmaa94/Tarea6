#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "count_lines.h"
#include "sec_order.h"

/**
Módulo que contiene la función main para analizar los datos de un archivo de puntos y hacer lasolución usando Runge Kutta de cuarto orden.
Autores:Nathalie Agudelo Dueñas y  María M. Ariza Acero 
Fecha de creación: Oct  24 02:53:49 COT 2013
**/

float main(int argc, char **dots){

  //Comprobar el número de parámetros

  if(argc!=2){
	      printf("Los parámetros de entrada no son los requeridos");
	      exit(1);
	    }

  //Archivo 
  FILE *dot;
  dot=fopen(dots[1],"r");

  if(!(dot=fopen(argv[1],"r"))){
	      printf("Problema abriendoel archivo %s\n",argv[1]);
	      exit(1);
	    }

  //Número de objetos a analizar
  int n_stars=count_lines(dot);
  
  //Número de galaxias
  int n_galaxias=n_stars/121;

  //Arreglos que guardan las coordenadas los ID, posiciones y velocidades inciales en el archivo de entrada
  float *id, *x0, *y0, *v0x, *v0y;

  //Separación de espacio para guardar los datos de las condiciones inciales  
  id=malloc(n_stars*sizeof(float));
  x0=malloc(n_stars*sizeof(float));
  y0=malloc(n_stars*sizeof(float));
  v0x=malloc(n_stars*sizeof(float));
  v0y=malloc(n_stars*sizeof(float));

  //Entero para recorrer un ciclo
  int i;

  //Intervalo entre cada punto de tiempo
  float h=5000;
  
  //Número de puntos de tiempo

  float time=5*pow(10,9);
  int n_points=int((time+h)/h);


  //Arreglo para el tiempo

  float *t;
  t=malloc(50*sizeof(float));

  //Ciclo para llenar el arreglo del tiempo

  for(i=0; i<121; i++){
    
    t[i]=i;
  }

  //Ciclo para guardar los datos en los arregloa anteriores

  for(i=0;i<n_points;i++){

    scanf(dot,"%f %f %f %f %f \n",&id[i],&x0[i],&y0[i],,&v0x[i],&v0y[i]);
  }
  fclose(dot);

  //Ciclo para hacer el análisis conel modelode Runge Kutta en cada galaxia y para cada estrella
  for(i=0;i<n_galaxias;i++){

    //Entero para recorrer un ciclo
    int j;

    for(j=1;j=121;j++){

      float rg_4od[5];
      rg_4od=runge_kutta4(1,2,3,4,5);
    }
  }    
  
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
    
    in5 = fopen(t5_output,"w");

    if(!in5){
    printf("problems opening the file %s\n", filename5);
    exit(1);
    }

    for(i=0;i<n_points;i++){
      fprintf(in5, "%d\n", i);
    }
    
    fclose(in5);

  return 0;
}  
