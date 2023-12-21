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
    int f, c, nf, nc, n;
    tcasilla casilla[MAX_FILAS][MAX_COLUMNAS];
} tablero;


//int comprobar(tablero *tablero);


int main()
{
    tablero t;

    unsigned int conexiones, max_conexiones;
    int err, num, title, x1, x2, num_casillas, final=FALSE;
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
		t.n = leer_int_fichero();   //numero mas grande que aparece
		t.nf = leer_int_fichero();  //numero de filas
		t.nc = leer_int_fichero();  //numero de columnas
                max_conexiones = t.nf*t.nc/2; //numero de conexiones maximas

                for(t.f=0;t.f<t.nf;t.f++)
                {
                        for(t.c=0;t.c<t.nc;t.c++)
                        {
                                t.casilla[t.f][t.c].valor = leer_int_fichero(); //guarda los valores del tablero en la matriz casilla[][].valor
                                t.casilla[t.f][t.c].e = FALSE; //borra todas las conexiones en e
                                t.casilla[t.f][t.c].s = FALSE; //borra todas las conexiones en s
                        }
                }
                cerrar_fichero();
	}
	//final funcion inicializacion
        if(err==ABRIR_FICHERO_OK){
                do //cuando deje de cumplirse, el juego acaba (main loop)
                {
                        conexiones = 0; //numero de conexiones
                        charf = 'A'; //cabecera de fila
                        title = 0; //cabecera de columna
                        printf_color_negrita();
                        printf("\n");

                        //inicio funcion dibujar tablero
                        for(t.c=0;t.c<t.nc;t.c++)
                        {
                                printf("   %d", title); //escribe la cabecera de las columnas
                                title++;
                        } printf("\n ");
                        for(t.c=0;t.c<t.nc;t.c++)
                        {
                                printf("+---");
                        } printf("+\n");
                        
                        for(t.f=0;t.f<t.nf;t.f++)
                        {
                                printf("%c| ", charf); //escribe la cabecera de las filas
                                charf++;
                                for(t.c=0;t.c<t.nc;t.c++)
                                {
                                        num = leer_int_fichero();
                                        printf_color_num(t.casilla[t.f][t.c].valor); //cambia el color al color del valor de la casilla
                                        printf("%d", t.casilla[t.f][t.c].valor);     //escribe las casillas
                                        printf_reset_color();
                                        printf_color_negrita();
                                        if(t.casilla[t.f][t.c].e==TRUE)
                                        {
                                                printf("███");  //escribe la conexion en caso de que casilla[][].e sea cierto
                                                conexiones++;                                                
                                        }
                                        else
                                                printf("   ");  //escribe la conexion en caso de que casilla[][].e sea falso
                                } printf("\n");
                                for(t.c=0;t.c<t.nc;t.c++)
                                {
                                        printf(" + ");
                                        if(t.casilla[t.f][t.c].s == TRUE)
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
                        //final = comprobar(&t);

                        int n1, n2, ficha[MAX_N][MAX_N];

                        //printf("nf:%d nc:%d n:%d\n", t.nf, t.nc, t.n);

                        for(t.f=0;t.f<t.n;t.f++)
                        {
                                for(t.c=0;t.c<t.n;t.c++)
                                {
                                        ficha[t.f][t.c] = FALSE;
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
                                for(t.f=0;ficha[n1][n2]!=TRUE&&t.f<t.nf;t.f++)
                                {
                                    for(t.c=0;ficha[n1][n2]!=TRUE&&t.c<t.nc;t.c++)
                                    {
                                        if((t.casilla[t.f][t.c].e == TRUE && ((t.casilla[t.f][t.c].valor==n1&&t.casilla[t.f][t.c+1].valor==n2)||(t.casilla[t.f][t.c].valor==n2&&t.casilla[t.f][t.c+1].valor==n1))) || (t.casilla[t.f][t.c].s == TRUE && ((t.casilla[t.f][t.c].valor==n1&&t.casilla[t.f+1][t.c].valor==n2)||(t.casilla[t.f][t.c].valor==n2&&t.casilla[t.f+1][t.c].valor==n1)))
                                            ficha[n1][n2] = TRUE;
                                    }
                                }
                            }
							n2++;
                        }
						while(ficha[n1][n2-1]==TRUE&&n1<t.n);

                            if(ficha[t.n][t.n]==TRUE)
                                //final = TRUE;

                        if(final!=TRUE)
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
                                while(x1==x2 && y1==y2 || x1!=x2 && y1!=y2 || x1-x2!=1 && y1-y2!=1 && x2-x1!=1 && y2-y1!=1 || y1>t.nf-1 || y2>t.nf-1 || x1>t.nc || x2>t.nc); //comprueba que la conexion es posible
                                if(y1>y2)
                                {
                                        if(t.casilla[y2][x1].s == TRUE)
                                        {
                                                t.casilla[y2][x1].s = FALSE;
                                        }
                                        else
                                        {
                                                t.casilla[y1][x1].e = FALSE;
                                                t.casilla[y1][x1].s = FALSE;
                                                t.casilla[y2][x2].e = FALSE;
                                                t.casilla[y2][x2].s = FALSE;
                                                t.casilla[y1][x1-1].e = FALSE;
                                                t.casilla[y1-1][x1].s = FALSE;
                                                t.casilla[y2][x2-1].e = FALSE;
                                                t.casilla[y2-1][x2].s = FALSE;
                
                                                t.casilla[y2][x1].s = TRUE;
                                                
                                        }
                
                                }
                                else if(y1<y2)
                                {
                                        if(t.casilla[y1][x1].s == TRUE)
                                        {
                                                t.casilla[y1][x1].s = FALSE;
                                        }
                                        else
                                        {
                                                t.casilla[y1][x1].e = FALSE;
                                                t.casilla[y1][x1].s = FALSE;
                                                t.casilla[y2][x2].e = FALSE;
                                                t.casilla[y2][x2].s = FALSE;
                                                t.casilla[y1][x1-1].e = FALSE;
                                                t.casilla[y1-1][x1].s = FALSE;
                                                t.casilla[y2][x2-1].e = FALSE;
                                                t.casilla[y2-1][x2].s = FALSE;
                
                                                t.casilla[y1][x1].s = TRUE;
                                                
                                        }
                                }
                                else if(x1>x2)
                                {
                                        if(t.casilla[y1][x2].e == TRUE)
                                        {
                                                t.casilla[y1][x2].e = FALSE;
                                        }
                                        else
                                        {
                                                t.casilla[y1][x1].e = FALSE;
                                                t.casilla[y1][x1].s = FALSE;
                                                t.casilla[y2][x2].e = FALSE;
                                                t.casilla[y2][x2].s = FALSE;
                                                t.casilla[y1][x1-1].e = FALSE;
                                                t.casilla[y1-1][x1].s = FALSE;
                                                t.casilla[y2][x2-1].e = FALSE;
                                                t.casilla[y2-1][x2].s = FALSE;
                
                                                t.casilla[y1][x2].e = TRUE;
                                                
                                        }
                                }
                                else if(x1<x2)
                                {
                                        if(t.casilla[y1][x1].e == TRUE)
                                        {
                                                t.casilla[y1][x1].e = FALSE;
                                        }
                                        else
                                        {
                                                t.casilla[y1][x1].e = FALSE;
                                                t.casilla[y1][x1].s = FALSE;
                                                t.casilla[y2][x2].e = FALSE;
                                                t.casilla[y2][x2].s = FALSE;
                                                t.casilla[y1][x1-1].e = FALSE;
                                                t.casilla[y1-1][x1].s = FALSE;
                                                t.casilla[y2][x2-1].e = FALSE;
                                                t.casilla[y2-1][x2].s = FALSE;
                                                
                                                t.casilla[y1][x1].e = TRUE;
                                        }
                                }      //final funcion añadir conexiones
                        }
                } while(final!=TRUE);
        }
	if (final==TRUE)
                printf("FELICIDADES! HAS RESUELTO ESTE DOMINOSA! B-)\n\n");
}

// int comprobar(tablero *t)
// {
// int n1, n2, ficha[MAX_N][MAX_N];
// int final=FALSE, err=FALSE;

// printf("nf:%d nc:%d n:%d\n", t->nf, t->nc, t->n);

// for(t->f=0;t->f<t->n;t->f++)
// {
//         for(t->c=0;t->c<t->n;t->c++)
//         {
//                 ficha[t->f][t->c] = FALSE;
//         }
// }

// for(n1=0;err!=TRUE&&n1<=t->n;n1++)
// {
//         for(n2=0;err!=TRUE&&n2<=t->n;n2++)
//         {
//                 if(n1>n2)
//                         n2++;

//                 for(t->f=0;ficha[n1][n2]!=TRUE&&t->f<t->nf;t->f++)
//                 {
//                         for(t->c=0;ficha[n1][n2]!=TRUE&&t->c<t->nc;t->c++)
//                         {
//                                 printf("e:%d, s:%d in f:%d c:%d\n", t->casilla[t->f][t->c].e, t->casilla[t->f][t->c].s, t->f, t->c);
//                                 if((t->casilla[t->f][t->c].e == TRUE&&t->casilla[t->f][t->c].valor==n1&&t->casilla[t->f][t->c+1].valor==n2) || (t->casilla[t->f][t->c].e == TRUE&&t->casilla[t->f][t->c].valor==n2&&t->casilla[t->f][t->c+1].valor==n1) || (t->casilla[t->f][t->c].s == TRUE&&t->casilla[t->f][t->c].valor==n1&&t->casilla[t->f+1][t->c].valor==n2) || (t->casilla[t->f][t->c].s == TRUE&&t->casilla[t->f][t->c].valor==n2&&t->casilla[t->f+1][t->c].valor==n1))
//                                 {
//                        	                ficha[n1][n2] = TRUE;
//                                         printf("%d-%d yes\n", n1, n2);
//                                 }
//                         }
//                 } err=TRUE;
//         }
// }
//         if(ficha[t->n][t->n]==TRUE)
//                 final = TRUE;
//                 printf("final %d\n", final);
        
//         return final;
        
// }
