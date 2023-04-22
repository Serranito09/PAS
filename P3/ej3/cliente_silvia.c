#include "ej3_common.h"
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>

FILE *fLog = NULL;

void funcionLog(char *mensaje) {
    int resultado;
    char nombreFichero[100];
    char mensajeAEscribir[300];
    char fecha[100];
    time_t t;

    // Abrir el fichero
    sprintf(nombreFichero, "log-cliente.txt");
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

// Cola del servidor y del cliente
mqd_t mq_server;
mqd_t mq_client;

// Buffer para intercambiar mensajes
char ReadBuffer[MAX_SIZE];
char WriteBuffer[MAX_SIZE];
// Nombre para la cola
char serverQueue[100];
char clientQueue[100];

void manejadorSIGINT(int signal){
    printf(" Capturé la señal SIGINT, saliendo...");
    sprintf(WriteBuffer, "Capturada la señal con identificador: %d", signal);
	funcionLog(WriteBuffer);
	sprintf(WriteBuffer, "exit\n");

    if (mq_send(mq_server, WriteBuffer, MAX_SIZE, 0) != 0) {
        perror("Error al enviar el mensaje");
        funcionLog("Error al enviar el mensaje");
        exit(-1);
    }
    funcionLog(WriteBuffer);
    printf("\n");

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
    exit(0);
}

void manejadorSIGTERM(int signal){
    printf("Capturé la señal SIGTERM, saliendo...");
    sprintf(WriteBuffer, "Capturada la señal con identificador: %d", signal);
	funcionLog(WriteBuffer);
	sprintf(WriteBuffer, "exit\n");

    if (mq_send(mq_server, WriteBuffer, MAX_SIZE, 0) != 0) {
        perror("Error al enviar el mensaje");
        funcionLog("Error al enviar el mensaje");
        exit(-1);
    }
    funcionLog(WriteBuffer);
    printf("\n");

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
    exit(0);
}

int main(int argc, char **argv) {
    if(signal(SIGINT, manejadorSIGINT)==SIG_ERR){
        printf("No puedo asociar la señal SIGINT al manejador!\n");
        funcionLog("No puedo asociar la señal SIGINT al manejador!\n");
    }

    if(signal(SIGTERM, manejadorSIGTERM)==SIG_ERR){
        printf("No puedo asociar la señal SIGTERM al manejador!\n");
        funcionLog("No puedo asociar la señal SIGTERM al manejador!\n");
    }

    // Nombre para la cola. Al concatenar el login sera unica en un sistema compartido.
    sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    printf("[Cliente]: El nombre de la cola del servidor es: %s\n", serverQueue);
    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Cliente]: El nombre de la cola del cliente es: %s\n", clientQueue);

    mq_server = mq_open(serverQueue, O_WRONLY);
    mq_client = mq_open(clientQueue, O_RDONLY);

    if (mq_server == (mqd_t)-1) {
        perror("Error al abrir la cola del servidor");
        funcionLog("Error al abrir la cola del servidor");
        exit(-1);
    }
    printf("[Cliente]: El descriptor de la cola del servidor es: %d\n", (int)mq_server);

    if (mq_client == (mqd_t)-1){
        perror("Error al abrir la cola del cliente");
        funcionLog("Error al abrir la cola del cliente");
        exit(-1);
    }
    printf("[Cliente]: El descriptor de la cola del cliente es: %d\n", (int)mq_client);

    printf("\nMandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
   
    do {
        printf("→ ");

        /* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
        It stops when either (n-1) characters are read, the newline character is read,
        or the end-of-file is reached, whichever comes first.
        Automáticamente fgets inserta el fin de cadena '\0'
        */
        fgets(WriteBuffer, MAX_SIZE, stdin);

        // Enviar y comprobar si el mensaje se manda
        if (mq_send(mq_server, WriteBuffer, MAX_SIZE, 0) != 0) {
            perror("Error al enviar el mensaje");
            funcionLog("Error al enviar el mensaje");
            exit(-1);
        }
        funcionLog(strtok(WriteBuffer,"\n"));

        // Número de bytes leidos
        ssize_t bytes_read;

        // Recibir el mensaje
        bytes_read = mq_receive(mq_client, ReadBuffer, MAX_SIZE, NULL);

        // Comprobar que la recepción es correcta (bytes leidos no son negativos)
        if (bytes_read < 0) {
            perror("Error al recibir el mensaje");
            funcionLog("Error al recibir el mensaje");
            exit(-1);
        }
        printf("%s\n",ReadBuffer);
        //printf("%s\n",WriteBuffer);
    // Iterar hasta escribir el código de salida
    } while(strcmp(WriteBuffer, MSG_STOP));

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

    return 0;
}