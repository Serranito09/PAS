/*
Servidor que lee de una cola abierta para lectura una cadena de caracteres y la
imprime por pantalla.

Lo hace mientras que el valor de esa cadena sea distinto a la palabra exit.
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

// Prototipo de funcion auxiliar
void funcionLog(char *);

// Apuntador al fichero de log. Se usa para que la funcion auxiliar pueda escribir en el fichero
FILE *fLog = NULL;

int main(int argc, char **argv) {

    mqd_t mq_server; // Cola del servidor
    mqd_t mq_client; // Cola del cliente

    struct mq_attr attr; // Atributos de la cola

    // Buffers para intercambiar mensajes
    char readbuffer[MAX_SIZE];
    char writebuffer[MAX_SIZE];

    int must_stop = 0; // flag que indica cuando hay que parar. Se escribe palabra exit
    
    // Inicializar los atributos de la cola
    attr.mq_maxmsg = 10;        // Maximo número de mensajes
    attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje
    
    // Nombre para la cola
    char serverQueue[100];
    char clientQueue[100];

    // Nombre para la cola del servidor. Al concatenar el login sera unica en un sistema compartido.
    sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    printf("[Servidor]: El nombre de la cola es: %s\n", serverQueue);

    // Crear la cola de mensajes del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen
    mq_server = mq_open(serverQueue, O_CREAT | O_RDONLY, 0644, &attr);
    /*0644 son permisos de lectura y escritura para el propietario
    y de sólo lectura para el grupo y para otros*/

    // mq_server = mq_open(SERVER_QUEUE, O_CREAT | O_RDONLY, 0644, &attr);

    if (mq_server == (mqd_t)-1) {
        perror("Error al abrir la cola del servidor");
        funcionLog("Error al abrir la cola del servidor");
        exit(-1);
    }

    printf("[Servidor]: El descriptor de la cola del servidor es: %d\n", (int)mq_server);

    //Nombre de la cola del cliente
    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Servidor]: El nombre de la cola del cliente es: %s\n", clientQueue);

    // Crear la cola de mensajes del cliente
    mq_client = mq_open(clientQueue, O_CREAT | O_WRONLY, 0644, &attr);

    if (mq_client == (mqd_t)-1){
        perror("Error al abrir la cola del cliente");
        funcionLog("Error al abrir la cola del cliente");
        exit(-1);
    }
    
    printf("[Servidor]: El descriptor de la cola del cliente es: %d\n\n", (int)mq_client);

    do {
        // Número de bytes leidos
        ssize_t bytes_read;

        // Recibir el mensaje
        bytes_read = mq_receive(mq_server, readbuffer, MAX_SIZE, NULL);

        // Comprobar que la recepción es correcta (bytes leidos no son negativos)
        if (bytes_read < 0) {
            perror("Error al recibir el mensaje");
            funcionLog("Error al recibir el mensaje");
            exit(-1);
        }
        
        // Cerrar la cadena
        // buffer[bytes_read] = '\0';

        // Comprobar el fin del bucle
        if (strncmp(readbuffer, MSG_STOP, strlen(MSG_STOP)) == 0)
            must_stop = 1;
        else
            printf("Recibido el mensaje: %s\n", readbuffer);
            //sprintf sirve para escribir en un buffer (fichero log)
            sprintf(writebuffer,"Número de caracteres leídos: %ld",(strlen(readbuffer)-1));
            funcionLog(writebuffer);
            
        if (mq_send(mq_client, writebuffer, MAX_SIZE, 0) != 0) {
            perror("Error al enviar el mensaje");
            funcionLog("Error al enviar el mensaje");
            exit(-1);
        }
    } while (!must_stop); // Iterar hasta que llegue el código de salida, es decir, la palabra exit
    funcionLog("exit");

    // Cerrar la cola del servidor
    if (mq_close(mq_server) == (mqd_t)-1) {
        perror("Error al cerrar la cola del servidor");
        funcionLog("Error al cerrar la cola del servidor");
        exit(-1);
    }
    // Cerrar la cola del cliente
    if(mq_close(mq_client)==(mqd_t)-1 ){
        perror("Error al cerrar la cola del cliente");
        funcionLog("Error al cerrar la cola del cliente");
        exit(-1);
    }

    // Eliminar la cola del servidor
    if (mq_unlink(serverQueue) == (mqd_t)-1) {
        perror("Error al eliminar la cola del servidor");
        funcionLog("Error al eliminar la cola del servidor");
        exit(-1);
    }
    // Cerrar la cola del cliente
    if(mq_unlink(clientQueue) == (mqd_t)-1) {
        perror("Error al eliminar la cola del cliente");
        funcionLog("Error al eliminar la cola del cliente");
        exit(-1);
    }

    return 0;
}

// Función auxiliar
void funcionLog(char *mensaje) {
    int resultado;
    char nombreFichero[100];
    char mensajeAEscribir[300];
    time_t t;

    // Abrir el fichero
    sprintf(nombreFichero, "log-servidor.txt");
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

