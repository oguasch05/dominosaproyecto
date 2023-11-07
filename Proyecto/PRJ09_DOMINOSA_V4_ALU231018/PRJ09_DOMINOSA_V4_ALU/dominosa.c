#include <stdio.h>
#include "colores.h"
#include "fichero.h"

#define SIZE_NOMBRE_FICHERO     80
#define MAX_CASILLAS            11

typedef struct casilla
{
        int valor; //valor casilla 0-9
        int e, s; //0 o 1 (true or false)  
} tcasilla[121];

int main()
{
        tcasilla casilla;

        unsigned int conexiones = 0, max_conexiones;
        int err, f, c, n, nf, nc, num, t, x1, x2, i, num_casillas;
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

                for(i=0;i<=nf*nc;i++)
                {
                        casilla[i].valor = leer_int_fichero();
                        casilla[i].e = 0;
                        casilla[i].s = 0;
                }
                cerrar_fichero();
	}
        while(conexiones < max_conexiones)
        {
                charf = 'A';
                t = 0, i=0;
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
                                printf_color_num(casilla[i].valor);
                                printf("%d", casilla[i].valor);
                                printf_reset_color();
                                printf_color_negrita();
                                if(casilla[i].e==1)
                                {
                                        printf("███");                                                
                                }
                                else
                                        printf("   ");
                                i++;
                        } printf("\n");
                        i = i-nc;
                        for(c=0;c<nc;c++)
                        {
                                printf(" + ");
                                if(casilla[i].s == 1)
                                        printf("o");
                                else
                                        printf(" ");
                                i++;
                        } printf(" +\n");

                }

                printf("\n");
                printf("\nConexiones: %u de %u\n\n", conexiones, max_conexiones);

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
                        casilla[nc*y2+x1].s = 1;
                else if(y1<y2)
                        casilla[nc*y1+x1].s = 1;
                else if(x1>x2)
                        casilla[nc*y1+x2].e = 1;
                else if(x1<x2)
                        casilla[nc*y1+x1].e = 1;       


        }
}