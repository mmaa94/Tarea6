#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float first_derv(float x, float y1, float y2){

  return y2;
}

float second_derv(float x, float y1, float y2){

  return -4*(math.sin(y1));

}


float runge_kutta4( float x_old, float y1_old,float  y2_old, float h){
  
  //get the first derivatives

  y1_prime_1 = first_derv(x_old,y1_old, y2_old);
  y2_prime_1 = second_derv(x_old,y1_old, y2_old);

  //from this estimation move to the middle point
  x_mid = x_old+ (h/2.0);
  y1_mid = y1_old + (h/2.0) * y1_prime_1;
  y2_mid = y2_old + (h/2.0) * y2_prime_1; 

  //from this new points calculate primes

  y1_prime_2 = first_derv(x_mid,y1_mid, y2_mid);
  y2_prime_2 = second_derv(x_mid,y1_mid, y2_mid);

  //from this estimation move to the middle point

  x_mid1 = x_mid+ (h/2.0);
  y1_mid1 = y1_mid + (h/2.0) * y1_prime_2;
  y2_mid1 = y2_mid + (h/2.0) * y2_prime_2;

  //from this new points calculate primes 

  y1_prime_3 = first_derv(x_mid1,y1_mid1, y2_mid1);
  y2_prime_3 = second_derv(x_mid1,y1_mid1, y2_mid1);

  //from this estimation move to the next point

  x_mid2 = x_mid1+ h;
  y1_mid2 = y1_mid1 + h * y1_prime_3;
  y2_mid2 = y2_mid1 + h * y2_prime_3; 

  //last prime estimation 

  y1_prime_4 = first_derv(x_mid2,y1_mid2, y2_mid2);
  y2_prime_4 = second_derv(x_mid2,y1_mid2, y2_mid2);

  //averages 
  
  y1_prime_av=(1/6)*(y1_prime_1+(2*y1_prime_2)+(2*y1_prime_3)+y1_prime_4);
  y2_prime_av=(1/6)*(y2_prime_1+(2*y2_prime_2)+(2*y2_prime_3)+y2_prime_4);

}
