/*
Cliente que envia por una cola abierta para escritura una cadena de caracteres
recogida por teclado, mientras que el valor de esa cadena sea distinto a la palabra exit
*/

#include "ej3_common.h"
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

// Prototipo de funcion
void funcionLog(char *);
// Apuntador al fichero de log.
FILE *fLog = NULL;

int main(int argc, char **argv) {
    
    mqd_t mq_server; // Cola del servidor
    mqd_t mq_client; // Cola del cliente

    // Buffers para intercambiar mensajes
    char readbuffer[MAX_SIZE];
    char writebuffer[MAX_SIZE];

    // Nombre para las colas
    char serverQueue[100];
    char clientQueue[100];

    // Nombre para la cola del servidor. Al concatenar el login sera unica en un sistema compartido.
    sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    printf("[Cliente]: El nombre de la cola del servidor es: %s\n", serverQueue);

    // Abrir la cola del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen.
    // No es necesario crearla si se lanza primero el servidor, sino el programa no funciona.
    mq_server = mq_open(serverQueue, O_WRONLY);

    // mq_server = mq_open(SERVER_QUEUE, O_WRONLY);
    if (mq_server == (mqd_t)-1) {
        perror("Error al abrir la cola del servidor");
        exit(-1);
    }
    printf("[Cliente]: El descriptor de la cola del servidor es: %d\n", (int)mq_server);

    // Nombre para la cola del cliente
    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Cliente]: El nombre de la cola del cliente es: %s\n", clientQueue);

    // Abrir la cola del cliente
    mq_client = mq_open(clientQueue, O_WRONLY);

    // mq_server = mq_open(SERVER_QUEUE, O_WRONLY);
    if (mq_client == (mqd_t)-1) {
        perror("Error al abrir la cola del servidor");
        exit(-1);
    }
    printf("[Cliente]: El descriptor de la cola del cliente es: %d\n", (int)mq_client);

    // Bucle de envío de mensajes
    printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
    do {
        printf("> ");

        ssize_t bytes_read;

        /* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
        It stops when either (n-1) characters are read, the newline character is read,
        or the end-of-file is reached, whichever comes first.
        Automáticamente fgets inserta el fin de cadena '\0'
        */
        fgets(writebuffer, MAX_SIZE, stdin);

        // Enviar y comprobar si el mensaje se manda
        if (mq_send(mq_server, writebuffer, MAX_SIZE, 0) != 0) {
            perror("Error al enviar el mensaje");
            exit(-1);
        }

        // Recibir y comprobar si el mensaje se recibe
        bytes_read=mq_receive(mq_client, readbuffer, MAX_SIZE, NULL);

        if (bytes_read < 0) {
            perror("Error al recibir el mensaje");
            exit(-1);
        }

        printf("Recibido: %s\n", readbuffer);

        // Iterar hasta escribir el código de salida
    } while(strcmp(writebuffer, MSG_STOP));
    

    // Cerrar la cola del servidor
    if (mq_close(mq_server) == (mqd_t)-1) {
        perror("Error al cerrar la cola del servidor");
        exit(-1);
    }

    // Cerrar la cola del cliente
    if (mq_close(mq_client) == (mqd_t)-1) {
        perror("Error al cerrar la cola del cliente");
        exit(-1);
    }
    return 0;
}

/* Función auxiliar, escritura de un log.
No se usa en este ejemplo, pero le puede servir para algun
ejercicio resumen */
void funcionLog(char *mensaje) {
    int resultado;
    char nombreFichero[100];
    char mensajeAEscribir[300];
    time_t t;

    // Abrir el fichero
    sprintf(nombreFichero, "log-cliente.txt");
    if (fLog == NULL) {
        fLog = fopen(nombreFichero, "at");
        if (fLog == NULL) {
            perror("Error abriendo el fichero de log");
            exit(1);
        }
    }

    // Obtener la hora actual
    t = time(NULL);
    struct tm *p = localtime(&t);
    strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

    // Vamos a incluir la hora y el mensaje que nos pasan
    sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);

    // Escribir finalmente en el fichero
    resultado = fputs(mensajeAEscribir, fLog);
    if (resultado < 0)
        perror("Error escribiendo en el fichero de log");

    fclose(fLog);
    fLog = NULL;
}
