#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define KILOB 1000

int main() {
    key_t key = 1234;
    int tamano, shmId;
    int tamanoConfirm = 2;
    char *salida, *respuesta;
    int *controlSalida, *controlRespuesta;

    for(int potencia = 0; potencia < 6; potencia++) {
        // Repeticiones
        int limite = 100;
        if(potencia == 5) {
            limite = 10;
        }
        double tiempoTotal = 0;

        for(int i = 0; i < limite; i++) {
            clock_t inicio = clock();

            tamano = KILOB * pow(10, potencia) * sizeof(char);
            char *buffer = malloc(tamano);

            // Crear un solo bloque de memoria compartida
            // para los bloques de salida, respuesta y una variable de control
            shmId = shmget(key, tamano+tamanoConfirm+2*sizeof(int), IPC_CREAT|0666);
            if(shmId < 0) {
                perror("Error en shmget\n");
                exit(-1);
            }

            // Asignar apuntadores a la memoria compartida
            salida = (char *) shmat(shmId, 0, 0);
            if(salida < 0) {
                perror("Error en shmat\n");
                exit(-1);
            }
            respuesta = salida + tamano;
            controlSalida = (int *) respuesta + tamanoConfirm;
            controlRespuesta = controlSalida + sizeof(int);

            // Escribir bloque de salida
            *controlSalida = 1;
            memcpy(salida, buffer, strlen(buffer));
            *controlSalida = 0;

            // Esperar la respuesta; idealmente corregir
            while(*controlRespuesta != 0) {
                // printf("%d\n", *controlRespuesta);
                // sleep(1);
            }

            // Leer bloque de respuesta
            *controlRespuesta = 1;
            char confirmacion[tamanoConfirm];
            memcpy(confirmacion, respuesta, tamanoConfirm);
            confirmacion[tamanoConfirm] = 0;
            // printf("%s %d\n", confirmacion, i);
            *controlRespuesta = 0;

            shmdt(salida);
            // Liberar llave
            shmctl(shmId, IPC_RMID, NULL);

            clock_t fin = clock();
            double tiempo = (double)(fin-inicio)/CLOCKS_PER_SEC;
            tiempoTotal = tiempoTotal+tiempo;
        }

        tiempoTotal = tiempoTotal/limite;
        printf("El tiempo promedio enviando %d datos y recibiendo una confirmacion es de %f\n",tamano,tiempoTotal);
    }
}