#include "tuberia.h"


#define KILOB 1000

int main()
{
    // Ruta del archivo tuberia
    char *tuberia = "./tuberia";
    char *tuberia2 = "./tuberia2";

    int tamano;
    // Potencia de diez que tendran los datos
    for (int potencia = 0; potencia < 6; potencia++)
    {
         // Cantidad de veces que se enviara el mismo tamaño de datos
        int limite = 50;
        double tiempoTotal = 0;
        for (int i = 0; i < limite; i++)
        {
            // Se guarda la hora inicial
            clock_t inicio = clock();

            // Crear un archivo de tipo fifo
            mkfifo(tuberia, 0666);

            // Tamaño calcula el tamaño de los datos
            tamano = KILOB * pow(10, potencia) * sizeof(char);
            char *buffer = malloc(tamano);

            // Cantidad es la cantidad de bytes escritos por la tuberia
            int cantidad = escribirTuberia(tuberia, buffer, tamano);

            // printf("La cantidad total de bytes escritos es %d i %d\n",cantidad,i);

            // Se libera la memoria utilizada en los datos
            free(buffer);

            // Se recibe el mensaje de confirmacion
            char confirmacion[3];
            cantidad = leerTuberia(tuberia2, confirmacion, 2);
            confirmacion[3] = 0;
            // printf("Mensaje de confirmacion %s\n",confirmacion);

            // Se elimina el archivo FIFO
            unlink(tuberia2);

            // Se guarda la hora final y se calcula el tiempo empleado en segundos
            clock_t fin = clock();
            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

            // Se suman todos los tiempos parciales y se divide por el total
            tiempoTotal = tiempoTotal + tiempo;
        }
        tiempoTotal = tiempoTotal / limite;
        printf("El tiempo promedio enviando %d datos y recibiendo una confirmacion es de %f\n", tamano, tiempoTotal);
    }
}