#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <errno.h> 

int main(int argc, char **argv){

    int c; //Variable para el switch()
    //Estructura a utilizar por el getoptlong
    static struct option long_options[] = {
    //{<nombre_largo>, <recibe/no recibe argumentos>, NUUL, <nombre_corto>}
        {"userpsswd", required_argument, NULL, 'p'},
        {0, 0, 0, 0} //Poner siempre al final
 
    };

    char *pvalue = NULL;
    char *lgn;
    struct passwd *pw;

    if(argc < 2){

        if((lgn = getenv("USER")) == NULL || (pw = getpwnam(lgn)) == NULL){
            printf("EEROR, esto no funciona bien\n");
            exit(EXIT_FAILURE);
        }
    }

    while ((c = getopt_long(argc, argv, "p:", long_options, NULL)) != -1){ //Los ':' es para indicar que tiene argumentos
        /*printf("optind: %d, optarg: %s, optopt: %c\n", optind, optarg, optopt);
        El optarg: para guardar valores del argv, optind: para contar los argumentos*/

        switch (c){

            case 'p':
                //flag para llamar a la opcion user, acompañado de el ususario que queramos
                pvalue = optarg;
                break;

            case '?':
                //Error generico
                printf("ERROR, esta opcion no se encuentra dentro de las posibles\n");
                exit(EXIT_FAILURE);

            default:
                abort();
        }
    }

    if (optind < argc) {
        printf("Argumentos ARGV que no son opciones: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        putchar('\n');
        return 0;
    }
    if(pvalue){
        
        lgn = pvalue;
        //Para cuando introducimos el nombre del usuario
        if ((pw = getpwnam(lgn)) == NULL){

            printf("Fallo al obtener información de usuario.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Para realizar el fork
    pid_t rf;
    int flag, status;
    // Para controlar los valores devueltos por las funciones (control de errores)
    mqd_t mq_cola;
    char buffer[1024];
    char colaQueue[100];
    struct mq_attr attr;
    attr.mq_maxmsg = 10;        
    attr.mq_msgsize = 1024;

    //creacion de procesos Rf es el pid del proceso
    rf = fork();
    switch (rf) {
    case -1:
        printf("No se ha podido crear el proceso hijo...\n");
        exit(EXIT_FAILURE);
    case 0:
        printf("\n");
        printf("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());
        sprintf(colaQueue, "%s-%s", "/COLA", getenv("USER"));
        printf("[HIJO]: El nombre de la cola servidor es: %s\n", colaQueue);

        mq_cola = mq_open(colaQueue, O_CREAT | O_WRONLY, 0644, &attr);
        //CONTROL ERRORES
        if(mq_cola == (mqd_t)-1){
            perror("Error al abrir la cola \n");
            exit(EXIT_FAILURE);
        }
        printf("[HIJO]: El descriptor de la cola Servidor es: %d\n", (int)mq_cola);
        printf("[HIJO]: MANDANDOLE COSAS A MI PADRE...\n");

        sprintf(buffer, "Nombre: %s\nLogin: %s\nPassword: %s\nUID: %d\nHome: %s\nShell: %s\nNumero de grupo principal: %d\n",pw->pw_gecos, pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_dir, pw->pw_shell, pw->pw_gid);
        if(mq_send(mq_cola, buffer, 1024, 0) != 0){
            perror("Error al enviar el mensaje\n");
            exit(EXIT_FAILURE);
        }
        
        if(mq_close(mq_cola) == (mqd_t)-1){
            perror("Error al cerrar la cola\n");
            exit(EXIT_FAILURE);
        }

        if(mq_unlink(colaQueue) == (mqd_t)-1){
            perror("Error al eliminar la cola\n");
            exit(EXIT_FAILURE);
        }

        break;

    default:

        printf("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
        sprintf(colaQueue, "%s-%s", "/COLA", getenv("USER"));
        printf("[PADRE]: El nombre de la cola servidor es: %s\n", colaQueue);

        mq_cola = mq_open(colaQueue, O_CREAT | O_RDONLY, 0644, &attr);
        //CONTROL ERRORES
        if(mq_cola == (mqd_t)-1){
            perror("Error al abrir la cola \n");
            exit(EXIT_FAILURE);
        }
        printf("[PADRE]: El descriptor de la cola Servidor es: %d\n", (int)mq_cola);
        printf("[PADRE]: Recibiendo cosas de mi hijo...\n");
        
        ssize_t mensaje = mq_receive(mq_cola, buffer, 1024, NULL);
        if(mensaje < 0){
            perror("Error al recibir el mensaje\n");
            exit(EXIT_FAILURE);
        }
        printf("[PADRE]: RECIBIDO\n%s", buffer);
        
        if(mq_close(mq_cola) == (mqd_t)-1){
            perror("Error al cerrar la cola\n");
            exit(EXIT_FAILURE);
        }



        
//------------------------------------------------------------------------------------------------------------------
        /*Espera del padre a los hijos*/
        while ((flag = wait(&status)) > 0) {
            if (WIFEXITED(status)) {
                printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) { // Para seniales como las de finalizar o matar
                printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
            }
        }
        if (flag == (pid_t)-1 && errno == ECHILD) {
            printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
        } else {
            printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);    



}