#include <stdio.h>
#include "colores.h"
#include "fichero.h"

#define SIZE_NOMBRE_FICHERO     80
#define MAX_FILAS               11
#define MAX_COLUMNAS            10
#define MAX_N			9
#define TRUE                    1
#define FALSE                   0

typedef struct casilla
{
    int valor; //valor casilla 0-9
    int e, s; //0 o 1 (true or false)  
} tcasilla;

typedef struct tablero
{
    int nf, nc, n;
    tcasilla mat[MAX_FILAS][MAX_COLUMNAS];
} tablero;

tablero inicializar(tablero t);
int dibujar(tablero t);
void jugadas(tablero t);
int comprobar(tablero t);


int main()
{
    tablero t;
    unsigned int conexiones;
	int f, c, conexiones_reales=0, title, c1, c2, f1, f2, max_conexiones;
	char charf, y1, y2;

	t = inicializar(t);
        max_conexiones = t.nf*t.nc/2; //numero de conexiones maximas
        if(t.n!=-1)
        {
                do {
                        conexiones = dibujar(t);
                        conexiones_reales = comprobar(t);
                        if(conexiones_reales<max_conexiones)
                        {
                        do
                        {               
                        printf("Casillas a conectar/desconectar (ej: [A0B0]): "); //pide valores de dos casillas
                        scanf("%c%d%c%d%*c", &y1, &c1, &y2, &c2);       //guarda valores de dos casillas en x1, x2, y1, y2
                        if(y1>='a'&&y1<='z')
                        {
                                f1 = y1-'a'; //si la letra introducida es minuscula, f1 pasa a valer un numero (a=0,b=1,c=2,...)
                        }
                        if(y1>='A'&&y1<='Z')
                        {
                                f1 = y1-'A'; //si la letra introducida es mayuscula, f1 pasa a valer un numero (A=0,B=1,C=2,...)
                        }
                        if(y2>='a'&&y2<='z')
                        {
                                f2 = y2-'a'; //si la letra introducida es minuscula, f2 pasa a valer un numero (a=0,b=1,c=2,...)
                        }
                        if(y2>='A'&&y2<='Z')
                        {
                                f2 = y2-'A'; //si la letra introducida es mayuscula, f2 pasa a valer un numero (A=0,B=1,C=2,...)
                        }
                        }
                        while(c1==c2 && f1==f2 || c1!=c2 && f1!=f2 || c1-c2!=1 && f1-f2!=1 && c2-c1!=1 && f2-f1!=1 || f1>t.nf-1 || f2>t.nf-1 || c1>t.nc || c2>t.nc); //comprueba que la conexion es posible
                                        
                        if(f1>f2)
                        {
                        if(t.mat[f2][c1].s == TRUE)
                        {
                                t.mat[f2][c1].s = FALSE;
                        }
                        else
                        {
                                t.mat[f1][c1].e = FALSE;
                                t.mat[f1][c1].s = FALSE;
                                t.mat[f2][c2].e = FALSE;
                                t.mat[f2][c2].s = FALSE;
                                if(c1!=0)
                                        t.mat[f1][c1-1].e = FALSE;
                                if(c1!=0)
                                        t.mat[f1-1][c1].s = FALSE;
                                if(c2!=0)
                                        t.mat[f2][c2-1].e = FALSE;
                                if(f2!=0)
                                        t.mat[f2-1][c2].s = FALSE;
                                t.mat[f2][c1].s = TRUE;          
                        }
                        
                        }
                        else if(f1<f2)
                        {
                        if(t.mat[f1][c1].s == TRUE)
                        {
                                t.mat[f1][c1].s = FALSE;
                        }
                        else
                        {
                                t.mat[f1][c1].e = FALSE;
                                t.mat[f1][c1].s = FALSE;
                                t.mat[f2][c2].e = FALSE;
                                t.mat[f2][c2].s = FALSE;
                                if(c1!=0)
                                        t.mat[f1][c1-1].e = FALSE;
                                if(c1!=0)
                                        t.mat[f1-1][c1].s = FALSE;
                                if(c2!=0)
                                        t.mat[f2][c2-1].e = FALSE;
                                if(f2!=0)
                                        t.mat[f2-1][c2].s = FALSE;
                                t.mat[f1][c1].s = TRUE;                
                        }
                        }
                        else if(c1>c2)
                        {
                        if(t.mat[f1][c2].e == TRUE)
                        {
                                t.mat[f1][c2].e = FALSE;
                        }
                        else
                        {
                                t.mat[f1][c1].e = FALSE;
                                t.mat[f1][c1].s = FALSE;
                                t.mat[f2][c2].e = FALSE;
                                t.mat[f2][c2].s = FALSE;
                                if(c1!=0)
                                        t.mat[f1][c1-1].e = FALSE;
                                if(c1!=0)
                                        t.mat[f1-1][c1].s = FALSE;
                                if(c2!=0)
                                        t.mat[f2][c2-1].e = FALSE;
                                if(f2!=0)
                                        t.mat[f2-1][c2].s = FALSE;
                                t.mat[f1][c2].e = TRUE;        
                        }
                        }
                        else if(c1<c2)
                        {
                        if(t.mat[f1][c1].e == TRUE)
                        {
                                t.mat[f1][c1].e = FALSE;
                        }
                        else
                        {
                                t.mat[f1][c1].e = FALSE;
                                t.mat[f1][c1].s = FALSE;
                                t.mat[f2][c2].e = FALSE;
                                t.mat[f2][c2].s = FALSE;
                                if(c1!=0)
                                        t.mat[f1][c1-1].e = FALSE;
                                if(c1!=0)
                                        t.mat[f1-1][c1].s = FALSE;
                                if(c2!=0)
                                        t.mat[f2][c2-1].e = FALSE;
                                if(f2!=0)
                                        t.mat[f2-1][c2].s = FALSE;      
                                t.mat[f1][c1].e = TRUE;
                        }
                        }       //final funcion añadir conexiones
                        }
                }
                while(conexiones_reales<max_conexiones);
        }
        if (conexiones_reales==max_conexiones)
        printf("FELICIDADES! HAS RESUELTO ESTE DOMINOSA! B-)\n\n");
}

tablero inicializar(tablero t)
{
	int err, f, c;
	char nombre_fichero[SIZE_NOMBRE_FICHERO];
        t.n=-1;

	printf("Introduce el nombre del fichero: ");
	scanf("%s%*c", nombre_fichero);
	err = abrir_fichero(nombre_fichero);
	if (err != ABRIR_FICHERO_OK) {
		printf("ERROR: FICHERO NO ENCONTRADO.\n");
		printf("PUEDE QUE EL NOMBRE NO SEA EL CORRECTO O QUE ESTE EN OTRO DIRECTORIO.\n");
	} 
        else 
        {
		t.n = leer_int_fichero();   //numero mas grande que aparece
		t.nf = leer_int_fichero();  //numero de filas
		t.nc = leer_int_fichero();  //numero de columnas

                for(f=0;f<t.nf;f++)
                {
                        for(c=0;c<t.nc;c++)
                        {
                                t.mat[f][c].valor = leer_int_fichero(); //guarda los valores del tablero en la matriz casilla[][].valor
                                t.mat[f][c].e = FALSE; //borra todas las conexiones en e
                                t.mat[f][c].s = FALSE; //borra todas las conexiones en s
                        }
                }
                cerrar_fichero();
	}
	return t;
}

int dibujar(tablero t)
{
	int conexiones = 0, f, c, max_conexiones; //numero de conexiones
    char charf = 'A'; //cabecera de fila
    unsigned int title = 0; //cabecera de columna
    printf_color_negrita();
    printf("\n");
    for(c=0;c<t.nc;c++)
    {
        printf("   %d", title); //escribe la cabecera de las columnas
        title++;
    } printf("\n ");
    for(c=0;c<t.nc;c++)
    {
        printf("+---");
    } printf("+\n"); 
    for(f=0;f<t.nf;f++)
    {
        printf("%c| ", charf); //escribe la cabecera de las filas
        charf++;
    	for(c=0;c<t.nc;c++)
        {
            printf_color_num(t.mat[f][c].valor); //cambia el color al color del valor de la casilla
            printf("%d", t.mat[f][c].valor);     //escribe las casillas
            printf_reset_color();
            printf_color_negrita();
            if(t.mat[f][c].e==TRUE)
            {
                printf("███");  //escribe la conexion en caso de que casilla[][].e sea cierto
                conexiones++;                                                
            }
            else
                printf("   ");  //escribe la conexion en caso de que casilla[][].e sea falso
        } printf("\n");
        for(c=0;c<t.nc;c++)
        {
            printf(" + ");
            if(t.mat[f][c].s == TRUE)
            {
                printf("█"); //escribe la conexion en caso de que casilla[][].s sea cierto
                conexiones++;
            }
        	else
                printf(" "); //escribe la conexion en caso de que casilla[][].e sea falso
        } printf(" +\n");
    }
	printf("\n");
	max_conexiones = t.nf*t.nc/2; //numero de conexiones maximas
    printf("\nConexiones: %u de %u\n\n", conexiones, max_conexiones); //escribe "__ conexiones de __"
	return conexiones;
}

int comprobar(tablero t)
{

        int f, c, n1, n2, ficha[MAX_N][MAX_N], conexiones=0, max_conexiones, final=FALSE;
        max_conexiones = t.nf*t.nc/2; //numero de conexiones maximas

        for(f=0;f<t.n;f++)
        {
                for(c=0;c<t.n;c++)
                {
                        ficha[f][c] = FALSE;
                }
        }

        n1=0, n2=0;
	do
        {
                if(n2>t.n) //pasa de la ficha 0-2 a la 1-1 en caso de que el numero mas grande (t.n) sea 1 (se salta la fichas 1-0, 2-0, 2-1 que estan repetidas)
                {
                        n1++;
                        n2=n1;
                }
                if(n1<=t.n) //comprueba que n1 no se salga del límite de la ficha t.n-t.n (ficha mas grande posible)
                {
                        for(f=0;conexiones<max_conexiones&&f<t.nf;f++)
                        {
                                for(c=0;conexiones<max_conexiones&&c<t.nc;c++)
                                {
                                        if((t.mat[f][c].e == TRUE && ((t.mat[f][c].valor==n1&&t.mat[f][c+1].valor==n2)||(t.mat[f][c].valor==n2&&t.mat[f][c+1].valor==n1))) || (t.mat[f][c].s == TRUE && ((t.mat[f][c].valor==n1&&t.mat[f+1][c].valor==n2)||(t.mat[f][c].valor==n2&&t.mat[f+1][c].valor==n1))))
                                        {
                                                ficha[n1][n2] = TRUE;
                                                conexiones++;
                                        }
                                }
                        }
                }
			n2++;
        }
	while(ficha[n1][n2-1]==TRUE&&n1<t.n);
        return conexiones;
}