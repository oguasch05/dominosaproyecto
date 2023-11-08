#include <stdio.h>
#include "colores.h"
#include "fichero.h"

#define SIZE_NOMBRE_FICHERO     80
#define MAX_FILAS               11
#define MAX_COLUMNAS            10

typedef struct casilla
{
        int valor; //valor casilla 0-9
        int e, s; //0 o 1 (true or false)  
} tcasilla;

int main()
{
        tcasilla casilla[MAX_FILAS][MAX_COLUMNAS];

        unsigned int conexiones = 0, max_conexiones;
        int err, f, c, n, nf, nc, num, t, x1, x2, num_casillas;
	char nombre_fichero[SIZE_NOMBRE_FICHERO], charf = 'A', y1, y2;


        printf("Introduce el nombre del fichero: ");
	scanf("%s%*c", nombre_fichero);
	err = abrir_fichero(nombre_fichero);
	if (err != ABRIR_FICHERO_OK) {
		printf("ERROR: FICHERO NO ENCONTRADO.\n");
		printf("PUEDE QUE EL NOMBRE NO SEA EL CORRECTO O QUE ESTE EN OTRO DIRECTORIO.\n");
	} 
        else 
        {
		n = leer_int_fichero();
		nf = leer_int_fichero();
		nc = leer_int_fichero();
                max_conexiones = nf*nc/2;

                for(f=0;f<nf;f++)
                {
                        for(c=0;c<nc;c++)
                        {
                                casilla[f][c].valor = leer_int_fichero();
                                casilla[f][c].e = 0;
                                casilla[f][c].s = 0;
                        }
                }
                cerrar_fichero();
	}
        while(conexiones < max_conexiones)
        {
                conexiones = 0;
                charf = 'A';
                t = 0;
                printf_color_negrita();
                printf("\n");

                for(c=0;c<nc;c++)
                {
                        printf("   %d", t);
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
                                printf_color_num(casilla[f][c].valor);
                                printf("%d", casilla[f][c].valor);
                                printf_reset_color();
                                printf_color_negrita();
                                if(casilla[f][c].e==1)
                                {
                                        printf("███");
                                        conexiones++;                                                
                                }
                                else
                                        printf("   ");
                        } printf("\n");
                        for(c=0;c<nc;c++)
                        {
                                printf(" + ");
                                if(casilla[f][c].s == 1)
                                {
                                        printf("█");
                                        conexiones++;
                                }
                                else
                                        printf(" ");
                        } printf(" +\n");

                }

                printf("\n");
                printf("\nConexiones: %u de %u\n\n", conexiones, max_conexiones);

                if(conexiones == max_conexiones)
                        break;

                do
                {               
                        printf("Casillas a conectar/desconectar (ej: [A0B0]): "); 
                        scanf("%c%d%c%d%*c", &y1, &x1, &y2, &x2);
                        if(y1>='a'&&y1<='z')
                        {
                                y1 = y1-'a';
                        }
                        if(y1>='A'&&y1<='Z')
                        {
                                y1 = y1-'A';
                        }
                        if(y2>='a'&&y2<='z')
                        {
                                y2 = y2-'a';
                        }
                        if(y2>='A'&&y2<='Z')
                        {
                                y2 = y2-'A';
                        }
                }
                while(x1==x2 && y1==y2 || x1!=x2 && y1!=y2 || x1-x2!=1 && y1-y2!=1 && x2-x1!=1 && y2-y1!=1 || y1>nf-1 || y2>nf-1 || x1>nc || x2>nc);
                if(y1>y2)
                {
                        if(casilla[y2][x1].s == 1)
                        {
                                casilla[y2][x1].s = 0;
                        }
                        else
                        {
                                casilla[y1][x1].e = 0;
                                casilla[y1][x1].s = 0;
                                casilla[y2][x2].e = 0;
                                casilla[y2][x2].s = 0;
                                casilla[y1][x1-1].e = 0;
                                casilla[y1-1][x1].s = 0;
                                casilla[y2][x2-1].e = 0;
                                casilla[y2-1][x2].s = 0;

                                casilla[y2][x1].s = 1;
                                
                        }

                }
                else if(y1<y2)
                {
                        if(casilla[y1][x1].s == 1)
                        {
                                casilla[y1][x1].s = 0;
                        }
                        else
                        {
                                casilla[y1][x1].e = 0;
                                casilla[y1][x1].s = 0;
                                casilla[y2][x2].e = 0;
                                casilla[y2][x2].s = 0;
                                casilla[y1][x1-1].e = 0;
                                casilla[y1-1][x1].s = 0;
                                casilla[y2][x2-1].e = 0;
                                casilla[y2-1][x2].s = 0;

                                casilla[y1][x1].s = 1;
                                
                        }
                }
                else if(x1>x2)
                {
                        if(casilla[y1][x2].e == 1)
                        {
                                casilla[y1][x2].e = 0;
                        }
                        else
                        {
                                casilla[y1][x1].e = 0;
                                casilla[y1][x1].s = 0;
                                casilla[y2][x2].e = 0;
                                casilla[y2][x2].s = 0;
                                casilla[y1][x1-1].e = 0;
                                casilla[y1-1][x1].s = 0;
                                casilla[y2][x2-1].e = 0;
                                casilla[y2-1][x2].s = 0;

                                casilla[y1][x2].e = 1;
                                
                        }
                }
                else if(x1<x2)
                {
                        if(casilla[y1][x1].e == 1)
                        {
                                casilla[y1][x1].e = 0;
                        }
                        else
                        {
                                casilla[y1][x1].e = 0;
                                casilla[y1][x1].s = 0;
                                casilla[y2][x2].e = 0;
                                casilla[y2][x2].s = 0;
                                casilla[y1][x1-1].e = 0;
                                casilla[y1-1][x1].s = 0;
                                casilla[y2][x2-1].e = 0;
                                casilla[y2-1][x2].s = 0;
                                
                                casilla[y1][x1].e = 1;
                        }
                }       

        }
        printf("FELICIDADES! HAS RESUELTO ESTE DOMINOSA! B-)\n\n");
}
