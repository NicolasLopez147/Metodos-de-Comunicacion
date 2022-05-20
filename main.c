#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    //Descriptor del archivo
    int descriptorTuberia;
    //Ruta del archivo tuberia
    char *tuberia = "./tuberia"; 

    //Crear un archivo de tipo fifo
    mkfifo(tuberia,0666);
    
    //Se abre la tuberia en modo de escritura
    descriptorTuberia = open(tuberia,O_WRONLY);

    if (descriptorTuberia < 0){
        perror("Hubo un error abriendo el archivo de la tuberia");
        exit(-1);
    }
    for (int potencia = 1 ; potencia < 2;potencia ++){
        int tamano = 1000*pow(10,potencia)*sizeof(char);
        //Se aparta memoria de la informacion a enviar
        char * buffer = malloc(tamano);
        int r = write(descriptorTuberia,buffer,tamano);
        if (r < 0){
            perror("Hubo un error enviando los datos");
            exit(-1);
        }
        printf("Tamano mensaje enviado %d",r);
    }
    close(descriptorTuberia);
    unlink(tuberia);
    return 0;
}