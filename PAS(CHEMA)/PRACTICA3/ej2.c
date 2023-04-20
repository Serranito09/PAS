#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> //Gestion de errores
#include <string.h> //Empleada en strerror(), para definir el valor de errno.
#include <time.h>
#include <sys/wait.h>

int main(){
    pid_t rf; // Permite realizar el fork
	int flag, status; 
	int resultado; //Permite gestionar errores
	float numeroAle1;
	float numeroAle2;
	float sumaAle;
	int fildes[2]; //Extremos de la tubería

	resultado=pipe(fildes); //Creacion de la tuberia
	if(status==-1){
		printf("\nERROR en la creacion.\n");
		exit(1);
	}

    rf=fork();
	switch (rf){             
		
        case -1:
			printf ("No se ha podido crear el proceso hijo...\n"); //Error en la creacion del proceso hijo
			exit(EXIT_FAILURE);
        break;

		case 0:
			printf ("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid()); //Informacion acerca del hijo
			close(fildes[1]);
            resultado = read( fildes[0], &sumaAle, sizeof(int));//Recibimos mensaje
            if(resultado != sizeof(int)){ //Se comprueba mensaje
				printf("\n[HIJO]: ERROR al leer de la tubería...\n");
				exit(EXIT_FAILURE);
			}
            printf("[HIJO]: El resultado de la suma leido de la tubería es: %f.\n", sumaAle); //Imprimimos el valor enviado		
			printf("[HIJO]: Tubería cerrada ...\n"); //Cerramos la tuberia
			close(fildes[0]);
			break;

		default:
			printf ("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf); //Informacion acerca del padre
			close(fildes[0]);
			srand(time(NULL)); //Generacion de los numeros aleatorios
            numeroAle1=rand()%5000;
			numeroAle2=rand()%5000;
            printf("[PADRE]: Escribo el resultado de la suma de los números aleatorios %f y %f en la tubería...\n", numeroAle1, numeroAle2); //Se escribe en la tuberia
			sumaAle=numeroAle1+numeroAle2;
			resultado = write( fildes[1], &sumaAle, sizeof(int)); //Se envía el mensaje
			if(resultado != sizeof(int)){ //Comprobacion del mensaje
				printf("\n[PADRE]: ERROR al escribir en la tubería...\n");
				exit(EXIT_FAILURE);
			}
			close(fildes[1]); // Se cierra el extremo usado
			printf("[PADRE]: Tubería cerrada...\n");

	        while ( (flag=wait(&status))>0){//El padre pasa a esperar al hijo
		        if (WIFEXITED(status)){
			        printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
		        } 
		        else if (WIFSIGNALED(status)){
			        printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
		        } 		
	        }
	        if (flag==(pid_t)-1 && errno==ECHILD) {
		        printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
	        }
	        else{
		        printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
		        exit(EXIT_FAILURE);
	        }			 
	}
	exit(EXIT_SUCCESS);
}