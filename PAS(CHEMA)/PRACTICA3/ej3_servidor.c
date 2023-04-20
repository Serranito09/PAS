//Compilacion con -lrt
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include "ej3_common.h"

void funcionLog(char *); //prototipo de la función
FILE *fLog = NULL;

int main(int argc, char **argv){
	mqd_t mq_server; //Cola del servidor
	struct mq_attr attr; //Posibles atributos de cola
	char buffer[MAX_SIZE]; //Buffer que se encarga de intercambiar mensajes
	int must_stop = 0; //Flag utilizado para parar cunado se escribe exit
	attr.mq_maxmsg = 10; //Valor para indicar el número máximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; //Valor para indicar el tamaño máximo del mensajes
    char serverQueue[100]; //Nombre que la cola va recibir

	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    printf ("[Servidor]: El nombre de la cola es: %s\n", serverQueue); //Se le da el nombre para la cola.

	mq_server = mq_open(serverQueue, O_CREAT | O_RDONLY, 0644, &attr); //Se crea la cola de mensajes del servidor

	if(mq_server == (mqd_t)-1){//Se comprueba que la cola se ha abierto correctamente
   	    perror("Error al abrir la cola del servidor");
        exit(-1);
	}
    printf ("[Servidor]: El descriptor de la cola es: %d\n", (int) mq_server); //Se define el descriptor de la cola

	while (!must_stop){ //Finalizara al alcanzar la palabra exit 
		ssize_t bytes_read; //Valor del número de bytes leidos
		bytes_read = mq_receive(mq_server, buffer, MAX_SIZE, NULL); //Recepcion del mensaje
		if(bytes_read < 0){ //Comprobacion de la recepcion del mensaje viendo que los bytes leidos no son menores que 0
			perror("Error al recibir el mensaje");
			exit(-1);
		}
		if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0){ //Se comprobará el fin del while
			must_stop = 1;
        }
		else{ //Recepcion del mensaje correcto
			printf("Recibido el mensaje: %s\n", buffer);
        }
	} 

	if(mq_close(mq_server) == (mqd_t)-1){ //Se cerrará la cola del servidor y se comprobará que se ha realizado correctamente
		perror("Error al cerrar la cola del servidor");
		exit(-1);
	}

	if(mq_unlink(serverQueue) == (mqd_t)-1){ //Se elimina la cola del servidor y se comprueba que se ha relizado correctamente
		perror("Error al eliminar la cola del servidor");
		exit(-1);
	}

	return 0;
}

//Función auxiliar, escritura de un log.
void funcionLog(char *mensaje){
	int resultado;
	char nombreFichero[100];
	char mensajeAEscribir[300];
	time_t t;

	sprintf(nombreFichero,"log-servidor.txt"); //Apertura del fichero log-servidor.txt
	if(fLog==NULL){ //Se comprueba que el fichero se abre correctamente, y sino se genera un error 
		fLog = fopen(nombreFichero,"at");
		if(fLog==NULL){
			perror("Error abriendo el fichero de log");
			exit(1);
		}
	}

	t = time(NULL);//Se obtiene la hora actual
	struct tm * p = localtime(&t);
	strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

    sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);//Y se incluye la hora y el mensaje que ha sido recibido

    resultado = fputs(mensajeAEscribir,fLog); //Se escribirá en el fichero
	if (resultado < 0){ //Y se comprueba que se ha incluido en el fichero
		perror("Error escribiendo en el fichero de log");
    }
	fclose(fLog);
	fLog=NULL;
}