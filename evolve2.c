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

  //Intervalo entre cada punto de tiempo en Gyr
  
  float h = pow(10,-5);
  
  //Número de puntos de tiempo

  float time = 5;/*En miles de millones años*/
  int n_points = ((time + h)/h);

  //Ciclo para guardar los datos en los arreglos anteriores

  for(i=0; i < n_points; i++){

    scanf(dot,"%f %f %f %f %f \n",&id[i],&x0[i],&y0[i],&v0x[i],&v0y[i]);
  }
  fclose(dot);

  //Arreglos de los resultados obtenidos para x, y, V_x, V_y para los tiempos t = 1, 2, 3, 4, 5 (t está en Gyr)

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

  //Análisis para cada estrella de una sola galaxia 

  if (n_galaxy==1){

    

  }
  if (n_galaxy==2){

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

float first_derv(z1){

  return z1;

}

//Segunda derivada (para cualquier ordenada (x,y) de una estrella) para una estrella

float second_derv_star1(float r1, float r2, float z1_1,float z1_2, int n_galaxia){
  /**
   Retorna la segunda derivada de la coordenada que entra 
  **/
  
  float interaction;

  if (n_galaxia==1){

    interaction = (G*M*(z1_1))/(pow(r1,3);

  }

  else{
  
    interaction = (G*M*(z1_1))/(pow(r1,3)+(G*M*(z1_2))/(pow(r2,3);
  }
 
  return interaction;

}

//Aproximación: Método Runge Kutta de 4to orden para cada coordenada

float *runge_kutta4(float t_old, float r1, float r2, float x1_old1, float x1_old2, float  x2_old, float y1_old1,float y1_old2, float y2_old, float h){

  /**
   Calcula el valor de la derivada en el punto usando la aproximación del método de Runge Kutta de 4to orden.
   Input: 
   -t_old: valor previo del tiempo
   -r1: valor de la distancia entre la estrella y el centro de la galaxia 1
   -r2: valor de la distancia entre la estrella y el centro de la galaxia 2
   -x1_old1: valor previo de x con respecto a la galaxia 1; o sea la posición en x
   -x1_old2: valor previo de x con respecto a la galaxia 2; o sea la posición en x
   -y1_old1: valor previo de y con respecto a la galaxia 1; o sea la posición en y
   -y1_old2: valor previo de y con respecto a la galaxia 2; o sea la posición en y
   -x2_old: valor previo de la primera derivada de x; o sea, la velocidad en x
   -y2_old: valor previo de la primera derivada de y; o sea, la velocidad en y
   -h: espacio entre cada tiempo
   Output:Arreglo con los nuevos valores de tiempo, las coordenadas x y y y sus respectivas derivadas
  **/

  //Declaración de variables

  float x1_prime_1, x2_prime_1, y1_prime_1, y2_prime_1, t_mid, x1_mid, x2_mid, y1_mid, y2_mid;
  float x1_prime_2, x2_prime_2, y1_prime_2, y2_prime_2, t_mid1, x1_mid1, x2_mid1, y1_mid1, y2_mid1;
  float x1_prime_3, x2_prime_3, y1_prime_3, y2_prime_3, t_mid2, x1_mid2, x2_mid2, y1_mid2, y2_mid2;
  float x1_prime_4, x2_prime_4, y1_prime_4, y2_prime_4;
  float x1_prime_av, x2_prime_av, y1_prime_av, y2_prime_av;
  
  //Se obtienen las primeras derivadas de x y y

  x1_prime_1 = first_derv(x2_old);
  x2_prime_1 = second_derv(r1,r2,x1_old1, x1_old2);

  y1_prime_1 = first_derv(y2_old);
  y2_prime_1 = second_derv(r1,r2,y1_old1, y1_old2);
  
  //De esta estimación, vamos al punto medio: tiempo medio, posición en x y y medias

  t_mid = t_old + (h/2.0);

  x1_mid = x1_old + (h/2.0) * x1_prime_1;
  x2_mid = x2_old + (h/2.0) * x2_prime_1;

  y1_mid = y1_old + (h/2.0) * y1_prime_1;
  y2_mid = y2_old + (h/2.0) * y2_prime_1;

  //Para estos nuevos puntos, se calcula la derivada

  x1_prime_2 = first_derv(x2_old);
  x2_prime_2 = second_derv(r,x1_old1, x1_old2);

  y1_prime_2 = first_derv(y2_old);
  y2_prime_2 = second_derv(r,y1_old1, y1_old2);

  //De esta estimación nos vamos al punto medio: tiempo medio, posición en x y y medias

  t_mid = t_old + (h/2.0);

  x1_mid1 = x1_old + (h/2.0) * x1_prime_2;
  x2_mid1 = x2_old + (h/2.0) * x2_prime_2;

  y1_mid1 = y1_old + (h/2.0) * y1_prime_2;
  y2_mid1 = y2_old + (h/2.0) * y2_prime_2;

  //Con estos nuevos puntos calculamos las derivadas 

  x1_prime_3 = first_derv(x2_mid1);
  x2_prime_3 = second_derv(r,x1_mid1, x2_mid1);

  y1_prime_3 = first_derv(y2_mid1);
  y2_prime_3 = second_derv(r,y1_mid1, y2_mid1);

  //Con esta estimación vamos al siguiente punto

  t_mid2 = t_old+ h;

  x1_mid2 = x1_old + h * x1_prime_3;
  x2_mid2 = x2_old + h * x2_prime_3;

  y1_mid2 = y1_old + h * y1_prime_3;
  y2_mid2 = y2_old + h * y2_prime_3;

  //last prime estimation 

  x1_prime_4 = first_derv(t_mid2,r,x1_mid2, x2_mid2);
  x2_prime_4 = second_derv(t_mid2,r,x1_mid2, x2_mid2);

  y1_prime_4 = first_derv(t_mid2,r,y1_mid2, y2_mid2);
  y2_prime_4 = second_derv(t_mid2,r,y1_mid2, y2_mid2);

  //averages 
  
  x1_prime_av=(1/6)*(x1_prime_1+(2*x1_prime_2)+(2*x1_prime_3)+x1_prime_4);
  x2_prime_av=(1/6)*(x2_prime_1+(2*x2_prime_2)+(2*x2_prime_3)+x2_prime_4);

  y2_prime_av=(1/6)*(y1_prime_1+(2*y1_prime_2)+(2*y1_prime_3)+y1_prime_4);
  y2_prime_av=(1/6)*(y2_prime_1+(2*y2_prime_2)+(2*y2_prime_3)+y2_prime_4);

  //new values 

  float x1_new,x2_new, y1_new,y2_new;

  x1_new=x1_old+(x1_prime_av*h);
  x2_new=x2_old+(x2_prime_av*h);
  y1_new=y1_old+(y1_prime_av*h);
  y2_new=y2_old+(y2_prime_av*h);

  //array of values to return 
 
  float *ans;
  ans=malloc(5*sizeof(float));
  
  //fill the array of values to return

  ans[0]=t_mid2;
  ans[1]=x1_new;
  ans[2]=x2_new;
  ans[3]=y1_new; 
  ans[4]=y2_new;

  return ans;
} 
