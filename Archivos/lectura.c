#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/file.h>   // flock

#define KILOB 1000

int main() {
    char *archivo1 = "./salida.txt";
    char *archivo2 = "./respuesta.txt";

    int cantidad, r, tamano;
    int tamanoConfirm = 2;

    // Apertura de archivos
    FILE *salida = fopen(archivo1, "r");
    if(salida == NULL) {
        perror("Error al abrir el archivo de salida\n");
    }
    
    FILE *respuesta = fopen(archivo2, "w");
    if(respuesta == NULL) {
        perror("Error al abrir el archivo de respuesta\n");
    }

    for(int potencia = 0; potencia < 6; potencia++) {
        // Repeticiones
        int limite = 100;
        if(potencia == 5) {
            limite = 10;
        }

        for(int i = 0; i < limite; i++) {
            tamano = KILOB * pow(10, potencia) * sizeof(char);
            char *buffer = malloc(tamano);

            // Bloquear archivo de respuesta primero
            r = flock(fileno(respuesta), LOCK_EX);
            if(r < 0) {
                perror("Error bloqueando el archivo de respuesta\n");
            }

            // Lectura del archivo de salida
            r = flock(fileno(salida), LOCK_SH);
            if(r < 0) {
                perror("Error bloqueando el archivo de salida\n");
            }

            fseek(salida, 0, SEEK_SET);
            fread(buffer, tamano, 1, salida);

            r = flock(fileno(salida), LOCK_UN);
            if(r < 0) {
                perror("Error desbloqueando el archivo de salida\n");
            }

            // Confirmacion
            char *confirmacion = "OK";
            fwrite(confirmacion, strlen(confirmacion), 1, respuesta);

            r = flock(fileno(respuesta), LOCK_UN);
            if(r < 0) {
                perror("Error desbloqueando el archivo de respuesta\n");
            }
        }
    }






    fclose(salida);
    fclose(respuesta);
}