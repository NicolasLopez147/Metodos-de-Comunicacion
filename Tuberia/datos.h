#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


int escribirTuberia(char *tuberia, char * buffer, int tamano,int *apDescriptor)
{
    // Descriptor del archivo
    int descriptor = *apDescriptor; 
    descriptor = open(tuberia, O_WRONLY);
    if (descriptor < 0)
    {
        perror("Hubo un error abriendo el archivo de la tuberia");
        exit(-1);
    }
    //Numero de bytes escritos
    int r = write(descriptor, buffer, tamano);
    printf("Despues del write\n");
    if (r < 0)
    {
        perror("No se pudo escribir el origen en la tuberia");
    }
    return r;
}

int leerTuberia(char *tuberia, char *buffer, int tamano,int *apDescriptor)
{   
    int descriptor = *apDescriptor;
    // Se abre la tuberia
    do
    {
        // Espera a que se cree el archivo tipo FIFO memuBuscador
        descriptor = open(tuberia, O_RDONLY);
        // printf("Hola mundo");
    } while (descriptor == -1);

    if (descriptor < 0)
    {
        perror("Hubo un error abriendo el archivo de la tuberia");
        exit(-1);
    }
    // Lee el archivo FIFO y guarla la informacion en buffer, retorna el numero de bytes leidos
    int r = read(descriptor, buffer, tamano);
    if (r < 0)
    {
        perror("Hubo un error leyendo el archivo de la tuberia");
        exit(-1);
    }
    return r;
}