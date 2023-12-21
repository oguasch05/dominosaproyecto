//----------------------------------------------------------- INCLUDES -------------------------------------------------------
#include <stdio.h>
#include "colores.h"
#include "fichero.h"

//--------------------------------------------------------- CONSTANTES --------------------------------------------------------

#define SIZE_NOMBRE_FICHERO     80
#define MAX_FILAS               11
#define MAX_COLUMNAS            10
#define MAX_N			9
#define TRUE                    1
#define FALSE                   0

//------------------------------------------------------------ STRUCTS --------------------------------------------------------
	
typedef struct
{
    int valor; //valor casilla 0-9
    int e, s; //0 o 1 (true or false)  
} tcasilla;

typedef struct
{
    int nf, nc, n;
    tcasilla mat[MAX_FILAS][MAX_COLUMNAS];
} tablero;

//--------------------------------------------------- DECLARACIÓN DE FUNCIONES --------------------------------------------------

tablero inicializar(tablero t); //da a escoger un tablero de juego y lee el fichero que lo contiene guardando la información que este contiene y returnando el valor de ciertos paràmetros del tablero 
int dibujar(tablero t); //printa el tablero escogido en la función inicializar y las conexiones que se van realizando
int comprobar(tablero t); //comprueba que las conexiones introducidas sean válidas, posibles y correctas


//---------------------------------------------------------- MAIN ---------------------------------------------------------------

int main()
{
	// Pasos del juego:
	// 1.- Inicializamos las variables
	// 2.- Generamos un tablero a partir del fichero seleccionado
	// 3.- Pintamos el tablero con el que vamos a jugar
	// 4.- Recibimos la jugada del usuario , comprobamos si esta jugada es valida y la realizamos en el caso de que todos los filtros se cumplan
	// 5.- Pintamos el tablero
	// Se iteran los puntos 4 y 5 hasta que todo el tablero este relleno
	// 7.- Se determina que el juego ha terminado
	
    tablero t;
    unsigned int conexiones;
	int f, c, conexiones_reales=0, title, c1, c2, f1, f2, max_conexiones;
	char charf, y1, y2;

	t = inicializar(t); 							//inicia el juego
        max_conexiones = t.nf*t.nc/2; 						//número de conexiones máximas
        if(t.n!=-1)
        {
                do {				//se repite mientras las conexiones realizadas no coincidan con las de cada una de las fichas
                        conexiones = dibujar(t); 
                        conexiones_reales = comprobar(t);
                        if(conexiones_reales<max_conexiones)
                        {
                        do
                        {               
                        printf("Casillas a conectar/desconectar (ej: [A0B0]): "); 			//pide valores de las dos casillas que se quieren conectar o desconectar
                        scanf("%c%d%c%d%*c", &y1, &c1, &y2, &c2);       				//guarda los valores de las dos casillas a conectar en y1, y2, c1, c2 siendo 'y' la letra (char) de la fila escogida (que se pasará a int) y 'c' el número de la columna, 1 y 2 hacen referencia a la casilla primera o segunda que queremos conectar
                        if(y1>='a'&&y1<='z')								//evalúa que la letra de la primera casilla sea minúscula 
                        {
                                f1 = y1-'a'; 								//si la letra introducida es minúscula, f1 pasa a valer un número (a=0,b=1,c=2,...)
                        }
                        if(y1>='A'&&y1<='Z')								//evalúa que la letra de la primera casilla sea mayúscula 
                        {
                                f1 = y1-'A'; 								//si la letra introducida es mayúscula, f1 pasa a valer un número (A=0,B=1,C=2,...)
                        }
                        if(y2>='a'&&y2<='z')								//evalúa que la letra de la segunda casilla sea minúscula 
                        {
                                f2 = y2-'a'; 								//si la letra introducida es minúscula, f2 pasa a valer un número (a=0,b=1,c=2,...)
                        }
                        if(y2>='A'&&y2<='Z')								//evalúa que la letra de la segunda casilla sea mayúscula
                        {
                                f2 = y2-'A'; 								//si la letra introducida es mayúscula, f2 pasa a valer un número (A=0,B=1,C=2,...)
                        }
                        }
                        while(c1==c2 && f1==f2 || c1!=c2 && f1!=f2 || c1-c2!=1 && f1-f2!=1 && c2-c1!=1 && f2-f1!=1 || f1>t.nf-1 || f2>t.nf-1 || c1>t.nc || c2>t.nc); //comprueba que la conexión es posible mirando si las casillas escogidas son consecutivas
                                        
                        if(f1>f2) 									//mira que la conexión sea vertical ascendente (de abajo a arriba)
                        {
                        if(t.mat[f2][c1].s == TRUE)							//si la conexión evaluada ya existe, la borra
                        {
                                t.mat[f2][c1].s = FALSE;
                        }
                        else										//mira que la conexión no este hecha con anterioridad
                        {
                                t.mat[f1][c1].e = FALSE;						//mira que no haya conexiones que interfieran con la que queremos añadir y si las hay las elimina
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
                        else if(f1<f2) 									//mira que la conexión sea horizontal descendente (de arriba a abajo)
                        {
                        if(t.mat[f1][c1].s == TRUE)							//hace el mismo proceso que antes de evaluar si la conexión ya existía y hace los cambios necesarios para que se pueda hacer o deshacer la conexión
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
                        else if(c1>c2) 									//mismo procedimiento está vez evaluando las conexiones horizontales de derecha a izquierda
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
                        else if(c1<c2)									//mismo procedimiento evaluando las conexiones horizontales de izquierda a derecha
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
                        }     
                        }
                }
                while(conexiones_reales<max_conexiones);
        }
        if (conexiones_reales==max_conexiones)
        printf("FELICIDADES! HAS RESUELTO ESTE DOMINOSA! B-)\n\n");					//mensaje que muestra que el juego ha acabado y el jugador ha ganado la partida
}

//-------------------------------------------------------- FUNCIONES -------------------------------------------------------------

tablero inicializar(tablero t)
{
	int err, f, c;
	char nombre_fichero[SIZE_NOMBRE_FICHERO];
        t.n=-1;

	printf("Introduce el nombre del fichero: ");
	scanf("%s%*c", nombre_fichero);
	err = abrir_fichero(nombre_fichero);
	if (err != ABRIR_FICHERO_OK) {							//en caso de que el fichero no se pueda abrir, se muestra el siguiente mensaje
		printf("ERROR: FICHERO NO ENCONTRADO.\n");
		printf("PUEDE QUE EL NOMBRE NO SEA EL CORRECTO O QUE ESTE EN OTRO DIRECTORIO.\n");
	} 
        else 										//lectura de la información de la partida extraida del fichero
        {
		t.n = leer_int_fichero();   						//número mas grande que aparece
		t.nf = leer_int_fichero();  						//número de filas
		t.nc = leer_int_fichero();  						//número de columnas

                for(f=0;f<t.nf;f++)							//bucle para inicializar todos los valores del tablero y sus conexiones en condiciones iniciales
                {
                        for(c=0;c<t.nc;c++)
                        {
                                t.mat[f][c].valor = leer_int_fichero(); 		//guarda los valores del tablero en la matriz casilla[][].valor
                                t.mat[f][c].e = FALSE; 					//borra todas las conexiones en e
                                t.mat[f][c].s = FALSE; 					//borra todas las conexiones en s
                        }
                }
                cerrar_fichero();
	}
	return t; 									//devuelve una variable de struct tablero
}


int dibujar(tablero t)
{
	int conexiones = 0, f, c, max_conexiones; 					//número de conexiones
	char charf = 'A'; 								//cabecera de fila
    unsigned int title = 0; 								//cabecera de columna
    printf_color_negrita();
    printf("\n");
	
    for(c=0;c<t.nc;c++)									//bucle que se repite hasta printar la cabecera de las columnas
    {
        printf("   %d", title); 							//escribe cada valor de la cabecera de las columnas
        title++;
    } printf("\n ");
    for(c=0;c<t.nc;c++)									//bucle para printar el tablero en el formato del ejemplo
    {
        printf("+---");
    } printf("+\n"); 
    for(f=0;f<t.nf;f++)									//bucle que va de fila en fila printando la cabecera de las filas
    {
        printf("%c| ", charf); 								//escribe la letra de la cabecera de las fila
        charf++;
	    
    	for(c=0;c<t.nc;c++)								//bucle que dentro del bucle de las filas, va printado en el color que toca el valor de cada casilla de columna en columna
        {
            printf_color_num(t.mat[f][c].valor); 					//cambia el color al color del valor de la casilla
            printf("%d", t.mat[f][c].valor);     					//escribe el valor de las casillas
            printf_reset_color();							//devuelve el color al inicial
            printf_color_negrita();
            if(t.mat[f][c].e==TRUE)							//evalúa si hay una conexión en la casilla que se está printando
            {
                printf("███");  							//escribe la conexión en caso de que casilla[][].e sea cierto
                conexiones++;                                                
            }
            else
                printf("   ");  							//escribe un espacio en blanco en caso de que casilla[][].e sea falso
        } printf("\n");
	    
        for(c=0;c<t.nc;c++)								//este bucle escribe la separación entre columnas y las conexiones verticales
        {
            printf(" + ");
            if(t.mat[f][c].s == TRUE)
            {
                printf("█"); 								//escribe la conexión en caso de que casilla[][].s sea cierto
                conexiones++;
            }
        	else
                printf(" "); 								//escribe un espacio en blanco en caso de que casilla[][].e sea falso
        } printf(" +\n");
    }
	printf("\n");
	max_conexiones = t.nf*t.nc/2; 							//número de conexiones máximas
    printf("\nConexiones: %u de %u\n\n", conexiones, max_conexiones); 			//escribe "__ conexiones de __", es decir, el número de conexiones que hay actualmente hechas respecto al número total de conexiones
	return conexiones;								//devuelve las conexiones realizadas
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
