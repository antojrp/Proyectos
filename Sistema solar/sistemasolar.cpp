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

void crear_fichero()
{
  ofstream salida("planets_data.dat");
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

void escribir_datos(double r[][2], int n)
{
  ofstream salida("planets_data.dat", ios::app);
  for(int i=0 ; i < n ; i++)
  {
     salida << r[i][0] << ", " << r[i][1] <<"\n";  
  }
  salida << "\n\n";
  salida.close();
}

int main()
{
  // Defino matriz con la posición de todos los planetas, tendra tantas filas como planetas y 2 columnas correspondientes al valor de x_i e y_i.
  double r[10][2], v[10][2], a[10][2], m[10];
  double h = 0.2;
  int n=10, p;
  
  cout << "posiciones: ";
  cin >> p;

  crear_fichero();
  leer_datos(r,v,a,m);
  reescalar(r,v,m,n);
  escribir_datos(r,n);
  for (int i=0; i<p; i++)
  {
    gravitacion(r,a,m,n);
    verlet(r,v,a,m,h,n);
    escribir_datos(r,n);
  }
  


}