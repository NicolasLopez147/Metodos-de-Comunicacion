#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <math.h>
#include <time.h>

#define PORT 3536
#define BACKLOG 5
int main(){
    int limite = 50;
    for (int potencia = 0 ; potencia < 6 ; potencia ++){
        double tiempoTotal = 0;
        int tamanoBuff;
        if (potencia == 5){
            limite = 10;
        }
        for (int i = 0 ; i < limite ; i++){
            clock_t inicio = clock();
            int serverfd, clientfd, r ,opt = 1;
            struct sockaddr_in server,client;
            socklen_t tamano = sizeof(client);

            serverfd = socket(AF_INET,SOCK_STREAM,0);
            if (serverfd < 0){
                perror("Error en socket");
                exit(-1);
            }
            server.sin_family = AF_INET;
            server.sin_port = htons(PORT);
            server.sin_addr.s_addr = INADDR_ANY;
            bzero(server.sin_zero,8);

            setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(int));

            r = bind(serverfd,(struct sockaddr *)&server,sizeof(struct sockaddr));
            if (r < 0 ){
                perror("Error en bind");
                exit(-1);
            }
            r = listen(serverfd,BACKLOG);
            if (r < 0 ){
                perror("Error en LISTEN");
                exit(-1);
            }
            clientfd = accept(serverfd, (struct sockaddr *)&client, &tamano);
            if (clientfd < 0){
                perror("Error en el accept");
                exit(-1);
            }
            tamanoBuff = 1000 * pow(10, potencia) * sizeof(char);
            char * buffer = malloc(tamanoBuff);
            r = send(clientfd,buffer,tamanoBuff,0);
            if (r < 0 ){
                perror("Error en send");
                exit(-1);
            }
            // printf("Cantidad de bytes enviados %d i %d\n",r,i);
            char confirmacion [3];
            r = recv(clientfd,confirmacion,2,0);
            confirmacion[3] = 0;
            // printf("Confirmacion: %s\n",confirmacion);
            
            close(clientfd);
            close(serverfd);
            clock_t fin = clock();
            double tiempo = (double)(fin-inicio)/CLOCKS_PER_SEC;
            tiempoTotal = tiempoTotal+tiempo;
            // printf("Tiempo empleado: %f i %d\n",tiempo,i);
            int reloj = 0;
            while(reloj < 100000000){
                reloj++;
            }
        }
        tiempoTotal = tiempoTotal/limite;
        printf("El tiempo promedio enviando %d datos y recibiendo una confirmacion es de %f\n",tamanoBuff,tiempoTotal);
    }
}