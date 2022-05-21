#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // Descriptor del archivo
    int descriptorTuberia;

    // int tamano = 10000 * sizeof(char);

    // Ruta del archivo tuberia
    char *tuberia = "./tuberia";

    // char *buffer = malloc(tamano);

    // Se abre la tuberia
    descriptorTuberia = open(tuberia, O_RDONLY);
    if (descriptorTuberia < 0)
    {
        perror("Hubo un error abriendo el archivo de la tuberia");
        exit(-1);
    }
    int bandera = 1;
    int contador = 0;
    // while(bandera)
    // {

    //     //Se lee el mensaje de la tuberia
    //     int r = read(descriptorTuberia,buffer,tamano);
    //     if (r < 0){
    //         perror("Hubo un error leyendo el archivo de la tuberia");
    //         exit(-1);
    //     }
    //     printf("Se leyeron %d bytes\n",r);
    //     printf("Ultimo byte leido %s\n",(buffer+r));
    //     contador++;
    //     // if (r == 0){
    //     //     contador++;
    //     // }
    //     // if (contador > 20){
    //     //     bandera = 0;
    //     // }

    // }
    int potencia = 2;
    // for (int potencia; potencia < 6; potencia++)
    // {
        int tamano = 1000 * pow(10, potencia) * sizeof(char);
        // size_t tamano = 34463*sizeof(char);

        char *buffer = malloc(tamano);
        // Se lee el mensaje de la tuberia
        int r = read(descriptorTuberia, buffer, tamano);

        while (contador != 5){
            // Se lee el mensaje de la tuberia
            r = read(descriptorTuberia, buffer+r, tamano);

            if (r < 0)
            {
                perror("Hubo un error leyendo el archivo de la tuberia");
                exit(-1);
            }
            // if (*(buffer+r) == 'a'   )
            // printf("Ultimo byte leido %s\n",(buffer+r));
            contador++;
            printf("Tamano mensaje recibido %d\n",r);
        }
        
    // }

    printf("Cantidad de veces que se leee %d\n", contador);

    close(descriptorTuberia);
    return 0;
}