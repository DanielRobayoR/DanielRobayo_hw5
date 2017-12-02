import numpy as np
import matplotlib.pyplot as plt

Datos = np.genfromtxt('RadialVelocities.dat')
Parametros = np.genfromtxt('Datos_Ajuste.txt')

x = Datos[:,0]
y = Datos[:,1]

M_b = Parametros[0]
M_d = Parametros[1]
M_h = Parametros[2]



Velocidad_Ajuste = np.zeros(300)

def ajustado(Mb,Md,Mh,R):
	Bb = 0.2497;
	Bd = 5.16;
	Ad = 0.3105;
	Ah = 64.3;
	V = ((Mb**0.5)*(R)/(R**2+Bb**2)**0.75) + ((Md**0.5)*(R)/ (R**2+(Bd+Ad)**2)**0.75) + ((Mh**0.5)/(R**2+Ah**2)**0.25)
	return V

for i in range(0,300):
	Velocidad_Ajuste[i] = ajustado(M_b,M_d,M_h,x[i])


plt.figure()
plt.scatter(x, y, label='Observado', c='blue')
plt.plot(x, Velocidad_Ajuste, label='Modelo', c='Red')
plt.legend()
plt.xlabel('Radio(kpc)')
plt.ylabel('Velocidad de Rotacion(km/s)')
plt.savefig("figura.png")
