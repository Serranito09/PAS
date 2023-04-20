//Compilacion con -lrt
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <errno.h>
#include "ej3_common.h"

void funcionLog(char *); //prototipo de la función
FILE *fLog = NULL;

int main(int argc, char **argv){
	mqd_t mq_server;
	char buffer[MAX_SIZE]; //Buffer que se encarga de intercambiar mensajes
    char serverQueue[100]; //Nombre de la cola

	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER")); 
    printf ("[Cliente]: El nombre de la cola es: %s\n", serverQueue); //Se le da el nombre para la cola.

    mq_server = mq_open(serverQueue, O_WRONLY);
	if(mq_server == (mqd_t)-1){ //Se comprueba que la cola se abre correctamente
      perror("Error al abrir la cola del servidor");
      exit(-1);
	}
    printf ("[Cliente]: El descriptor de la cola es: %d\n", (int) mq_server); //Define el descriptor de la cola
	printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP); //Se envia mensajes al servidor
	while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))){
		printf("> "); //Lectura por teclado, al final del documenta se incluye '\0'
		fgets(buffer, MAX_SIZE, stdin);

		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0){ //Se comprueba el mensaje a enviar
			perror("Error al enviar el mensaje");
			exit(-1);
		}
	}

	if(mq_close(mq_server) == (mqd_t)-1) //Se cierra la cola del servidor y se comprueba que se ha realizado correctamente
	{
		perror("Error al cerrar la cola del servidor");
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

	sprintf(nombreFichero,"log-cliente.txt"); //Apertura del fichero log-cliente.txt
	if(fLog==NULL){ //Se comprueba que el fichero se abre correctamente, y sino se genera un error
		fLog = fopen(nombreFichero,"at");
		if(fLog==NULL){
			perror("Error abriendo el fichero de log");
			exit(1);
		}
	}

	t = time(NULL); //Se obtiene la hora actual
	struct tm * p = localtime(&t);
	strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

	sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje); //Y se incluye la hora y el mensaje que ha sido recibido

	resultado = fputs(mensajeAEscribir,fLog); //Se escribirá en el fichero
	if (resultado < 0){ //Y se comprueba que se ha incluido en el fichero
		perror("Error escribiendo en el fichero de log");
    }
	fclose(fLog);
	fLog=NULL;
}