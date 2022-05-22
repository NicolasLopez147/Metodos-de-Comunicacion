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
    char *tuberia = "./tuberia";
    char *tuberia2 = "./tuberia2";

    char a;
    int cantidad = 0;
    int *descriptor;
    for (int potencia = 0 ; potencia < 5 ; potencia ++){

        for (int i = 0 ; i < 20 ; i ++){
            int tamano = 1000 * pow(10, potencia) * sizeof(char);
            char * buffer = malloc(tamano);
            int r = leerTuberia(tuberia,buffer,tamano,descriptor);
            close(*descriptor);

            cantidad = r+cantidad;
            while(cantidad < tamano){
                r = leerTuberia(tuberia,buffer+cantidad,tamano,descriptor);
                close(*descriptor);
                printf("Valor de r %d\n",r);
                cantidad = r+cantidad;
                printf("Cantidad %d\n",cantidad);
                printf("Tamano %d\n",tamano);
            }

            printf("Bytes leidos %d\n",cantidad);
            printf("Tamano de bytes a leer %d\n",tamano);
            
            // scanf("%s",&a);
            unlink(tuberia);


            mkfifo(tuberia2,0666);
            char confirmacion [] = "OK";

            r = escribirTuberia(tuberia2,confirmacion,2,descriptor);
            close(*descriptor);
            cantidad = 0;
        }
    }
}