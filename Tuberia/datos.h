#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


int escribirTuberia(char *tuberia, char * buffer, int tamano)
{
    // Descriptor del archivo
    int descriptor; 

    int cantidad = 0;
    descriptor = open(tuberia, O_WRONLY);
    if (descriptor < 0)
    {
        perror("Hubo un error abriendo el archivo de la tuberia");
        exit(-1);
    }
    int r;
    while(cantidad < tamano){
        r = write(descriptor, buffer+cantidad, tamano);
        if (r < 0)
        {
            perror("No se pudo escribir en la tuberia");
            exit(-1);
        }
        // printf("Bytes escritos %d\n",r);
        cantidad = cantidad+r;
    }
    close(descriptor);
    return cantidad;
}

int leerTuberia(char *tuberia, char *buffer, int tamano)
{   
    int descriptor;
    int cantidad = 0;
    // Se abre la tuberia
    do
    {
        // Espera a que se cree el archivo tipo FIFO memuBuscador
        descriptor = open(tuberia, O_RDONLY);
        // printf("Hola mundo");
    } while (descriptor == -1);

    // if (descriptor < 0)
    // {
    //     perror("Hubo un error abriendo el archivo de la tuberia");
    //     exit(-1);
    // }
    int r;
    while(cantidad < tamano){
        r = read(descriptor, buffer+cantidad, tamano);
        cantidad = r+cantidad;
    }
    // Lee el archivo FIFO y guarla la informacion en buffer, retorna el numero de bytes leidos
    if (r < 0)
    {
        perror("Hubo un error leyendo el archivo de la tuberia");
        exit(-1);
    }
    close(descriptor);
    return cantidad;
}