#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int main(){
    //Descriptor del archivo
    int t;
    //Ruta del archivo tuberia
    char *tuberia = "./tuberia"; 

    char * buffer = malloc(sizeof(char)*1000*pow(10,1));

    //Se abre la tuberia
    t = open(tuberia,O_RDONLY);
    if (t < 0){
        perror("Hubo un error abriendo el archivo de la tuberia");
        exit(-1);
    }

    //Se lee el mensaje de la tuberia
    int r = read(t,buffer,sizeof(buffer));
    if (r < 0){
        perror("Hubo un error leyendo el archivo de la tuberia");
        exit(-1);
    }
    
    close(t);
    return 0;
}