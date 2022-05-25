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
    FILE *salida = fopen(archivo1, "w");
    if(salida == NULL) {
        perror("Error al abrir el archivo de salida\n");
    }

    FILE *respuesta = fopen(archivo2, "r");
    if(respuesta == NULL) {
        perror("Error al abrir el archivo de respuesta\n");
    }

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

            // Escritura del archivo de salida
            r = flock(fileno(salida), LOCK_EX);
            if(r < 0) {
                perror("Error bloqueando el archivo de salida\n");
            }

            fseek(salida, 0, SEEK_SET);
            fwrite(buffer, tamano, 1, salida);

            r = flock(fileno(salida), LOCK_UN);
            if(r < 0) {
                perror("Error desbloqueando el archivo de salida\n");
            }

            // Lectura del archivo de respuesta
            r = flock(fileno(respuesta), LOCK_SH);
            if(r < 0) {
                perror("Error bloqueando el archivo de respuesta\n");
            }

            char confirmacion[tamanoConfirm];
            fread(confirmacion, tamanoConfirm, 1, respuesta);
            confirmacion[tamanoConfirm] = 0;
            // printf("%s %d\n", confirmacion, i);

            r = flock(fileno(respuesta), LOCK_UN);
            if(r < 0) {
                perror("Error desbloqueando el archivo de respuesta\n");
            }

            clock_t fin = clock();
            double tiempo = (double)(fin-inicio)/CLOCKS_PER_SEC;
            tiempoTotal = tiempoTotal+tiempo;
        }

        tiempoTotal = tiempoTotal/limite;
        printf("El tiempo promedio enviando %d datos y recibiendo una confirmacion es de %f\n",tamano,tiempoTotal);
    }

    fclose(salida);
    fclose(respuesta);
}