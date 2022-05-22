#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "datos.h"

int main(){
    // Ruta del archivo tuberia
    char *tuberia = "./tuberia";
    char *tuberia2 = "./tuberia2";

    // Crear un archivo de tipo fifo
    int *descriptor;
    int cantidad = 0;

    
    for (int potencia = 0; potencia < 5 ; potencia ++){
        for (int i = 0 ; i < 20 ; i ++){
            mkfifo(tuberia, 0666);
            int tamano = 1000 * pow(10, potencia) * sizeof(char);
            
            char * buffer = malloc(tamano);

            int r = escribirTuberia(tuberia,buffer,tamano,descriptor);
            printf("Bytes escritos %d\n",r);
            
            cantidad = cantidad+r;
            while(cantidad < tamano){
                printf("Antes de escirbir \n");
                r = escribirTuberia(tuberia,buffer+cantidad,tamano,descriptor);
                cantidad = r+cantidad;
            }
            printf("La cantudad total de bytes escritos es %d\n",cantidad);
            cantidad = 0;
            char confirmacion [3];
            
            r = leerTuberia(tuberia2,confirmacion,2,descriptor);
            close(*descriptor);
            confirmacion[3] = 0;
            printf("Mensaje de confirmacion %s\n",confirmacion);
            unlink(tuberia2);
        }
    }
    
}