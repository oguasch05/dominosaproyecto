#include <stdio.h>
#include "colores.h"
#include "fichero.h"

#define SIZE_NOMBRE_FICHERO     80
#define MAX_SIZE                11

typedef struct casilla
{
        int valor; //valor casilla 0-6
        int e[MAX_SIZE], s[MAX_SIZE]; //0 o 1 (true or false)  (0, 0, 1, 0, 0, 0, 0, 0 ,0 ,0) e[2] = 1
        int f[MAX_SIZE], c[MAX_SIZE]; //fila o columna de la casilla
} tcasilla;

int main()
{
        tcasilla casilla1;

        unsigned int conexiones = 0, max_conexiones;
        int err, f, c, n, nf, nc, num, t, x1, x2;
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
                for(f=0;f<nf*2+2;f++)
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
                                        printf("%d", num);
                                        printf_reset_color();
                                        printf_color_negrita();
                                        if(f==casilla1.f && c==casilla1.c)
                                        if(casilla1.e==c/* && casilla1.s==f*2+3*/)
                                        {
                                                printf("███");                                                
                                        }
                                        else
                                                printf("   ");
                                }

                        }

                        printf("\n");
                }
                cerrar_fichero();
                printf("\nConexiones: %u de %u\n\nCasillas a conectar/desconectar (ej: [A0B0]): ", conexiones, max_conexiones); 
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
                while(y1>nc || y2>nc || x1>nf || x2>nf || y1==y2 && x1==x2)
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
                if(y1+1==y2 && x1==x2)
                {
                        casilla1.s = 1;
                }
                if(x1+1==x2 && y1==y2)
                {
                        casilla1.c[x1] = 
                        casilla1.e = x1;
                }


                // conexiones = max_conexiones;

        }
}