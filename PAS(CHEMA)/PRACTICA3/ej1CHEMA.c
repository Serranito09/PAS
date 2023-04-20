#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/types.h>

void printUsuario(struct passwd *pw){ //Imprime los principales datos del usuario.
    printf("Usuario:\n");
    printf("Nombre: %s\n", strtok(pw->pw_gecos, ",")); //Elimina las comas sobrantes
    printf("Login: %s\n", pw->pw_name);
    printf("Password: %s\n", pw->pw_passwd);
    printf("UID: %d\n", pw->pw_uid);
    printf("Home: %s\n", pw->pw_dir);
    printf("Shell: %s\n", pw->pw_shell);
    printf("Número de grupo principal: %d\n", pw->pw_gid);
}

void printGrupo(struct group *gr){ //Imprime los principales datos del grupo.
    printf("Grupo:\n");
    printf("Nombre del grupo: %s\n", gr->gr_name); //Nombre del grupo  
    printf("GID: %d\n", gr->gr_gid); //GID
    printf("Miembros secundarios: %s\n", *gr->gr_mem); //Miembros secundarios si los tiene
}

void printOpciones(){ //Imprime las principales opciones del programa
    printf("Uso del programa: ./ej1.c [opciones]:\n");
    printf("-h, --help Imprimir esta ayuda.\n");
    printf("-u, --user (<nombre>|<uid>) Información sobre el usuario.\n");
    printf("-a, --active Información sobre el usuario activo actual.\n");
    printf("-m, --maingroup Además de info de usuario, imprimir la info de su grupo,\n → principal.\n");
    printf("-g, --group (<nombre>|<gid>) Información sobre el grupo.\n");
    printf("-s, --allgroups Muestra info de todos los grupos del sistema.\n");   
}

int main(int argc, char **argv){

        
    if(argc==0){
        printf("Error en la estructura de la ejecución, ten en cuenta lo siguiente: \n\n");
        printOpciones();
        exit(0);
    }

    int option;
    opterr = 0;
    char *lgn;
    int uid;
    char *gname;
    int gid;
    char *name;
    struct passwd *pw;
    struct group *gr;
    //Estos elementos anteriores se encargarán de almacenar la información que iremos obteniendo

    //Estructura a utilizar por linea de comandos y configuracion de ejemplo: ej1.c -h
    static struct option long_options[] = {
        {"user", required_argument, NULL, 'u'},
        {"group", required_argument, NULL, 'g'},
        {"active", no_argument, NULL, 'a'},
        {"maingroup", no_argument, NULL, 'm'},
        {"allgroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
	};

    //Permiten almacenar la informacion obtenida por el terminal
    char *uvalue = NULL; //Inicializamos los char a NULL para no dar error
    char *gvalue = NULL;
    bool aflag = false; //Inicializamos los booleanos a false para no dar error
    bool mflag = false;
    bool sflag = false;
    bool hflag = false;

    while((option= getopt_long(argc, argv, "u:g:amsh", long_options, NULL))!=-1){
        switch (option) {
            //Se adapta cada una de las opciones para obtener un cierto valor
            case 'u': //Para el uso de user
                uvalue = optarg;
            break;
        
            case 'g': //Para el uso de group
                gvalue = optarg;
                break;

            case 'a': //Para el uso de active
                aflag = true;
            break;

            case 'm': //Para el uso de maingroup
                mflag = true;
            break;

            case 's': //Para el uso de allgroup
                sflag = true;
            break;

            case 'h': //Para el uso de help
                hflag = true;
            break;
        }
    }

    if(argc==1){
        if( (pw = getpwnam(lgn)) == NULL ||(lgn = getenv("USER")) == NULL){
            printf("Error al intentar acceder a la información de usuario.\n");
            exit(-1);
        }
        if ((gr = getgrgid(pw->pw_gid)) == NULL){
            printf("Error al obtener información de grupo.\n");
            exit(-1);
        }
        printUsuario(pw);
        printGrupo(gr);
        exit(0);
    }

    else{
        if (hflag){ //Si se selecciona help
            printOpciones(); 
            exit (0);
        }

        else if((uvalue != NULL)&&(gvalue == NULL)&&(!mflag)&&(!aflag)&&(!hflag)&&(!sflag)){ //Uso de -u
            if(isdigit(*uvalue)){ //Se comprueba que es un digito el user.
                uid = atoi(uvalue);
                if ((pw=getpwuid(uid))==NULL){
                    printf("Error al intentar acceder a la información de usuario.\n");
                    exit(-1);
                }
            }
            else{
                lgn=uvalue; //Comprobacion del login 
                if ((pw = getpwnam(lgn)) == NULL){
                    printf("Error al intentar acceder a la información de usuario.\n");
                    exit(-1);
                }
            } 
            printUsuario(pw); //Imprime usuario si es todo correcto
            exit (0);
        }
        
        else if((uvalue != NULL)&&(gvalue == NULL)&&(mflag)&&(!aflag)&&(!hflag)&&(!sflag)){ //Uso de -m
            if (isdigit(*uvalue)){//Comprobacion del user
                uid = atoi(uvalue);
                if ((pw = getpwuid(uid)) == NULL){ //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                    printf("Error al intentar acceder a la información de usuario.\n");
                    exit(-1);
                }
            }
            else{
                lgn = uvalue; //Comprobacion del login
                if ((pw = getpwnam(lgn)) == NULL){
                    printf("Error al intentar acceder a la información de usuario.\n");
                    exit(-1);
                }
            }
            printUsuario(pw); //Imprime usuario si esta todo correcto
            
            if ((gr = getgrgid(pw->pw_gid))==NULL){ //Comprobacion del grupo
                printf("Error al intentar acceder a la información de grupo.\n");
                exit(-1);
            }
            printGrupo(gr);
            exit(0);
        }

        else if((uvalue == NULL) && (gvalue == NULL)&&(!sflag)&&(aflag)&&(!mflag)&&(!hflag)){ //Uso de -a
            if((lgn = getenv("USER"))==NULL||(pw = getpwnam(lgn))==NULL){//Comprobacion del login y del usuario actual
                printf("Error al intentar acceder a la información de usuario.\n");
                exit(-1);
            }
            printUsuario(pw);//Se imprime el usuario si esta todo correcto
            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue == NULL)&&(mflag)&&(aflag)&&(!hflag)&&(!sflag)){ //Uso de -a -m
            if ((lgn = getenv("USER"))==NULL||(pw = getpwnam(lgn))==NULL){ //Comprobacion del login y del usuario actual
                printf("Error al intentar acceder a la información de usuario.\n");
                exit(-1);
            }
            printUsuario(pw); //Se imprime usuario si esta todo correcto
            if ((gr = getgrgid(pw->pw_gid)) == NULL) {
                printf("Error al intentar acceder a la información del grupo.\n");
                exit(-1);
            }
            printGrupo(gr); //Se imprime grupo si esta todo correcto
            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue!=NULL)&&(!sflag)&&(!mflag)&&(!aflag)&&(!hflag)){ //Uso de -g
            if (isdigit(*gvalue)){//Se comprueba el valor que se ha pasado
                gid = atoi(gvalue);
                if ((gr=getgrgid(gid))==NULL){
                    printf("Error al intentar acceder a la información de usuario.\n");
                    exit(-1);
                }
            }
            else{
                gname = gvalue; //Se comprueba el valor que se ha pasado
                if ((gr = getgrnam(gname)) == NULL){
                    printf("Error al intentar acceder a la información de usuario.\n");
                    exit(-1);
                }
            }
            printGrupo(gr); //Se imprime grupo si esta todo correcto
            exit(0);
        }
        
        else if((uvalue == NULL)&&(gvalue == NULL)&& (!hflag) && (!mflag) && (sflag) && (!aflag)){
            FILE *f;
            f = fopen("/etc/group","r"); //Este variara del SO
            if(f == NULL){ //Se comprueba que el fichero se puede abrir
               printf("Error al abrir el fichero localizado en /etc/group");   
               exit(-1);             
            }
            //Se generar elementos para almacenar los valores del grupo
            char buffer[256];
            char *gruponombre;
            char *password;
            char *pidgrupo;
            char *miembrosgrupo;
            printf("Grupo:\n\n");

            while (fgets(buffer, 256, f) != NULL){ //Uso de -s
                //Obtenemos la informacion del grupo y se va almacenando en las variable al ritmo que se imprime hasta finalizar el bucle
                gruponombre = strtok(buffer,":");
                password = strtok(NULL,":");
                pidgrupo = strtok(NULL,":");
                strtok(NULL,":");
                miembrosgrupo = strtok(NULL,":");
                //Se imprimen todos todos los grupos
                printf("Nombre del grupo principal: %s\n", gruponombre);
                printf("GID: %s\n", pidgrupo);
                printf("Miembros secundarios: %s\n", miembrosgrupo);
            }
            exit(0);
        }

        else{
            printf("Uso del programa: ./ej1.c [opciones]:\n");
            printf("-h, --help Imprimir esta ayuda.\n");
            printf("-u, --user (<nombre>|<uid>) Información sobre el usuario.\n");
            printf("-a, --active Información sobre el usuario activo actual.\n");
            printf("-m, --maingroup Además de info de usuario, imprimir la info de su grupo,\n → principal.\n");
            printf("-g, --group (<nombre>|<gid>) Información sobre el grupo.\n");
            printf("-s, --allgroups Muestra info de todos los grupos del sistema.\n");  
            exit (-1);            
        }   
    }
    exit(0);
}