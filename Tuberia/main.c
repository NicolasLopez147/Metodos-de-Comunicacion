#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <time.h>
#include "datos.h"

#define KILOB 1000

int main(){
    // Ruta del archivo tuberia
    char *tuberia = "./tuberia";
    char *tuberia2 = "./tuberia2";

    // Crear un archivo de tipo fifo
    int tamano;
    for (int potencia = 0; potencia < 6 ; potencia ++){
        int limite = 100;
        double tiempoTotal = 0;
        for (int i = 0 ; i < limite ; i ++){
            clock_t inicio = clock();
            mkfifo(tuberia, 0666);
            tamano = KILOB * pow(10, potencia) * sizeof(char);
            char * buffer = malloc(tamano);
            int cantidad  = escribirTuberia(tuberia,buffer,tamano);

            // printf("La cantidad total de bytes escritos es %d i %d\n",cantidad,i);
            free(buffer);
            char confirmacion [3];
            
            cantidad = leerTuberia(tuberia2,confirmacion,2);
            confirmacion[3] = 0;
            // printf("Mensaje de confirmacion %s\n",confirmacion);
            unlink(tuberia2);
            int reloj = 0;
            // while(reloj < 100000000){
            //     reloj++;
            // }
            clock_t fin = clock();
            double tiempo = (double)(fin-inicio)/CLOCKS_PER_SEC;
            tiempoTotal = tiempoTotal+tiempo;
        }
        tiempoTotal = tiempoTotal/limite;
        printf("El tiempo promedio enviando %d datos y recibiendo una confirmacion es de %f\n",tamano,tiempoTotal);
    }
    
}