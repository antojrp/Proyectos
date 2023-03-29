# include <iostream>
# include <cmath>
# include <fstream>
using namespace std;

void reescalar(double r[][2], double v[][2], double m[], int n)
{
  double c=1.496e11, ms, G=6.6743e-11;
  ms=m[0];
  for(int i=0; i < n ; i++)
  {
    r[i][0]=r[i][0]/c;
    r[i][1]=r[i][1]/c;
    v[i][0]=v[i][0]/sqrt(G*ms/c);
    v[i][1]=v[i][1]/sqrt(G*ms/c);
    m[i]=m[i]/ms;
  }
  return;
}

//
void gravitacion(double r[][2], double a[][2], double m[], int n)
{ 
  double sumax=0, sumay=0, distancia=0;
  for(int i=0; i < n ; i++)
  {
    sumax = 0;
    sumay = 0;
    for(int j=0; j < n ; j++)
    {
      if( j != i )
      {

        distancia=sqrt(pow(r[i][0]-r[j][0],2)+pow(r[i][1]-r[j][1],2));
        sumax=sumax+m[j]*(r[i][0]-r[j][0])/pow(distancia,3);
        sumay=sumay+m[j]*(r[i][1]-r[j][1])/pow(distancia,3);

      }
    }
    a[i][0] = -sumax;
    a[i][1] = -sumay;
  }
  return;
}

void verlet(double r[][2], double v[][2], double a[][2], double m[], double h, int n)
{
   double w[n][2];
   for(int i=0; i < n ; i++)
   {
      r[i][0]=r[i][0]+h*v[i][0]+h*h*a[i][0]/2;
      r[i][1]=r[i][1]+h*v[i][1]+h*h*a[i][1]/2;
      w[i][0]=v[i][0]+h*a[i][0]/2;
      w[i][1]=v[i][1]+h*a[i][1]/2;
   }
   gravitacion(r,a,m,n);
   for(int i=0; i < n ; i++)
   {
      v[i][0]=w[i][0]+h*a[i][0]/2;
      v[i][1]=w[i][1]+h*a[i][1]/2;
   }
  return;
}

double energia_potencial(double r[][2], double m[], int n)
{
  double distancia=0;
  double energia_potencial=0;
  for(int i=0; i < n ; i++)
  {

    for(int j=0; j < n ; j++)
    {
      if( j != i )
      {

        distancia=sqrt(pow(r[i][0]-r[j][0],2)+pow(r[i][1]-r[j][1],2));
        energia_potencial=energia_potencial+m[i]*m[j]/distancia;

      }
    }
  
  }
  return energia_potencial;

}

double energia_cinetica(double v[][2], double m[], int n)
{
  double energia_cinetica=0 , vel=0;
  for(int i=0; i < n ; i++)
  {
    vel=sqrt(v[i][0]*v[i][0]+v[i][1]*v[i][1]);
    energia_cinetica=energia_cinetica+1.0/2.0*m[i]*vel*vel;
  }
  return energia_cinetica;

}

void angulo_planetas(double angulo[], double r[][2], int n)
{
  double ang;
  for(int i=1; i<n; i++)
  {
    if(r[i][0] > 0 )
    {
      ang=atan(r[i][1]/r[i][0])*180/(3.1416);
    }
    else if(r[i][1] > 0) 
    {
      ang=(atan(r[i][1]/r[i][0])*180/(3.1416))-180;
    }
    else
    {
      ang=atan(r[i][1]/r[i][0])*180/(3.1416)+180;
    }
    if(ang > int(angulo[i])%360)
    {
      angulo[i]=ang+int(angulo[i])/360*360;
    }
    else
    {
      angulo[i]=ang+int(angulo[i])/360*360+360;
    }
  }


}

void periodo_planetas(double angulo[], int n, double h, double p)

{
  double periodo;
  ofstream salida("Periodo_planetas.dat", ios::app);
  for(int i=1; i<n ; i++)
  {
    periodo=p*h*58.1/(angulo[i]/360.0);
    salida << i << ":  " << periodo << " dias" << "\n";
  }
  salida.close();
}
void crear_fichero(string nombre)
{
  ofstream salida(nombre);
  salida << "";
  salida.close();
}

void leer_datos(double r[][2], double v[][2], double a[][2], double m[])
{
  int i;
  string line;
  ifstream entrada("Datos.txt");

  if (entrada)
  { 
    getline(entrada, line);  
    while(!entrada.eof())
    {
      entrada >> i;
      entrada >> m[i] >> r[i][0] >> r[i][1] >> v[i][0] >> v[i][1]; 
    }
    entrada.close();
  }
  else
  {
    cout << "No se pudo abrir el fichero \n"; 
  }
  entrada.close();
}

void escribir_posiciones(double r[][2], int n)
{
  ofstream salida("planets_data.dat", ios::app);
  for(int i=0 ; i < n ; i++)
  {
     salida << r[i][0] << ", " << r[i][1] <<"\n";  
  }
  salida << "\n\n";
  salida.close();
}

void escribir_energia(double E)
{
  ofstream salida("Energia_planetas.dat", ios::app);
  salida << E << "\n";
  salida.close();
}


int main()
{
  // Defino matriz con la posición de todos los planetas, tendra tantas filas como planetas y 2 columnas correspondientes al valor de x_i e y_i.
  double r[10][2], v[10][2], a[10][2], m[10], angulo[10]={0,0,0,0,0,0,0,0,0,0};
  double h = 0.01, E;
  int n=10, p;
  
  cout << "posiciones: ";
  cin >> p;

  crear_fichero("planets_data.dat");
  crear_fichero("Energia_planetas.dat");
  crear_fichero("Periodo_planetas.dat");
  leer_datos(r,v,a,m);
  reescalar(r,v,m,n);
  escribir_posiciones(r,n);;
  E=-energia_potencial(r,m,n)+energia_cinetica(v,m,n);
  escribir_energia(E);
  gravitacion(r,a,m,n);
  for (int i=0; i<p; i++)
  {
    verlet(r,v,a,m,h,n);
    escribir_posiciones(r,n);
    E=-energia_potencial(r,m,n)+energia_cinetica(v,m,n);
    escribir_energia(E);
    angulo_planetas(angulo,r,n);

  }
  periodo_planetas(angulo, n, h, p); 


}