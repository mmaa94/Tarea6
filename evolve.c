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

  //Ciclo para guardar los datos en los arreglos anteriores

  for(i=0;i<n_points;i++){

    scanf(dot,"%f %f %f %f %f \n",&id[i],&x0[i],&y0[i],,&v0x[i],&v0y[i]);
  }
  fclose(dot);

   //Intervalo entre cada punto de tiempo
  float h=5000;
  
  //Número de puntos de tiempo

  float time=5*pow(10,9);
  int n_points=int((time+h)/h);

  //Arreglos para de los resultados obtenidos para X, Y, Vx, Vy para los tiempos t=1E9, 2E9, 3E9,4E9, 5E9

  float *t_X;
  float *t_y;
  float *t_Vx;
  float *t_Vy;

  t_X=malloc(5*n_stars*sizeof(float));
  t_y=malloc(5*n_stars*sizeof(float));
  t_Vx=malloc(5*n_stars*sizeof(float));
  t_Vy=malloc(5*n_stars*sizeof(float));

  //Entero para recorrer un ciclo

  int i;

  //Análisis para cada estrella de una sóla galaxia 

  if(n_galaxias==1){
    
    //Ciclo para recorrer cada estrella

    for(i=0;i<120;i++){

      //Distancia de la órbita de la estrella al CM en kpc
      float r;
      
      //Órbita interna
      if(i<=11){
	r=10;
      }
      //Segunda órbita
      if(i>=12 && i<=29){
	r=20;
      }
      //Tercera órbita
      if(i>=30 && i<=53){
	r=30;
      }
      //Cuarta órbita
      if(i>=54 && i<=83){
	r=40;
      }
      //Órbita exterior
      if(i>=84 && i<=119){
	r=50;
      }

      //Arreglos para guardar las posiciones y velocidades de la i-ésima estrella durante los 5000' de años

      float *Xi;
      Xi=malloc(n_points*sizeof(float));

      float *Yi;
      Vxi=malloc(n_points*sizeof(float));

      float *Vxi;
      Vxi=malloc(n_points*sizeof(float));

      float *Vyi;
      Vyi=malloc(n_points*sizeof(float));

      //Arreglo para el tiempo
      float *ti;
      t=malloc(n_points*sizeof(float));

      //Condiciones iniciales 

      t[0]=0;
      Xi[0]=x0[i];
      Yi[0]=y0[i];
      Vxi[0]=v0x[i];
      Vyi[0]=v0y[i];

      //Ciclo para terminar de llenar los arreglos anteriores, resultado de aplicar el método de Runge Kutta de 4to orden

      int j;

      for(j=1;j=n_points;j++){

	float *rg_4j=main(t[j-1],r,Xi[j-1],Vxi[j-1],Yi[j-1],Vyi[j-1],h);//Main del módulo Runge Kutta 4to orden(sec_order.c)
	rg_4j[0]=t[j];
	rg_4j[1]=Xi[j];
	rg_4j[2]=Vxi[j];
	rg_4j[3]=Yi[j];
	rg_4j[4]=Vyi[j];

	/**
	if (rg_4j[0]==(1*pow(10,9))){

	  int k;
	  for(k=0;k<(5*n_stars);
	}
	**/
      }

      free(*t);
      free(*Xi);
      free(*Yi);
      free(*Vxi);
      free(*Vxi);
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

  //Liberar espacio

    free(*id);
    free(*x0);
    free(*y0);
    free(*v0x);
    free(*v0y);

  return 0;
}  
