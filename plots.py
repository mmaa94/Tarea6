import pylab
import numpy

#El programa grafica la evolucion de la galaxia en 5000 millones de anos. 
#Autores: Nathalie Agudelo y  Maria M. Ariza Acero 
#Fecha de creacion: Oct/24/2013

#En este recorrido se extraen los datos de evolucion de la galaxia cada 5000 millones de anos

for i in range(5):

#Leyendo informacion de los archivos generados en evolve.c

    data_ev = numpy.loadtxt(open('evolution'+str(i+1)+'.txt', 'r'))
    x = data_ev[:,1]
    y = data_ev[:,2]

#Graficando las posiciones de las estrellas en un tiempo t
#Guardando graficas en archivos .jpg    
    
    pylab.plot(x,y)
    pylab.title('Evolucion de la galaxia en 5000 millones de anos')
    pylab.xlabel('x(t)')
    pylab.ylabel('y(t)')
    pylab.savefig('evolution'+str(i+1)+'.jpg')
    pylab.close()
    
 
