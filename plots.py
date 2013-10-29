import pylab
import numpy

"""
El programa grafica la evolución de la galaxia en 5000 millones de años. 
Autores: Nathalie Agudelo Dueñas y  María M. Ariza Acero 
Fecha de creación: Oct/24/2013
"""

#En este recorrido se extraen los datos de evolución de la galaxia cada 5000 millones de años

for i in range(5):

#Leyendo información de los archivos generados en evolve.c

    data_ev = numpy.loadtxt(open('filename(i)'+'.txt', 'r'))
    x = data_ev[:,1]
    y = data_ev[:,2]

#Graficando las posiciones de las estrellas en un tiempo t
#Guardando gráficas en archivos .jpg    
    
    pylab.plot(x,y)
    pylab.savefig('evolution(i)'+'.jpg')
    pylab.title('Evolución de la galaxia en 5000 millones de años')
    pylab.xlabel('x(t)')
    pylab.ylabel('y(t)')
    pylab.close()
    
 
