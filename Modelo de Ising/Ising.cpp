# include <iostream>
# include <stdlib.h>
# include <time.h>
# include <fstream>
# include <math.h>

using namespace std;

void generar_datos(int s[100][100], int N)
{
    int valor;
    for(int j=0; j<N; j++)
    {
        for(int i=0; i<N; i++)
        {
            valor=rand();
            if(valor<RAND_MAX/2)
            {
                s[i][j]=-1;
            }
            else
            {
                s[i][j]=1;
            }
        }

    }

}


double variacion_energia(int s[100][100], int n,int m, int N)
{
    return  2*s[n][m]*(s[n][(m+1)%N]+s[n][(m+N-1)%N]+s[(n+1)%N][m]+s[(n+N-1)%N][m]);
}

void ising(int s[100][100], double T, int N)
{
    int n,m;
    double p, e;
    
    n=rand()%N;
    m=rand()%N;

    p=exp(-variacion_energia(s,n,m,N)/T);

    if(p>1)
    {
        p=1;
    }

    e=1.0*rand()/RAND_MAX;

    if(e<p)
    {
        s[n][m]=-s[n][m];
    }

}

void crear_fichero(string nombre)
{
    ofstream salida(nombre);
    salida << "";
    salida.close();
}

void escribir_datos(int s[100][100], int N)
{
    ofstream salida("ising_data.dat", ios::app);
    for(int j=N-1; j>=0; j--)
    {
        for(int i=N-1; i>0; i--)
        {
            salida << s[i][j] << ",";
        }
        salida << s[j][0] <<"\n";
    }

    salida << "\n";
    salida.close();
}

int main()
{
    int N=100;
    int s[100][100]; 
    double T=0.01;
    srand(time(NULL));
    crear_fichero("ising_data.dat");
    generar_datos(s,N);
    escribir_datos(s,N);
    for(int i=0; i<N*N*10^6; i++)
    {
        ising(s,T,N);
        if(i%(N*N)==0)
        {
        escribir_datos(s,N);
        }
    }
}