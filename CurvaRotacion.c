//Preguntas: Como quitar la primera linea del archivo dat, como terminar el c (llevamos buen proceso), para que sirve en que nos dan las unidaes de los M
#include <stdio.h>
#include<math.h>
int main(){


FILE *Datos;
Datos = fopen("RadialVelocities.dat", "r");   //Abrimos  el archivo
int i;

float * Velocidad_Rotacion = malloc(300*sizeof(float));
float * Radio = malloc(300*sizeof(float));
float * Todos = malloc(600*sizeof(float));
float * Modelo = malloc(300*sizeof(float));
float * Resta = malloc(300*sizeof(float));

for(i=0;i<600;i++){
	fscanf(Datos, "%f", &Todos[i]); 
}

int cont_1 = 0;
int cont_2 = 0;
int j;
for(j=0;j<600;j++)                                   
{
	if ( j % 2 != 0 ){
		Velocidad_Rotacion[cont_1]= Todos[j];
		cont_1 = cont_1 + 1;
	}
	if ( j % 2 == 0 ){
		Radio[cont_2]= Todos[j];
		cont_2 = cont_2 + 1;
	}
}
fclose(Datos);
printf("%f \n", Velocidad_Rotacion[299]);
printf("%f \n", Radio[299]);



float Bb = 0.2497;
float Bd = 5.16;
float Ad = 0.3105;
float Ah = 64.3;
float V;
float G = 1;
float chi_cuadrado;
float Mb;
float Md;
float Mh;
float agrega;
float x_old;
float x_new;
float Suma = 0;
float f_x_old ;
float f_x_new ;
float alpha;
float betha;

float Velocidad(float Mb, float Md, float Mh, float R)
{
	float V;
	V = ((pow(Mb,0.5))*(R)/pow((pow(R,2)+pow(Bb,2)),0.75)) + ((pow(Md,0.5))*(R)/ pow((pow(R,2)+pow(Bd+Ad,2)),0.75)) + ((pow(Mh,0.5))*(R)/pow((pow(R,2)+pow(Ah,2)),0.25));
	return V;  
}

while(chi_cuadrado>=0.1){   
                               
	Mb=drand48();//Verificar aqui entre que y que valores
	Md=drand48();
	Mh=drand48();

	for(i=0;i<300;i++){  //Crea el Y modelo entre 0 y 40 que son los rangos de la velocidades, el Y observado son mis datos 
		agrega = 40*drand48();
		Modelo[i] = agrega;
		}
	for(i=0;i<300;i++){  //Hace la resta para el chi cuadrado, Velocidad_Rotacion es mi Y observado
		agrega = Velocidad_Rotacion[i]-Modelo[i];
		Resta[i]= agrega;
		}
	for(i=0;i<300;i++){  // Hace la suma del arreglo resta
		Suma = Suma + Resta[i];
		}

	chi_cuadrado = (1.0/2.0)*pow(Suma,2);

	x_old = drand48();
	x_new = drand48();

	f_x_old = Velocidad(Mb,Md,Mh,x_old);
	f_x_new = Velocidad(Mb,Md,Mh,x_new);
	alpha = f_x_new/f_x_old;

	if(alpha>1){}
	if(alpha<1){
		betha = drand48();
		if(alpha>betha){
		
		}
	}
}


return 0;
}
