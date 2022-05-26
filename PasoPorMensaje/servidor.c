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

// Se define el puerto y el tamaño maximo de la cola de conecciones
#define PORT 3536
#define BACKLOG 5

#define KILOB 1000
int main(){
    // Cantidad de veces que se enviara el mismo tamaño de datos
    int limite = 50;
    // Potencia de diez que tendran los datos
    for (int potencia = 0 ; potencia < 6 ; potencia ++){

        double tiempoTotal = 0;
        int tamanoBuff;
        if (potencia == 5){
            limite = 10;
        }
        for (int i = 0 ; i < limite ; i++){
            int cantidad = 0;

            // Se guarda la hora inicial
            clock_t inicio = clock();

            // Descriptor del socket servidor y cliente,parametro de setsockopt
            int serverfd, clientfd, r ,opt = 1;
            // EStructuras de configuracion de servidor y cliente
            struct sockaddr_in server,client;
            // Tamaño de una estructura sockaddr_in
            socklen_t tamano = sizeof(client);

            // Se crea el socket servidor
            serverfd = socket(AF_INET,SOCK_STREAM,0);
            if (serverfd < 0){
                perror("Error en socket");
                exit(-1);
            }
            // Se configura el servidor
            server.sin_family = AF_INET;
            server.sin_port = htons(PORT);
            server.sin_addr.s_addr = INADDR_ANY;
            bzero(server.sin_zero,8);

            // Reutiliza los recursos abiertos en ejecuciones pasadas
            setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(int));

            // Se configura el servidor
            r = bind(serverfd,(struct sockaddr *)&server,sizeof(struct sockaddr));
            if (r < 0 ){
                perror("Error en bind");
                exit(-1);
            }
            // Se configura como servidor
            r = listen(serverfd,BACKLOG);
            if (r < 0 ){
                perror("Error en LISTEN");
                exit(-1);
            }
            //Acepta a un cliente y lo guarda en la estructura cliente
            clientfd = accept(serverfd, (struct sockaddr *)&client, &tamano);
            if (clientfd < 0){
                perror("Error en el accept");
                exit(-1);
            }

            // Tamaño calcula el tamaño de los datos
            tamanoBuff = KILOB * pow(10, potencia) * sizeof(char);
            char * buffer = malloc(tamanoBuff);
            // Se envian todos los datos
            while (cantidad < tamanoBuff){
                r = send(clientfd,buffer+cantidad,tamanoBuff,0);
                cantidad = cantidad+r;
            }
            if (r < 0 ){
                perror("Error en send");
                exit(-1);
            }
            // printf("Cantidad de bytes enviados %d i %d\n",r,i);

            // Se recibe la confirmacion de que se enviaron todos los datos
            char confirmacion [3];
            r = recv(clientfd,confirmacion,2,0);
            confirmacion[3] = 0;
            // printf("Confirmacion: %s\n",confirmacion);
            
            // Se cierra ambos sockets
            close(clientfd);
            close(serverfd);

            // Se guarda la hora final y se calcula el tiempo empleado en segundos
            clock_t fin = clock();
            double tiempo = (double)(fin-inicio)/CLOCKS_PER_SEC;
            tiempoTotal = tiempoTotal+tiempo;
            // printf("Tiempo empleado: %f i %d\n",tiempo,i);
            
            // Se espera un tiempo para enviar nuevamente los datos
            int reloj = 0;
            while(reloj < 100000000){
                reloj++;
            }
        }
        tiempoTotal = tiempoTotal/limite;
        printf("El tiempo promedio enviando %d datos y recibiendo una confirmacion es de %f\n",tamanoBuff,tiempoTotal);
    }
}