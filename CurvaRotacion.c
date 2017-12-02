#include <stdio.h>
#include<math.h>
#include<stdlib.h>

double randn (double mu, double sigma) //Genera los aleatorios gaussianos, mu es media (centro) y sigma devsestandar(ancho) de la gaussiana
{
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;
 
  if (call)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }
 
  do
    {
      U1 = -1 + ((double) rand () / RAND_MAX) * 2;
      U2 = -1 + ((double) rand () / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }
  while (W >= 1 || W == 0);
 
  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;
 
  call = !call;
 
  return (mu + sigma * (double) X1);
}



int main(){

double drand48(void);
FILE *Datos;
Datos = fopen("RadialVelocities_2.dat", "r");   //Abrimos  el archivo
int i;

float * Velocidad_Rotacion = malloc(300*sizeof(float));
float * Radio = malloc(300*sizeof(float));
float * Todos = malloc(600*sizeof(float));
float * Modelo_nuevo = malloc(300*sizeof(float));
float * Resta_nuevo = malloc(300*sizeof(float));

float * Modelo_anterior = malloc(300*sizeof(float));
float * Resta_anterior = malloc(300*sizeof(float));

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


float Bb = 0.2497;
float Bd = 5.16;
float Ad = 0.3105;
float Ah = 64.3;
float V;
float G = 1;
float chi_cuadrado_nuevo;
float chi_cuadrado_anterior;
float Mb_nuevo;
float Md_nuevo;
float Mh_nuevo;
float Mb_anterior;
float Md_anterior;
float Mh_anterior;
float agrega_nuevo;
float agrega_anterior;
float x_old;
float x_new;
float Suma_nuevo = 0;
float Suma_anterior = 0;
float f_x_old ;
float f_x_new ;
float alpha;
float betha;

float Velocidad(float Mb, float Md, float Mh, float R)
{
	float V;
	V = ((pow(Mb,0.5))*(R)/pow((pow(R,2)+pow(Bb,2)),0.75)) + ((pow(Md,0.5))*(R)/ pow((pow(R,2)+pow(Bd+Ad,2)),0.75)) + ((pow(Mh,0.5))/pow((pow(R,2)+pow(Ah,2)),0.25));
	return V;  
}
Mb_anterior=randn(4000,100);  
Md_anterior=randn(4000,100);
Mh_anterior=randn(4000,100);

for(i=0;i<10000;i++){   
                               
	Mb_nuevo=randn(4000,100);
	Md_nuevo=randn(4000,100);
	Mh_nuevo=randn(4000,100);
	
		for(j=0;j<300;j++){  //Modelo (son los aleatorios) 
			Modelo_nuevo[j] = Velocidad(Mb_nuevo,Md_nuevo,Mh_nuevo,Radio[j]);
			Modelo_anterior[j] = Velocidad(Mb_anterior,Md_anterior,Mh_anterior,Radio[j]);
			}
		for(j=0;j<300;j++){  //Hace la resta para el chi cuadrado, Velocidad_Rotacion es mi Y observado
			agrega_nuevo = Velocidad_Rotacion[j]-Modelo_nuevo[j];
			Resta_nuevo[j]= agrega_nuevo;
			agrega_anterior = Velocidad_Rotacion[j]-Modelo_anterior[j];
			Resta_anterior[j] = agrega_anterior;
			}
		for(j=0;j<300;j++){  // Hace la suma del arreglo resta
			Suma_nuevo = Suma_nuevo + Resta_nuevo[j];
			Suma_anterior = Suma_anterior + Resta_anterior[j];
			}

		/*chi_cuadrado_nuevo = exp(-(1.0/2.0)*pow(Suma_nuevo,2)); //Este es sin Logaritmo
		chi_cuadrado_anterior = exp(-(1.0/2.0)*pow(Suma_anterior,2));


		alpha = chi_cuadrado_nuevo/chi_cuadrado_anterior;

		if(alpha>1){
		Mb_anterior=Mb_nuevo;
		Md_anterior=Md_nuevo;
		Mh_anterior=Mh_nuevo;
		}
		else{
			betha = drand48();
			if(alpha>betha){
			Mb_anterior=Mb_nuevo;
			Md_anterior=Md_nuevo;
			Mh_anterior=Mh_nuevo;
			}
			if(alpha<betha){
			Mb_anterior=Mb_anterior;
			Md_anterior=Md_anterior;
			Mh_anterior=Mh_anterior;
			}
		}
*/
		chi_cuadrado_nuevo = (-(1.0/2.0)*pow(Suma_nuevo,2)); //Este es con Logaritmo
		chi_cuadrado_anterior = (-(1.0/2.0)*pow(Suma_anterior,2));


		alpha = log(chi_cuadrado_nuevo/chi_cuadrado_anterior);

		if(alpha>0){ //0 porque logaritmo de 1 da 0
		Mb_anterior=Mb_nuevo;
		Md_anterior=Md_nuevo;
		Mh_anterior=Mh_nuevo;
		}
		else{
			betha = log(drand48());
			if(alpha>betha){
			Mb_anterior=Mb_nuevo;
			Md_anterior=Md_nuevo;
			Mh_anterior=Mh_nuevo;
			}
			if(alpha<betha){
			Mb_anterior=Mb_anterior;
			Md_anterior=Md_anterior;
			Mh_anterior=Mh_anterior;
			}
		}

	
}


printf("%s %f %s \n", "Mb =", Mb_anterior, "Mgal");
printf("%s %f %s \n", "Md =", Md_anterior, "Mgal");
printf("%s %f %s \n", "Mh =", Mh_anterior, "Mgal");

FILE* out = fopen("Datos_Ajuste.txt","w");
fprintf(out,"%f %f %f",Mb_anterior,Md_anterior,Mh_anterior);

return 0;
}


