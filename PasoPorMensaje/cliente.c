#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <math.h>

// Se define el puerto y el tamaño maximo de la cola de conecciones
#define PORT 3536
#define IP "127.0.0.1"

#define KILOB 1000

int main(){
    // Cantidad de veces que se enviara el mismo tamaño de datos
    int limite = 50;
    // Potencia de diez que tendran los datos
    for (int potencia = 0; potencia < 6 ; potencia ++){
        if (potencia == 5){
            limite = 10;
        }
        for (int i = 0 ; i < limite ; i ++){
            // Descriptor del socket cliente
            int clientefd, r,tamano;
            // EStructuras de configuracion de cliente
            struct sockaddr_in client;
            
            // Se crea el socket cliente
            clientefd = socket(AF_INET,SOCK_STREAM,0);
            if (clientefd < 0){
                perror("Error creando el socket\n");
                exit(-1);
            }
            // Se configura el cliente
            client.sin_family = AF_INET;
            client.sin_port = htons(PORT);
            inet_aton(IP,&client.sin_addr);
            // Espera a que el servidor este listo para poder conectarse
            do{
                r =connect(clientefd,(struct sockaddr *)&client,(socklen_t)sizeof(struct sockaddr));
            }while(r < 0);
            
            // Tamaño calcula el tamaño de los datos
            tamano = KILOB * pow(10, potencia) * sizeof(char);
            char * buffer = malloc(tamano);
            int cantidad = 0;
            // Se reciven todos los datos
            while (cantidad < tamano){
                r = recv (clientefd,buffer+cantidad,tamano,0);
                cantidad = cantidad + r;
            }
            if (r < 0){
                perror("Error en recv\n");
                exit(-1);
            }
            printf("Bytes leidos %d iteracion %d\n",cantidad,i);
            // Se envia la confirmacion de que se recibieron todos los datos
            if (tamano == cantidad)
                r = send(clientefd,"OK",2,0);
            else
                r = send(clientefd,"NO",2,0);
            if (r < 0 ){
                perror("Error en send");
                exit(-1);
            }
            // Se cierra el socket
            close(clientefd);
            // Se espera un tiempo para enviar nuevamente los datos
            int reloj = 0;
            while(reloj < 100000000){
                reloj++;
            }
        }
    }
}