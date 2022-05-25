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

#define PORT 3536
#define IP "127.0.0.1"

#define KILOB 1000

int main(){
    int limite = 50;
    for (int potencia = 0; potencia < 6 ; potencia ++){
        if (potencia == 5){
            limite = 10;
        }
        for (int i = 0 ; i < limite ; i ++){
            int clientefd, r,tamano;
            struct sockaddr_in client;
            struct hostent *he;
            
            clientefd = socket(AF_INET,SOCK_STREAM,0);
            if (clientefd < 0){
                perror("Error creando el socket\n");
                exit(-1);
            }
            client.sin_family = AF_INET;
            client.sin_port = htons(PORT);
            inet_aton(IP,&client.sin_addr);
            do{
                r =connect(clientefd,(struct sockaddr *)&client,(socklen_t)sizeof(struct sockaddr));
            }while(r < 0);
            
            // if (r < 0){
            //     perror("Error en connect\n");
            //     exit(-1);
            // }
            tamano = KILOB * pow(10, potencia) * sizeof(char);
            char * buffer = malloc(tamano);
            int cantidad = 0;
            while (cantidad < tamano){
                r = recv (clientefd,buffer+cantidad,tamano,0);
                cantidad = cantidad + r;
                printf("Hola mundo %d\n",r);
            }
            if (r < 0){
                perror("Error en recv\n");
                exit(-1);
            }
            printf("Bytes leidos %d iteracion %d\n",cantidad,i);
            if (tamano == cantidad)
                r = send(clientefd,"OK",2,0);
            else
                r = send(clientefd,"NO",2,0);
            if (r < 0 ){
                perror("Error en send");
                exit(-1);
            }
            close(clientefd);
            int reloj = 0;
            while(reloj < 100000000){
                reloj++;
            }
        }
    }
}