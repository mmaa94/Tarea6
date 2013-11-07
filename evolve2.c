#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
Módulo que contiene la función main para analizar los datos de un archivo de puntos y hacer la solución usando Runge Kutta de cuarto orden.
Autores:Nathalie Agudelo Dueñas y  María M. Ariza Acero 
Fecha de creación: Nov 5 23:20:49 COT 2013
**/

#define M 1.0E12
#define G 4.80475E-6 //Valor de la constante de gravitación universal en kpc^3*Gyr^-2*Mo^-1, donde Gyr son miles de millones de años


float aceleracion (float C1, float C2, float c1, float c2){

  
  float An;
  float Dif_C1;
  float Dif_C2;
  Dif_C1=C1-c1;
  Dif_C2=C2-c2;
  An = ((G*M)*(Dif_C1)/sqrt(pow((pow(Dif_C1,2)+pow(Dif_C2,2)),3)));

  return An;
}

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
  
  int n_stellar = count_lines(dots[1]);
  
  //Número de galaxias
  
  int n_galaxy = n_stellar/121;

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
  
  float h = 1.0E-6;
  
  //Número de puntos de tiempo

  float time = 5.0; /*En miles de millones años*/
  int n_points = (time + h)/h;

   //Ciclo para guardar los datos en los arreglos anteriores

  for(i=0; i < n_stellar; i++){

    fscanf(dot,"%f %f %f %f %f \n",&id[i],&x0[i],&y0[i],&v0x[i],&v0y[i]);
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
      Xi[0]=x0[i]+1;
      Yi[0]=y0[i]+1;
      Vxi[0]=v0x[i]+1;
      Vyi[0]=v0y[i]+1;

      //printf("%f %f %f %f\n",Xi[0], Yi[0], Vxi[0], Vyi[0]);}}

      int j;

      if(i==0){

	for(j=1;j<n_points;j++){

	  t[j]=t[j-1]+h;
	  Vxi[j]=Vxi[0];
	  Xi[j]=Xi[j-1]+(h*Vxi[0]);
	  Vyi[j]=Vyi[0];
	  Yi[j]=Yi[j-1]+(h*Vyi[0]);
	  printf("%f %f %f %f\n",Xi[j], Yi[j], Vxi[j], Vyi[j]);
	}
      }
      
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
            
      //      fprintf(out,"%d %f %f %f %f \n",i,Xi[(n_points/5)-1],Yi[(n_points/5)-1],Vxi[(n_points/5)-1],Vyi[(n_points/5)-1]);
      fprintf(out,"%d %f %f %f %f \n",i,Xi[1],Yi[1],Vxi[1],Vyi[1]);
      
      fclose(out);
      
      out=fopen("evolution2.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[(2*n_points/5)-1],Yi[(2*n_points/5)-1],Vxi[(2*n_points/5)-1],Vyi[(2*n_points/5)-1]);
      
      fclose(out);
      
      out=fopen("evolution3.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[(3*n_points/5)-1],Yi[(3*n_points/5)-1],Vxi[(3*n_points/5)-1],Vyi[(3*n_points/5)-1]);
      
      fclose(out);
      
      out=fopen("evolution4.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[(4*n_points/5)-1],Yi[(4*n_points/5)-1],Vxi[(4*n_points/5)-1],Vyi[(4*n_points/5)-1]);
      
      fclose(out);
      
      out=fopen("evolution5.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[n_points-1],Yi[n_points-1],Vxi[n_points-1],Vyi[n_points-1]);
      
      fclose(out);
      
      free(t);
      free(Xi);
      free(Yi);
      free(Vxi);
      free(Vyi);
      }
  }
  

  if (n_galaxy==2){

    int j;

  for(i=0;i<n_stellar;i++){

    if(i!=0 && i!= 122){

      FILE *out;
      t = malloc(n_points*sizeof(float));

      //Arreglos para guardar la evolución de la estrella i 

      float *Xi,*Yi, *Vxi, *Vyi;

      Xi = malloc(n_points*sizeof(float));
      Yi = malloc(n_points*sizeof(float));
      Vxi = malloc(n_points*sizeof(float));
      Vyi = malloc(n_points*sizeof(float));

      //Inicialización

      t[0] = 0.0;
      Xi[0]=x0[i];
      Yi[0]=y0[i];
      Vxi[0]=v0x[i];
      Vyi[0]=v0y[i];

     //Arreglos para guardar la evolución de las galaxia 1 en el tiempo

     float *Xi_1,*Yi_1, *Vxi_1, *Vyi_1;

     Xi_1 = malloc(n_points*sizeof(float));
     Yi_1 = malloc(n_points*sizeof(float));
     Vxi_1 = malloc(n_points*sizeof(float));
     Vyi_1 = malloc(n_points*sizeof(float));

     //Arreglos para guardar la evolución de las galaxia 1 en el tiempo

     float *Xi_2,*Yi_2, *Vxi_2, *Vyi_2;

     Xi_2 = malloc(n_points*sizeof(float));
     Yi_2 = malloc(n_points*sizeof(float));
     Vxi_2 = malloc(n_points*sizeof(float));
     Vyi_2 = malloc(n_points*sizeof(float));

     //Inicialización 

     Xi_1[0]=x0[0];
     Yi_1[0]=y0[0];
     Vxi_1[0]=v0x[0];
     Vyi_1[0]=v0y[0];

     Xi_2[0]=x0[122];
     Yi_2[0]=y0[122];
     Vxi_2[0]=v0x[122];
     Vyi_2[0]=v0y[122];

     for(j=1;j<n_points;j++){
	  
	float To = t[j-1]; //Instante inicial
	float Tn = To;
	float Xn=Xi[j-1]; //Posición inicial en x de la estrella
	float Yn=Yi[j-1]; //Posición inicial en y de la estrella
	float Xn_1 = Xi_1[j-1]; //Posición inicial en x para la galaxia 1
	float Yn_1 = Yi_1[j-1]; //Posición inicial en y para la galaxia 1
	float Xn_2 = Xi_2[j-1]; //Posición inicial en x para la galaxia 2
	float Yn_2 = Yi_2[j-1]; //Posición inicial en y para la galaxia 2
	float Vxn=Vxi[j-1]; //Velocidad inicial en x de la estrella
	float Vyn=Vyi[j-1]; //Velocidad inicial en y de la estrella 
	float Vxn_1 = Vxi_1[j-1]; //Velocidad inicial en x para la galaxia 1
	float Vyn_1 = Vyi_1[j-1]; //Velocidad inicial en y  parala galaxia 1
	float Vxn_2 = Vxi_2[j-1]; //Velocidad inicial en x para la galaxia 2
	float Vyn_2 = Vyi_2[j-1]; //Velocidad inicial en y  parala galaxia 2
	float Axn;
	float Ayn;
	float Axn_1;
	float Ayn_1;
	float Axn_2;
	float Ayn_2;
	float T,X,Y, X_1, Y_1, X_2, Y_2,Vx,Vy, Vx_1, Vy_1, Vx_2, Vy_2;
	float K1x, L1x, K2x, L2x, K3x, L3x, K4x, L4x, Kx, Lx;
	float K1y, L1y, K2y, L2y, K3y, L3y, K4y, L4y, Ky, Ly;
	float K1x_1, L1x_1, K2x_1, L2x_1, K3x_1, L3x_1, K4x_1, L4x_1, Kx_1, Lx_1;
	float K1x_2, L1x_2, K2x_2, L2x_2, K3x_2, L3x_2, K4x_2, L4x_2, Kx_2, Lx_2;
	float K1y_1, L1y_1, K2y_1, L2y_1, K3y_1, L3y_1, K4y_1, L4y_1, Ky_1, Ly_1;
	float K1y_2, L1y_2, K2y_2, L2y_2, K3y_2, L3y_2, K4y_2, L4y_2, Ky_2, Ly_2;
   
	//Al comienzo del intervalo
	
	T = Tn;
	X=Xn;
	Y=Yn;
	Vx=Vxn;
	Vy=Vyn;
	X_1 = Xn_1;
	Y_1 = Yn_1;
	Vx_1 = Vxn_1;
	Vy_1 = Vyn_1;
	X_2 = Xn_2;
	Y_2 = Yn_2;
	Vx_2 = Vxn_2;
	Vy_2 = Vyn_2;
	Axn = aceleracion(X_1,Y_1 ,X,Y) + aceleracion(X_2,Y_2,X,Y);
	Ayn = aceleracion(Y_1, X_1, Y, X)+aceleracion(Y_2, X_2, Y,X);
	Axn_1 = aceleracion(X_2,Y_2,X_1,Y_1);
	Ayn_1 = aceleracion(Y_2,X_2,Y_1,X_1);
	Axn_2 = aceleracion(X_1,Y_1,X_2,Y_2);
	Ayn_2 = aceleracion(Y_1,X_1,Y_2,X_2);
	K1x = Vx*h;
	L1x = Axn*h;
	K1y = Vy*h;
	L1y = Ayn*h;
	K1x_1=Vx_1*h;
	L1x_1=Axn_1*h;
	K1y_1=Vy_1*h;
	L1y_1=Ayn_1*h;
	K1x_2=Vx_2*h;
	L1x_2=Axn_2*h;
	K1y_2=Vy_2*h;
	L1y_2=Ayn_2*h;	

	//En el centro del intervalo

	T = Tn + 0.5*h;
	X = Xn + 0.5*K1x;
	Y = Yn + 0.5*K1y;
	Vx = Vxn + 0.5*L1x;
	Vy = Vyn + 0.5*L1y;
	X_1=Xn_1+0.5*K1x_1;
	Y_1=Yn_1+0.5*K1y_1;
	Vx_1=Vxn_1+0.5*L1x_1;
	Vy_1=Vyn_1+0.5*L1y_1;
	X_2=Xn_2+0.5*K1x_2;
	Y_2=Yn_2+0.5*K1y_2;
	Vx_2=Vxn_2+0.5*L1x_2;
	Vy_2=Vyn_2+0.5*L1y_2;
	Axn = aceleracion(X_1,Y_1 ,X,Y) + aceleracion(X_2,Y_2,X,Y);
	Ayn = aceleracion(Y_1, X_1, Y, X)+aceleracion(Y_2, X_2, Y,X);
	Axn_1 = aceleracion(X_2,Y_2,X_1,Y_1);
	Ayn_1 = aceleracion(Y_2,X_2,Y_1,X_1);
	Axn_2 = aceleracion(X_1,Y_1,X_2,Y_2);
	Ayn_2 = aceleracion(Y_1,X_1,Y_2,X_2);
	K2x = Vx*h;
	L2x = Axn*h;
	K2y = Vy*h;
	L2y = Ayn*h;
	K2x_1=Vx_1*h;
	L2x_1=Axn_1*h;
	K2y_1=Vy_1*h;
	L2y_1=Ayn_1*h;
	K2x_2=Vx_2*h;
	L2x_2=Axn_2*h;
	K2y_2=Vy_2*h;
	L2y_2=Ayn_2*h;

	//En el centro del intervalo

	T = Tn+ h;
	X = Xn + 0.5*K2x;
	Y = Yn + 0.5*K2y;
	Vx = Vxn + 0.5*L2x;
	Vy = Vyn + 0.5*L2y;
	X_1=Xn_1+0.5*K2x_1;
	Y_1=Yn_1+0.5*K2y_1;
	Vx_1=Vxn_1+0.5*L2x_1;
	Vy_1=Vyn_1+0.5*L2y_1;
	X_2=Xn_2+0.5*K2x_2;
	Y_2=Yn_2+0.5*K2y_2;
	Vx_2=Vxn_2+0.5*L2x_2;
	Vy_2=Vyn_2+0.5*L2y_2;
	Axn = aceleracion(X_1,Y_1 ,X,Y) + aceleracion(X_2,Y_2,X,Y);
	Ayn = aceleracion(Y_1, X_1, Y, X)+aceleracion(Y_2, X_2, Y,X);
	Axn_1 = aceleracion(X_2,Y_2,X_1,Y_1);
	Ayn_1 = aceleracion(Y_2,X_2,Y_1,X_1);
	Axn_2 = aceleracion(X_1,Y_1,X_2,Y_2);
	Ayn_2 = aceleracion(Y_1,X_1,Y_2,X_2);
	K3x = Vx*h;
	L3x = Axn*h;
	K3y = Vy*h;
	L3y = Ayn*h;
	K3x_1=Vx_1*h;
	L3x_1=Axn_1*h;
	K3y_1=Vy_1*h;
	L3y_1=Ayn_1*h;
	K3x_2=Vx_2*h;
	L3x_2=Axn_2*h;
	K3y_2=Vy_2*h;
	L3y_2=Ayn_2*h;

	//Al final del intervalo
	
	T=Tn+h;
	X = Xn + 0.5*K3x;
	Y = Yn + 0.5*K3y;
	Vx = Vxn + 0.5*L3x;
	Vy = Vyn + 0.5*L3y;
	X_1=Xn_1+0.5*K3x_1;
	Y_1=Yn_1+0.5*K3y_1;
	Vx_1=Vxn_1+0.5*L3x_1;
	Vy_1=Vyn_1+0.5*L3y_1;
	X_2=Xn_2+0.5*K3x_2;
	Y_2=Yn_2+0.5*K3y_2;
	Vx_2=Vxn_2+0.5*L3x_2;
	Vy_2=Vyn_2+0.5*L3y_2;
	Axn = aceleracion(X_1,Y_1 ,X,Y) + aceleracion(X_2,Y_2,X,Y);
	Ayn = aceleracion(Y_1, X_1, Y, X)+aceleracion(Y_2, X_2, Y,X);
	Axn_1 = aceleracion(X_2,Y_2,X_1,Y_1);
	Ayn_1 = aceleracion(Y_2,X_2,Y_1,X_1);
	Axn_2 = aceleracion(X_1,Y_1,X_2,Y_2);
	Ayn_2 = aceleracion(Y_1,X_1,Y_2,X_2);
	K4x = Vx*h;
	L4x = Axn*h;
	K4y = Vy*h;
	L4y = Ayn*h;
	K4x_1=Vx_1*h;
	L4x_1=Axn_1*h;
	K4y_1=Vy_1*h;
	L4y_1=Ayn_1*h;
	K4x_2=Vx_2*h;
	L4x_2=Axn_2*h;
	K4y_2=Vy_2*h;
	L4y_2=Ayn_2*h;

	//Se obtienen los valores para K y L

	Kx = (K4x + 2*K3x + 2*K2x + K1x)/6;
	Ky = (K4y + 2*K3y + 2*K2y + K1y)/6;
	Lx = (L4x + 2*L3x + 2*L2x + L1x)/6;
	Ly = (L4y + 2*L3y + 2*L2y + L1y)/6;
	Kx_1 = (K4x_1 + 2*K3x_1 + 2*K2x_1 + K1x_1)/6;
	Ky_1 = (K4y_1 + 2*K3y_1 + 2*K2y_1 + K1y_1)/6;
	Lx_1 = (L4x_1 + 2*L3x_1 + 2*L2x_1 + L1x_1)/6;
	Ly_1 = (L4y_1 + 2*L3y_1 + 2*L2y_1 + L1y_1)/6;
	Kx_2 = (K4x_2 + 2*K3x_2 + 2*K2x_2 + K1x_2)/6;
	Ky_2 = (K4y_2 + 2*K3y_2 + 2*K2y_2 + K1y_2)/6;
	Lx_2 = (L4x_2 + 2*L3x_2 + 2*L2x_2 + L1x_2)/6;
	Ly_2 = (L4y_2 + 2*L3y_2 + 2*L2y_2 + L1y_2)/6;
	

	t[j] = T;
	Xi[j] = Kx;
	Yi[j] = Ky;
	Vxi[j] = Lx;
	Vyi[j] = Ly;
	Xi_1[j] = Kx_1;
	Yi_1[j] = Ky_1;
	Vxi_1[j] = Lx_1;
	Vyi_1[j] = Ly_1;
	Xi_2[j] = Kx_2;
	Yi_2[j] = Ky_2;
	Vxi_2[j] = Lx_2;
	Vyi_2[j] = Ly_2;

     }
	
	if(i==1){

	  out=fopen("evolution1.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_1[(n_points/5)-1],Yi_1[(n_points/5)-1],Vxi_1[(n_points/5)-1],Vyi_1[(n_points/5)-1]);
      
	  fclose(out);

	  out=fopen("evolution2.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_1[(2*n_points/5)-1],Yi_1[(2*n_points/5)-1],Vxi_1[(2*n_points/5)-1],Vyi_1[(2*n_points/5)-1]);
      
	  fclose(out);

	  out=fopen("evolution3.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_1[(3*n_points/5)-1],Yi_1[(3*n_points/5)-1],Vxi_1[(3*n_points/5)-1],Vyi_1[(3*n_points/5)-1]);
      
	  fclose(out);

	  out=fopen("evolution4.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_1[(4*n_points/5)-1],Yi_1[(4*n_points/5)-1],Vxi_1[(4*n_points/5)-1],Vyi_1[(4*n_points/5)-1]);
      
	  fclose(out);

	  out=fopen("evolution5.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_1[(n_points)-1],Yi_1[(n_points)-1],Vxi_1[(n_points)-1],Vyi_1[(n_points)-1]);
      
	  fclose(out);
	}

	if(i==123){
	  
	  out=fopen("evolution1.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_2[(n_points/5)-1],Yi_2[(n_points/5)-1],Vxi_2[(n_points/5)-1],Vyi_2[(n_points/5)-1]);
      
	  fclose(out);

	  out=fopen("evolution2.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_2[(2*n_points/5)-1],Yi_2[(2*n_points/5)-1],Vxi_2[(2*n_points/5)-1],Vyi_2[(2*n_points/5)-1]);
      
	  fclose(out);

	  out=fopen("evolution3.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_2[(3*n_points/5)-1],Yi_2[(3*n_points/5)-1],Vxi_2[(3*n_points/5)-1],Vyi_2[(3*n_points/5)-1]);
      
	  fclose(out);

	  out=fopen("evolution4.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_2[(4*n_points/5)-1],Yi_2[(4*n_points/5)-1],Vxi_2[(4*n_points/5)-1],Vyi_2[(4*n_points/5)-1]);
      
	  fclose(out);

	  out=fopen("evolution5.txt","a");
            
	  fprintf(out,"%d %f %f %f %f \n",i-1,Xi_2[(n_points)-1],Yi_2[(n_points)-1],Vxi_2[(n_points)-1],Vyi_2[(n_points)-1]);
      
	  fclose(out);
	  
	}
             
      out=fopen("evolution1.txt","a");
            
      fprintf(out,"%d %f %f %f %f \n",i,Xi[(n_points/5)-1],Yi[(n_points/5)-1],Vxi[(n_points/5)-1],Vyi[(n_points/5)-1]);
      
      fclose(out);
      
      out=fopen("evolution2.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[(2*n_points/5)-1],Yi[(2*n_points/5)-1],Vxi[(2*n_points/5)-1],Vyi[(2*n_points/5)-1]);
      
      fclose(out);
      
      out=fopen("evolution3.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[(3*n_points/5)-1],Yi[(3*n_points/5)-1],Vxi[(3*n_points/5)-1],Vyi[(3*n_points/5)-1]);
      
      fclose(out);
      
      out=fopen("evolution4.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[(4*n_points/5)-1],Yi[(4*n_points/5)-1],Vxi[(4*n_points/5)-1],Vyi[(4*n_points/5)-1]);
      
      fclose(out);
      
      out=fopen("evolution5.txt","a");
      
      fprintf(out,"%d %f %f %f %f\n",i,Xi[n_points-1],Yi[n_points-1],Vxi[n_points-1],Vyi[n_points-1]);
      
      fclose(out);
      
      //Liberar espacio
      free(t);
      free(Xi);
      free(Yi);
      free(Vxi);
      free(Vyi);
      free(Xi_1);
      free(Xi_2);
      free(Yi_1);
      free(Yi_2);
      free(Vxi_1);
      free(Vxi_2);
      free(Vyi_1);
      free(Vyi_2);
      
    }
  }
  }
  
  //Liberar espacio

    free(id);
    free(x0);
    free(y0);
    free(v0x);
    free(v0y);
     
  return 0.0;
}  


