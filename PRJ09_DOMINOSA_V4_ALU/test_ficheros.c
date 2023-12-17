// Este fichero se le da al alumno
#include <stdio.h>
#include "fichero.h"

#define SIZE_NOMBRE_FICHERO	  80

int main() {
	int err, f, c, n, nf, nc, num;
	char nombre_fichero[SIZE_NOMBRE_FICHERO];

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
		printf("Dominosa %dx%d, fils = %d, cols = %d\n\n",
			       n, n, nf, nc);
		for (f = 0; f < nf; f++) {
			for (c = 0; c < nc; c++) {
				num = leer_int_fichero();
				printf("%d ", num);
				scanf("%*c");
			}
			printf("\n");
		}
		cerrar_fichero();
	}
}

