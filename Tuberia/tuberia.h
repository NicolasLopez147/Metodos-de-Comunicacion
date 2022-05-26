#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int escribirTuberia(char *tuberia, char *buffer, int tamano)
{
    // Descriptor del archivo
    int descriptor;

    // Cantidad total de bytes escritos
    int cantidad = 0;
    // Se abre el archivo en modo escritura
    descriptor = open(tuberia, O_WRONLY);
    if (descriptor < 0)
    {
        perror("Hubo un error abriendo el archivo de la tuberia");
        exit(-1);
    }
    int r;
    while (cantidad < tamano)
    {
        // r es la cantidad de bytes escritos por write
        r = write(descriptor, buffer + cantidad, tamano);
        if (r < 0)
        {
            perror("No se pudo escribir en la tuberia");
            exit(-1);
        }
        // printf("Bytes escritos %d\n",r);

        // Se ira sumando cada r hasta que se escriban todos los datos
        cantidad = cantidad + r;
    }
    // Se cierra el descriptor
    close(descriptor);
    return cantidad;
}

int leerTuberia(char *tuberia, char *buffer, int tamano)
{
    // Descriptor del archivo
    int descriptor;
    // Cantidad total de bytes leidos
    int cantidad = 0;
    do
    {
        // Espera a que se cree el archivo tipo FIFO tuberia2
        descriptor = open(tuberia, O_RDONLY);
    } while (descriptor == -1);

    int r;
    while (cantidad < tamano)
    {
        // r es la cantidad de bytes leidos por read
        r = read(descriptor, buffer + cantidad, tamano);
        // Se ira sumando cada r hasta que se escriban todos los datos
        cantidad = r + cantidad;
    }

    if (r < 0)
    {
        perror("Hubo un error leyendo el archivo de la tuberia");
        exit(-1);
    }
    // Se cierra el descriptor
    close(descriptor);
    return cantidad;
}