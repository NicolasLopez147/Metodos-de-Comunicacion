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

        for(int i = 0; i < limite; i++) {
            tamano = KILOB * pow(10, potencia) * sizeof(char);
            char *buffer = malloc(tamano);

            // Obtener bloque de memoria compartida
            shmId = shmget(key, tamano+tamanoConfirm+2*sizeof(int), 0666);
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

            // Bloquear bloque de respuesta primero
            *controlRespuesta = 1;

            // Esperar la salida; idealmente corregir
            while(*controlSalida != 0) {
                // printf("%d\n", *controlSalida);
                // sleep(1);
            }

            // Leer bloque de salida
            *controlSalida = 1;
            memcpy(buffer, salida, tamano);
            *controlSalida = 0;

            // Escribir bloque de respuesta
            char *confirmacion = "OK";
            memcpy(respuesta, confirmacion, tamanoConfirm);
            *controlRespuesta = 0;

            shmdt(salida);
        }
    }
    
}