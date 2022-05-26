#include "tuberia.h"

#define KILOB 1000

int main()
{
    // Ruta del archivo tuberia
    char *tuberia = "./tuberia";
    char *tuberia2 = "./tuberia2";

    // Potencia de diez que tendran los datos
    for (int potencia = 0; potencia < 6; potencia++)
    {
        // Cantidad de veces que se enviara el mismo tamaño de datos
        int limite = 50;

        for (int i = 0; i < limite; i++)
        {
            // Tamaño calcula el tamaño de los datos
            int tamano = KILOB * pow(10, potencia) * sizeof(char);
            char *buffer = malloc(tamano);
            // Cantidad de bytes leidos por la tuberia
            int cantidad = leerTuberia(tuberia, buffer, tamano);

            printf("Bytes leidos %d iteracion %d\n", cantidad, i);
            // Se elimina el archivo FIFO
            unlink(tuberia);

            // Se libera la memoria utilizada en los datos
            free(buffer);

            // Se crea un segundo archivo FIFO para enviar la confirmacion de los datos
            mkfifo(tuberia2, 0666);

            // Se envia un mensaje dependiendo si se recibieron todos los datos
            if (tamano == cantidad)
            {
                escribirTuberia(tuberia2, "OK", 2);
            }
            else
            {
                escribirTuberia(tuberia2, "NO", 2);
            }
        }
    }
}