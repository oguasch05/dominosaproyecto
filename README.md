# dominosaproyecto

El codigo del proyecto está en dominosa.c

Para compilar: 

    make
    
Para ejecutar:
    
    ./dominosa

Para ejecutar el codigo modelo: 

    ./ejdominosa

    
GITHUB

Para guardar el codigo en la nube: 

    git add .
    
    git commit -m "mensaje corto que explica tus cambios" (o simplemente "cambios en dominosa.c")
    
    git push


https://www.puzzle-dominosa.com/
https://es.puzzle-dominosa.com/

- Para compilar los testers:
gcc -Wall -o test_colores test_colores.c colores.c
gcc -Wall -o test_ficheros test_ficheros.c fichero.c

- Para poder ejecutar el Dominosa:
./dominosa

- Los ficheros con los Dominosas que se os dan están en ficheros .txt cuyo
nombre empieza por el número del doble más alto con el que se juega
(ej: 3001.txt usa las fichas desde el doble cero hasta el doble tres.

- El programa debe funcionar para tableros desde 1x2 (0x0 dominosa, que sólo
tiene el doble cero) hasta 10x11 (9x9 dominosa, que tiene del doble cero al
doble nueve).

- Los datos que introduce el usuario pueden estar en mayúsculas y/o minúsculas.

- En caso de conexión inválida (por casillas inexistentes o no contiguas), se
sigue pidiendo la nueva conexión. No se muestra mensaje de error.

- El juego acaba cuando el dominosa está bien resuelto.