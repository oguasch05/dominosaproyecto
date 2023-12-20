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

typedef struct fichas
{
	int ficha[MAX_N][MAX_N]; //fichas del 0-0 al 9-9
	int n1, n2; //valores de la ficha (n1-n2/n2-n1) (1-2)->n1=1 n2=2 || n1=2 n2=1
} tfichas;

int main()
{
        tcasilla casilla[MAX_FILAS][MAX_COLUMNAS];
	tfichas ficha;
	ficha.n1=0;

        unsigned int conexiones, max_conexiones;
        int err, f, c, n, nf, nc, num, t, x1, x2, num_casillas;
	char nombre_fichero[SIZE_NOMBRE_FICHERO], charf, y1, y2;

	//inicio funcion inicializacion
        printf("Introduce el nombre del fichero: ");
	scanf("%s%*c", nombre_fichero);
	err = abrir_fichero(nombre_fichero);
	if (err != ABRIR_FICHERO_OK) {
		printf("ERROR: FICHERO NO ENCONTRADO.\n");
		printf("PUEDE QUE EL NOMBRE NO SEA EL CORRECTO O QUE ESTE EN OTRO DIRECTORIO.\n");
	} 
        else 
        {
		n = leer_int_fichero();   //numero mas grande que aparece
		nf = leer_int_fichero();  //numero de filas
		nc = leer_int_fichero();  //numero de columnas
                max_conexiones = nf*nc/2; //numero de conexiones maximas

                for(f=0;f<nf;f++)
                {
                        for(c=0;c<nc;c++)
                        {
                                casilla[f][c].valor = leer_int_fichero(); //guarda los valores del tablero en la matriz casilla[][].valor
                                casilla[f][c].e = FALSE; //borra todas las conexiones en e
                                casilla[f][c].s = FALSE; //borra todas las conexiones en s
                        }
                }
                cerrar_fichero();
	}
	//final funcion inicializacion
        while(ficha.n1<=n) //cuando deje de cumplirse, el juego acaba (main loop)
        {
                conexiones = 0; //numero de conexiones
                ficha.n1 = 0;
		ficha.n2 = 0;
                charf = 'A'; //cabecera de fila
                t = 0; //cabecera de columna
                printf_color_negrita();
                printf("\n");

                //inicio funcion dibujar tablero
		for(c=0;c<nc;c++)
                {
                        printf("   %d", t); //escribe la cabecera de las columnas
                        t++;
                } printf("\n ");
                for(c=0;c<nc;c++)
                {
                        printf("+---");
                } printf("+\n");
                
                for(f=0;f<nf;f++)
                {
                        printf("%c| ", charf);
                        charf++;
                        for(c=0;c<nc;c++)
                        {
                                num = leer_int_fichero();
                                printf_color_num(casilla[f][c].valor); //cambia el color al color del valor de la casilla
                                printf("%d", casilla[f][c].valor);     //escribe las casillas
                                printf_reset_color();
                                printf_color_negrita();
                                if(casilla[f][c].e==TRUE)
                                {
                                        printf("███");  //escribe la conexion en caso de que casilla[][].e sea cierto
                                        conexiones++;                                                
                                }
                                else
                                        printf("   ");  //escribe la conexion en caso de que casilla[][].e sea falso
                        } printf("\n");
                        for(c=0;c<nc;c++)
                        {
                                printf(" + ");
                                if(casilla[f][c].s == TRUE)
                                {
                                        printf("█"); //escribe la conexion en caso de que casilla[][].s sea cierto
                                        conexiones++;
                                }
                                else
                                        printf(" "); //escribe la conexion en caso de que casilla[][].e sea falso
                        } printf(" +\n");

                }
		//final funcion dibujar tablero

                printf("\n");
                printf("\nConexiones: %u de %u\n\n", conexiones, max_conexiones); //escribe "__ conexiones de __"

		//inicio funcion comprobar fichas
                for(f=0;f<nf;f++)
                {
                        for(c=0;c<nc;c++)
                        {
                                if((casilla[f][c].e == TRUE&&casilla[f][c].valor==ficha.n1&&casilla[f][c+1].valor==ficha.n2) || (casilla[f][c].e == TRUE&&casilla[f][c].valor==ficha.n2&&casilla[f][c+1].valor==ficha.n1) || (casilla[f][c].s == TRUE&&casilla[f][c].valor==ficha.n1&&casilla[f+1][c].valor==ficha.n2) || (casilla[f][c].s == TRUE&&casilla[f][c].valor==ficha.n2&&casilla[f+1][c].valor==ficha.n1))
                                {
                                	ficha.ficha[ficha.n1][ficha.n2] = TRUE;
					f=0;
					c=-1;
					ficha.n2++;
					if(ficha.n2>n)
					{
						ficha.n1++;
						ficha.n2=0;
						while(ficha.n1>ficha.n2)
							ficha.n2++;
					}
                                }
                        }
                }
		//final fincion comprobar fichas
                if(ficha.n1<=n)
		{
			//inicio funcion añadir conexiones
	                do
	                {               
	                        printf("Casillas a conectar/desconectar (ej: [A0B0]): "); //pide valores de dos casillas
	                        scanf("%c%d%c%d%*c", &y1, &x1, &y2, &x2);       //guarda valores de dos casillas en x1, x2, y1, y2
	                        if(y1>='a'&&y1<='z')
	                        {
	                                y1 = y1-'a'; //si la letra introducida es minuscula, y1 pasa a valer un numero (a=0,b=1,c=2,...)
	                        }
	                        if(y1>='A'&&y1<='Z')
	                        {
	                                y1 = y1-'A'; //si la letra introducida es mayuscula, y1 pasa a valer un numero (A=0,B=1,C=2,...)
	                        }
	                        if(y2>='a'&&y2<='z')
	                        {
	                                y2 = y2-'a'; //si la letra introducida es minuscula, y2 pasa a valer un numero (a=0,b=1,c=2,...)
	                        }
	                        if(y2>='A'&&y2<='Z')
	                        {
	                                y2 = y2-'A'; //si la letra introducida es mayuscula, y2 pasa a valer un numero (A=0,B=1,C=2,...)
	                        }
	                }
	                while(x1==x2 && y1==y2 || x1!=x2 && y1!=y2 || x1-x2!=1 && y1-y2!=1 && x2-x1!=1 && y2-y1!=1 || y1>nf-1 || y2>nf-1 || x1>nc || x2>nc); //comprueba que la conexion es posible
	                if(y1>y2)
	                {
	                        if(casilla[y2][x1].s == TRUE)
	                        {
	                                casilla[y2][x1].s = FALSE;
	                        }
	                        else
	                        {
	                                casilla[y1][x1].e = FALSE;
	                                casilla[y1][x1].s = FALSE;
	                                casilla[y2][x2].e = FALSE;
	                                casilla[y2][x2].s = FALSE;
	                                casilla[y1][x1-1].e = FALSE;
	                                casilla[y1-1][x1].s = FALSE;
	                                casilla[y2][x2-1].e = FALSE;
	                                casilla[y2-1][x2].s = FALSE;
	
	                                casilla[y2][x1].s = TRUE;
	                                
	                        }
	
	                }
	                else if(y1<y2)
	                {
	                        if(casilla[y1][x1].s == TRUE)
	                        {
	                                casilla[y1][x1].s = FALSE;
	                        }
	                        else
	                        {
	                                casilla[y1][x1].e = FALSE;
	                                casilla[y1][x1].s = FALSE;
	                                casilla[y2][x2].e = FALSE;
	                                casilla[y2][x2].s = FALSE;
	                                casilla[y1][x1-1].e = FALSE;
	                                casilla[y1-1][x1].s = FALSE;
	                                casilla[y2][x2-1].e = FALSE;
	                                casilla[y2-1][x2].s = FALSE;
	
	                                casilla[y1][x1].s = TRUE;
	                                
	                        }
	                }
	                else if(x1>x2)
	                {
	                        if(casilla[y1][x2].e == TRUE)
	                        {
	                                casilla[y1][x2].e = FALSE;
	                        }
	                        else
	                        {
	                                casilla[y1][x1].e = FALSE;
	                                casilla[y1][x1].s = FALSE;
	                                casilla[y2][x2].e = FALSE;
	                                casilla[y2][x2].s = FALSE;
	                                casilla[y1][x1-1].e = FALSE;
	                                casilla[y1-1][x1].s = FALSE;
	                                casilla[y2][x2-1].e = FALSE;
	                                casilla[y2-1][x2].s = FALSE;
	
	                                casilla[y1][x2].e = TRUE;
	                                
	                        }
	                }
	                else if(x1<x2)
	                {
	                        if(casilla[y1][x1].e == TRUE)
	                        {
	                                casilla[y1][x1].e = FALSE;
	                        }
	                        else
	                        {
	                                casilla[y1][x1].e = FALSE;
	                                casilla[y1][x1].s = FALSE;
	                                casilla[y2][x2].e = FALSE;
	                                casilla[y2][x2].s = FALSE;
	                                casilla[y1][x1-1].e = FALSE;
	                                casilla[y1-1][x1].s = FALSE;
	                                casilla[y2][x2-1].e = FALSE;
	                                casilla[y2-1][x2].s = FALSE;
	                                
	                                casilla[y1][x1].e = TRUE;
	                        }
	                }       
			//final funcion añadir conexiones
		}
        }
	printf("FELICIDADES! HAS RESUELTO ESTE DOMINOSA! B-)\n\n");
}