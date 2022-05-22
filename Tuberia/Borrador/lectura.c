#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "datos.h"
int main()
{

    // Ruta del archivo tuberia
    char *tuberia = "./mainLectura";
    char *tuberia2 = "./lecturaMain";


    int cantidad = 0;
    for (int potencia = 0; potencia < 6; potencia++)
    {
        int tamano = 1000 * pow(10, potencia) * sizeof(char);
        printf("Tamano del buffer de lectura %d\n", tamano);
        char *buffer = malloc(tamano);

        
        // Se lee el mensaje de la tuberia
        int r = leerTuberia(tuberia,buffer,tamano);
        
        cantidad = r + cantidad;
        while (r != 0)
        {
            // Se lee el mensaje de la tuberia
            r = leerTuberia(tuberia,buffer+r,tamano);
            cantidad = r + cantidad;
            if (r < 0)
            {
                perror("Hubo un error leyendo el archivo de la tuberia");
                exit(-1);
            }
        }
        printf("La cantidad de bytes leidos fue %d\n", cantidad);

        mkfifo(tuberia2,0666);
        if (cantidad == tamano){
            escribirTuberia(tuberia2,"OK",2);
        }else{
            escribirTuberia(tuberia2,"NO",2);
        }
        cantidad = 0;
        
    }
    
    return 0;
}