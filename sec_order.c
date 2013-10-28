#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
Módulo que contiene las funciones para desarrollar el Runge Kutta de cuarto orden.
Autores: Nathalie Aguedelo Dueñas y María M. Ariza Acero
Fecha de creación: Oct 22  21:43:35 COT 2013
**/

//Constante de gravitación universal en kpc*km²

#define G 4.80475E-6 

//Masa del CM de la galaxia
#define M pow(10,12)

//Primera derivada (para cualquier ordenada (x,y))
float first_derv(float t,float r, float z1, float z2){

  /**
   Retorna la primera derivada de la coordenada que entra 
  **/
  return z2;
}

//Segunda derivada (para cualquier ordenada (x,y)) 
float second_derv(float t,float r, float z1, float z2){

   /**
   Retorna la segunda derivada de la coordenada que entra 
  **/
  return (G*M*(z1))/(pow(r,3));

}

//Aproximación: Método Runge Kutta de 4to orden para cada coordenada
float *main( float t_old, float r, float x1_old,float  x2_old, float y1_old,float y2_old, float h){

  /**
   Calcula el valor de la derivada en el punto usando la aproximación del método de Runge Kutta de 4to orden.
   Input: 
   -t_old: valor previo del tiempo
   -r: valor de la distancia entre la estrella y el centro de masa
   -x1_old: valor previo de x
   -x2_old: valor previo de la primera derivada de x
   -y1_old: valor previo de y
   -y2_old: valor previo de la primera derivada de y
   -h: espacio en tre cada tiempo
   Output:Arreglo con los nuevos valores de tiempo, las coordenadas x y y y sus respectivas derivadas
  **/

  //variable declaration

  float x1_prime_1, x2_prime_1, y1_prime_1, y2_prime_1, t_mid, x1_mid, x2_mid, y1_mid, y2_mid;
  float x1_prime_2, x2_prime_2, y1_prime_2, y2_prime_2, t_mid1, x1_mid1, x2_mid1, y1_mid1, y2_mid1;
  float x1_prime_3, x2_prime_3, y1_prime_3, y2_prime_3, t_mid2, x1_mid2, x2_mid2, y1_mid2, y2_mid2;
  float x1_prime_4, x2_prime_4, y1_prime_4, y2_prime_4;
  float x1_prime_av, x2_prime_av, y1_prime_av, y2_prime_av;
  
  //get the first derivatives of x and y

  x1_prime_1 = first_derv(t_old,r,x1_old, x2_old);
  x2_prime_1 = second_derv(t_old,r,x1_old, x2_old);

  y1_prime_1 = first_derv(t_old,r,y1_old, y2_old);
  y2_prime_1 = second_derv(t_old,r,y1_old, y2_old);
  
  //from this estimation move to the middle point: middle time, middle x position and middle y position

  t_mid = t_old+ (h/2.0);

  x1_mid = x1_old + (h/2.0) * x1_prime_1;
  x2_mid = x2_old + (h/2.0) * x2_prime_1;

  y1_mid = y1_old + (h/2.0) * y1_prime_1;
  y2_mid = y2_old + (h/2.0) * y2_prime_1;

  //from this new points calculate primes

  x1_prime_2 = first_derv(t_mid,r,x1_old, x2_old);
  x2_prime_2 = second_derv(t_mid,r,x1_old, x2_old);

  y1_prime_2 = first_derv(t_mid,r,y1_old, y2_old);
  y2_prime_2 = second_derv(t_mid,r,y1_old, y2_old);

  //from this estimation move to the middle point: middle time, middle x position and middle y position

  t_mid2 = t_old+ (h/2.0);

  x1_mid1 = x1_old + (h/2.0) * x1_prime_2;
  x2_mid1 = x2_old + (h/2.0) * x2_prime_2;

  y1_mid1 = y1_old + (h/2.0) * y1_prime_2;
  y2_mid1 = y2_old + (h/2.0) * y2_prime_2;

  //from this new points calculate primes 

  x1_prime_3 = first_derv(t_mid1,r,x1_mid1, x2_mid1);
  x2_prime_3 = second_derv(t_mid1,r,x1_mid1, x2_mid1);

  y1_prime_3 = first_derv(t_mid1,r,y1_mid1, y2_mid1);
  y2_prime_3 = second_derv(t_mid1,r,y1_mid1, y2_mid1);

  //from this estimation move to the next point

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


