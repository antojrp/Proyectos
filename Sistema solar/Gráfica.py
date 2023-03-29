# -*- coding: utf-8 -*-
"""
Created on Thu Feb 23 00:10:15 2023

@author: ajrp
"""

import matplotlib.pyplot as plt
import numpy as np

#Numero de iteraciones realizado
p=3000

x=np.linspace(0, p, p+1)
y=[]
valido = False

# Leer datos de los ficheros y meterlos en los vectores
for line in open('Energia_planetas.dat', 'r'):
    lines = [i for i in line.split()]
    y.append(float(lines[0]))

plt.figure()
# Nombre eje x
plt.xlabel('Paso',fontsize=(20))
# Nombre eje y
plt.ylabel('Energia',fontsize=(20))
# Descripción del plot
plt.plot(x,y, "-", color='tomato')
plt.grid()
#Titulo de la gráfica
plt.title('Energia', fontsize=(24))
# Guardar y poner nombre de la gráfica
plt.savefig('fig_Energia.png',bbox_inches='tight')
plt.show()