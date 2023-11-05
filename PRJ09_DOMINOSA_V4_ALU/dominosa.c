#include <stdio.h>
#include "colores.h"
#include "fichero.h"

#define SIZE_NOMBRE_FICHERO     80

typedef struct casilla
{
        int valor; //valor casilla 0-6
        int e, s; //0 o 1 (true or false)
        int x, y; //posicion
} tcasilla;

int main()
{
        tcasilla casilla1, casilla2;

        unsigned int conexiones = 0, max_conexiones;
        int err, f, c, n, nf, nc, num, t;
	char nombre_fichero[SIZE_NOMBRE_FICHERO], charf = 'A', y1, y2;


        printf("Introduce el nombre del fichero: ");
	scanf("%s%*c", nombre_fichero);
	err = abrir_fichero(nombre_fichero);
	if (err != ABRIR_FICHERO_OK) {
		printf("ERROR: FICHERO NO ENCONTRADO.\n");
		printf("PUEDE QUE EL NOMBRE NO SEA EL CORRECTO O QUE ESTE EN OTRO DIRECTORIO.\n");
	} else {
		n = leer_int_fichero();
		nf = leer_int_fichero();
		nc = leer_int_fichero();
                max_conexiones = nf*nc/2;
                nf = nf*2+2;
                cerrar_fichero();
	}

        while(conexiones < max_conexiones)
        {
                charf = 'A';
                t = 0;
                printf_color_negrita();
                abrir_fichero(nombre_fichero);
                leer_int_fichero();
                leer_int_fichero();
                leer_int_fichero();
                for(f=0;f<nf;f++)
                {
                        if(f==0)
                        {
                                for(c=0;c<nc;c++)
                                {
                                        printf("   %d", t);
                                        t++;
                                }
                        }
                        if(f%2!=0)
                        {
                                printf_reset_color();
                                printf_color_negrita();
                                printf(" ");
                                for(c=0;c<nc;c++)
                                {
                                        if(f==1)
                                                printf("+---");
                                        else
                                                printf("+   ");
                                }
                                printf("+");
                        }
                        if(f!=0 && f%2==0)
                        {
                                printf("%c| ", charf);
                                charf++;
                                for(c=0;c<nc;c++)
                                {
                                        num = leer_int_fichero();
                                        printf_color_num(num);
                                        printf("%d   ", num);
                                }

                        }

                        printf("\n");
                }
                cerrar_fichero();
                printf("\nConexiones: %u de %u\n\nCasillas a conectar/desconectar (ej: [A0B0]): ", conexiones, max_conexiones); 
                scanf("%c%d%c%d%*c", &y1, &casilla1.x, &y2, &casilla2.x);
                if(y1>='a' && y1<='z')
                        y1 = 'A'+y1-'a';
                if(y2>='a' && y1<='z')
                        y2 = 'A'+y2-'a';
                while(y1>=nf/2-2 || y2>=nf/2-2 || casilla1.x>=nc || casilla2.x>=nc) {
                        while(y1+1!=y2 && y1-1!=y2 && y1!=y2 || casilla1.x+1!=casilla2.x && casilla1.x-1!=casilla2.x && casilla1.x!=casilla2.x || y1==y2 && casilla1.x==casilla2.x)
                        {
                                printf("Casillas a conectar/desconectar (ej: [A0B0]): "); 
                                scanf("%c%d%c%d%*c", &y1, &casilla1.x, &y2, &casilla2.x);
                                if(y1>='a' && y1<='z')
                                        y1 = 'A'+y1-'a';
                                if(y2>='a' && y1<='z')
                                        y2 = 'A'+y2-'a';
                                printf("%c%d%c%d\n", y1, casilla1.x, y2, casilla2.x);
                        }
                }

                // conexiones = max_conexiones;

        }
}