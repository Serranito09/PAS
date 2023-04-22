#include "ej3_common.h"
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

FILE *fLog = NULL;

void funcionLog(char *mensaje) {
    int resultado;
    char nombreFichero[100];
    char mensajeAEscribir[300];
    char fecha[100];
    time_t t;

    // Abrir el fichero
    sprintf(nombreFichero, "log-servidor.txt");
    if(fLog == NULL){
        fLog = fopen(nombreFichero, "at");
        if(fLog == NULL){
            perror("Error abriendo el fichero de log");
            exit(1);
        }
    }

    // Obtener la hora actual
    t = time(NULL);
    struct tm *p = localtime(&t);
    strftime(fecha, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

    // Vamos a incluir la hora y el mensaje que nos pasan
    sprintf(mensajeAEscribir, "%s ==> %s\n", fecha, mensaje);

    // Escribir finalmente en el fichero
    resultado = fputs(mensajeAEscribir, fLog);
    if(resultado < 0){
        perror("Error escribiendo en el fichero de log");
    }
    fclose(fLog);
    fLog = NULL;
}

int main(int argc, char **argv) {
    //Descriptores de las colas
    mqd_t mq_server;
    mqd_t mq_client;

    // Atributos de la cola
    struct mq_attr attr;

    // Buffer para intercambiar mensajes
    char ReadBuffer[MAX_SIZE];
    char WriteBuffer[MAX_SIZE];

    // flag que indica cuando hay que parar. Se escribe palabra exit
    int must_stop = 0;

    // Inicializar los atributos de la cola
    attr.mq_maxmsg = 10;        // Máximo número de mensajes
    attr.mq_msgsize = MAX_SIZE; // Máximo tamaño de un mensaje

    // Nombre para la cola
    char serverQueue[100];
    char clientQueue[100];

    // Nombre para la cola. Al concatenar el login sera unica en un sistema compartido.
    sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    printf("[Servidor]: El nombre de la cola del servidor es: %s\n", serverQueue);

    // Crear la cola de mensajes del servidor
    mq_server = mq_open(serverQueue, O_CREAT | O_RDONLY, 0644, &attr);

    if (mq_server == (mqd_t)-1){
        perror("Error al abrir la cola del servidor");
        funcionLog("Error al abrir la cola del servidor");
        exit(-1);
    }
    printf("[Servidor]: El descriptor de la cola del servidor es: %d\n\n", (int)mq_server);

    // Crear la cola de mensajes del cliente
    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Servidor]: El nombre de la cola del cliente es: %s\n", clientQueue);

    mq_client = mq_open(clientQueue, O_CREAT | O_WRONLY, 0644, &attr);

    if (mq_client == (mqd_t)-1){
        perror("Error al abrir la cola del cliente");
        funcionLog("Error al abrir la cola del cliente");
        exit(-1);
    }
    printf("[Servidor]: El descriptor de la cola del cliente es: %d\n\n", (int)mq_client);

    do{
        // Número de bytes leidos
        ssize_t bytes_read;

        // Recibir el mensaje
        bytes_read = mq_receive(mq_server, ReadBuffer, MAX_SIZE, NULL);

        // Comprobar que la recepción es correcta (bytes leidos no son negativos)
        if (bytes_read < 0) {
            perror("Error al recibir el mensaje");
            funcionLog("Error al recibir el mensaje");
            exit(-1);
        }
    if (mq_send(mq_client, WriteBuffer, MAX_SIZE, 0) != 0) {
            perror("Error al enviar el mensaje");
            funcionLog("Error al enviar el mensaje");
            exit(-1);
        }
        // Comprobar el fin del bucle
        if(strncmp(ReadBuffer, MSG_STOP, strlen(MSG_STOP)) == 0){
            must_stop = 1;
        }
        
        printf("Recibido el mensaje: %s", ReadBuffer);
        sprintf(WriteBuffer,"Número de caracteres leídos: %ld",(strlen(ReadBuffer)-1));
        funcionLog(WriteBuffer);
        
    } while (!must_stop); // Iterar hasta que llegue el código de salida, es decir, la palabra exit
    funcionLog("exit");

    // Cerrar la cola del servidor y del cliente
    if(mq_close(mq_server) == (mqd_t)-1) {
        perror("Error al cerrar la cola del servidor");
        funcionLog("Error al cerrar la cola del servidor");
        exit(-1);
    }
    if(mq_close(mq_client) == (mqd_t)-1) {
        perror("Error al cerrar la cola del cliente");
        funcionLog("Error al cerrar la cola del cliente");
        exit(-1);
    }

    // Eliminar la cola del servidor y del cliente
    if(mq_unlink(serverQueue) == (mqd_t)-1) {
        perror("Error al eliminar la cola del servidor");
        funcionLog("Error al eliminar la cola del servidor");
        exit(-1);
    }
    if(mq_unlink(clientQueue) == (mqd_t)-1) {
        perror("Error al eliminar la cola del cliente");
        funcionLog("Error al eliminar la cola del cliente");
        exit(-1);
    }

    return 0;
}