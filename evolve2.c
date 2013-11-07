#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "count_lines.h"

/**
Módulo que contiene la función main para analizar los datos de un archivo de puntos y hacer la solución usando Runge Kutta de cuarto orden.
Autores:Nathalie Agudelo Dueñas y  María M. Ariza Acero 
Fecha de creación: Nov 5 23:20:49 COT 2013
**/

#define M 1.0E12
#define G 4.80475E-6 //Valor de la constante de gravitación universal en kpc^3*Gyr^-2*Mo^-1, donde Gyr son miles de millones de años

float aceleracion (float C1, float C2, float c1, float c2){

  float An = ((G*M)(C1-c1)/pow((pow((C1-c1),2)+pow((C2-c2),2))),(3/2));

  return An;
}

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

  int n_stars = n_stellar - n_galaxy;

  //Arreglos que guardan las coordenadas los ID, posiciones, velocidades inciales en el archivo de entrada  y los tiempos de evolución 
  
  float *id, *x0, *y0, *v0x, *v0y, *t;

  //Separación de espacio para guardar los datos de las condiciones inciales 
  
  id = malloc(n_stellar*sizeof(float));
  x0 = malloc(n_stellar*sizeof(float));
  y0 = malloc(n_stellar*sizeof(float));
  v0x = malloc(n_stellar*sizeof(float));
  v0y = malloc(n_stellar*sizeof(float));
 
  //Entero para recorrer un ciclo

  int i;

  //Intervalo entre cada punto de tiempo en Gyr
  
  float h = pow(10,-6);
  
  //Número de puntos de tiempo

  float time = 5; /*En miles de millones años*/
  int n_points = (time + h)/h;

   //Ciclo para guardar los datos en los arreglos anteriores

  for(i=0; i < n_stellar; i++){

    scanf(dot,"%f %f %f %f %f \n",&id[i],&x0[i],&y0[i],&v0x[i],&v0y[i]);
  }
  fclose(dot);

  //Análisis para cada estrella de una sola galaxia 

  if (n_galaxy==1){
    
    //Inicialización de variables
    for(i=0; i < n_stellar; i++){
      
      FILE *out;
      t = malloc(n_points*sizeof(float));

      float *Xi,*Yi, *Vxi, *Vyi;

      Xi = malloc(n_points*sizeof(float));
      Yi = malloc(n_points*sizeof(float));
      Vxi = malloc(n_points*sizeof(float));
      Vyi = malloc(n_points*sizeof(float));

      t[0] = 0.0;
      Xi[0]=x0[i];
      Yi[0]=y0[i];
      Vxi[0]=v0x[i];
      Vyi[0]=v0y[i];

      int j;

      if(i==0){

	for(j=1;j<n_points;j++){

	  t[j]=t[j-1]+h;
	  Vxi[j]=Vxi[0];
	  Xi[j]=Xi[j-1]+(h*Vxi[0]);
	  Vyi[j]=Vyi[0];
	  Yi[j]=Yi[j-1]+(h*Vyi[0]);
      
      
      //Runge Kutta
      
      for(j=1;j<n_points;j++){

	if(i!=0){

	float Xc = x0[0]; //Posición inicial en x del centro
	float Yc = y0[0]; //Posición inicial en y del centro
	float To = t[j-1]; //Instante inicial
	float Tn = To; 
	float Xn = Xi[j-1]; //Posición inicial en x
	float Yn = Yi[j-1]; //Posición inicial en y
	float Vxn = Vxi[j-1]; //Velocidad inicial en x
	float Vyn = Vyi[j-1]; //Velocidad inicial en y
	float Axn;
	float Ayn;
	float T, X, Y, Vx, Vy;
	float K1x, L1x, K2x, L2x, K3x, L3x, K4x, L4x, Kx, Lx;
	float K1y, L1y, K2y, L2y, K3y, L3y, K4y, L4y, Ky, Ly;
   
	 
	//Al comienzo del intervalo
	
	T = Tn;
	X = Xn;
	Y = Yn;
	Vx = Vxn;
	Vy = Vyn;
	Axn = aceleracion(Xc, Yc, X, Y);
	Ayn = aceleracion(Yc, Xc, Y, X);
	K1x = Vx*h;
	L1x = Axn*h;
	K1y = Vy*h;
	L1y = Ayn*h;

	//En el centro del intervalo

	T = Tn + 0.5*h;
	X = Xn + 0.5*K1x;
	Y = Yn + 0.5*K1y;
	Vx = Vxn + 0.5*L1x;
	Vy = Vyn + 0.5*L1y;
	Axn = aceleracion(Xc, Yc, X, Y);
	Ayn = aceleracion(Yc, Xc, Y, X);
	K2x = Vx*h;
	L2x = Axn*h;
	K2y = Vy*h;
	L2y = Ayn*h;

	//En el centro del intervalo

	T = Tn + h;
	X = Xn + 0.5*K2x;
	Y = Yn + 0.5*K2y;
	Vx = Vxn + 0.5*L2x;
	Vy = Vyn + 0.5*L2y;
	Axn = aceleracion(Xc, Yc, X, Y);
	Ayn = aceleracion(Yc, Xc, Y, X);
	K3x = Vx*h;
	L3x = Axn*h;
	K3y = Vy*h;
	L3y = Ayn*h;

	//Al final del intervalo

	T = Tn + h;
	X = Xn + 0.5*K3x;
	Y = Yn + 0.5*K3y;
	Vx = Vxn + 0.5*L3x;
	Vy = Vyn + 0.5*L3y;
	Axn = aceleracion(Xc, Yc, X, Y);
	Ayn = aceleracion(Yc, Xc, Y, X);
	K4x = Vx*h;
	L4x = Axn*h;
	K4y = Vy*h;
	L4y = Ayn*h;

	//Se obtienen los valores para K y L

	Kx = (K4x + 2*K3x + 2*K2x + K1x)/6;
	Ky = (K4y + 2*K3y + 2*K2y + K1y)/6;
	Lx = (L4x + 2*L3x + 2*L2x + L1x)/6;
	Ly = (L4y + 2*L3y + 2*L2y + L1y)/6;

	t[j] = T;
	Xi[j] = Kx;
	Yi[j] = Ky;
	Vxi[j] = Lx;
	Vyi[j] = Ly;
	}
      }
      
      out=fopen("evolution1.txt","a");
            
      fprintf(out,"%d %f %f %f %f \n",i,Xi[1000000],Yi[1000000],Vxi[1000000],Vyi[1000000]);
      
      fclose(out);
      
      out=fopen("evolution2.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[1000000*2],Yi[1000000*2],Vxi[1000000*2],Vyi[1000000*2]);
      
      fclose(out);
      
      out=fopen("evolution3.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[1000000*3],Yi[1000000*3],Vxi[1000000*3],Vyi[1000000*3]);
      
      fclose(out);
      
      out=fopen("evolution4.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[1000000*4],Yi[1000000*4],Vxi[1000000*4],Vyi[1000000*4]);
      
      fclose(out);
      
      out=fopen("evolution5.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[1000000*5],Yi[1000000*5],Vxi[1000000*5],Vyi[1000000*5]);
      
      fclose(out);
      
      free(t);
      free(Xi);
      free(Yi);
      free(Vxi);
      free(Vyi);
  }
 

    // if (n_galaxy==2){

  //}
  
  //Liberar espacio

    free(id);
    free(x0);
    free(y0);
    free(v0x);
    free(v0y);

  return 0;
}  

