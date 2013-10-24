#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "potencial.h"
#include "calcular_potencial.h"

"""
Módulo que contiene la función main para analizar los datos de un archivo de puntos y hacer lasolución usando Runge Kutta de cuarto orden.
Autores:Nathalie Agudelo Dueñas y  María M. Ariza Acero 
Fecha de creación: Oct  24 02:53:49 COT 2013
"""

float main(int argc, char **dots){

  //Comprobar el número de parámetros

  if(argc!=2){
	      printf("Los parámetros de entrada no son los requeridos");
	      exit(1);
	    }

  //Archivo 
  FILE *dot;
  dot=fopen(dots[1],"r");
  if(!(vocales=fopen(argv[1],"r"))){
	      printf("Problema abriendoel archivo %s\n",argv[1]);
	      exit(1);
	    }
