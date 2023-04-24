/*
Implemente un programa que obtenga e imprima informacion sobre usuarios del sistema
(todos los campos de la estructura passwd) e informacion sobre grupos del sistema (GID y
nombre del grupo mediante la estructura group), segun las opciones recibidas por la linea de
argumentos.

La opcion -u/--user se utilizara para indicar un usuario. Si le pasamos como argu-
mento un n  ́umero, lo interpretara como UID, en caso contrario como el nombre del
usuario. Se mostrara la informacion correspondiente a su estructura passwd.

La opcion -g/--group se utilizara para indicar un grupo. Si le pasamos como argu-
mento un numero, lo interpretara como GID, en caso contrario como el nombre del
grupo. Se mostrara la informacion correspondiente a su estructura group.

La opcion -a/--active sera equivalente a especificar--user con el usuario actual.

La opcion -m/--maingroup modifica a --user o --active y hace que imprima la
informacion de su grupo principal (mismo formato que --group).

Si se invoca al programa con la opcion -s o con --allgroups, se mostraran todos
los grupos del sistema, junto con su identificador. Para ello recorra el fichero corres-
pondiente (le permitira recordar como gestionar y buscar en cadenas) y luego vaya
extrayendo informacion como si se invocase la opcion --group. No muestre directamente 
el contenido del fichero, recorralo y muestre la informacion por cada grupo que haya.

Invocar al programa sin ninguna opcion sera equivalente a activar las opciones --active
y --maingroup, es decir, se mostrara la informacion del usuario actual (con el mismo
formato que que -u/--user) y del grupo al que pertenece (con el mismo formato que
que -g/--group).

Se creara una opcion de ayuda -h/--help para mostrar informacion sobre cada uno
de los usos del programa. Esa informaci  ́on tambi ́en se mostrara cuando el usuario
cometa cualquier error en la invocaci  ́on del programa.

Tenga tambien en cuenta el siguiente control de errores:
-Asegurar que se pasan nombres e identificadores de usuarios o grupos validos que
 existan en la maquina.
-Asegurar que no se puedan pasar por linea de comandos opciones que sean incompa-
 tibles. Las unicas combinaciones posibles son:
  • --help, junto con cualquiera (se ignoran las demas)
  • vacio (equivalente a --active --maingroup)
  • --user <uid o nombre de usuario>
  • --user <uid o nombre de usuario> --maingroup
  • --active
  • --active --maingroup
  • --group <gid o nombre de grupo>
  • --allgroups
*/

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


//Funcion que recibe un valor de tipo struct passwd la cual muestra la informacion del usuario
void Usuario(struct passwd *pw) {
    printf("Usuario:\n");
    printf("Nombre: %s\n", (pw->pw_gecos)); // No es lo mismo el nombre de usuario asociado a un login que el propio login, strtok para eliminar las comas
    printf("Login: %s\n", pw->pw_name);//para mostrar el login
    printf("Password: %s\n", pw->pw_passwd);//para mostrar la contraseña
    printf("UID: %d\n", pw->pw_uid);//para mostrar el uid
    printf("Home: %s\n", pw->pw_dir);//para mostrar la direccion del home
    printf("Shell: %s\n", pw->pw_shell);//para mostrar la shell
    printf("Número de grupo principal: %d\n", pw->pw_gid); //para mostrar el gid
}

//Funcion que recibe un valor de tipo struct group la cual muestra la informacion del grupo
void Grupo(struct group *gr) {
    printf("Grupo:\n");
    printf("Nombre del grupo: %s\n", gr->gr_name);//gr no lleva puntero por que no tiene nada mas que un valor
    printf("GID: %d\n",gr->gr_gid);
    printf("Miembros secundarios: %s\n", *gr->gr_mem);//gr* lleva puntero por que puede ser mas de un valor
    
}

//Imprime las principales opciones del programa
void Opciones() { 
    printf("Uso del programa: ./ej1.c [opciones]:\n");
    printf("-h, --help Imprimir esta ayuda.\n");
    printf("-u, --user (<nombre>|<uid>) Información sobre el usuario.\n");
    printf("-a, --active Información sobre el usuario activo actual.\n");
    printf("-m, --maingroup Además de info de usuario, imprimir la info de su grupo,\n → principal.\n");
    printf("-g, --group (<nombre>|<gid>) Información sobre el grupo.\n");
    printf("-s, --allgroups Muestra info de todos los grupos del sistema.\n");   
}      


int main(int argc, char **argv) {

    int gid; //variable que se utiliza para almacenar el gid
    int c; //variable que se utiliza para ver que flags se han activado
    int uid; //variable que se utiliza para almacenar el uid
    char *nombre; //variable que se utiliza para almacenar el nombre del usuario
    char *gname; //variable que se utiliza para almacenar el nombre del grupo
    struct passwd *pw; //variable que se utiliza para almacenar la informacion del usuario
    struct group *gr; //variable que se utiliza para almacenar la informacion del grupo

    /* Estructura a utilizar por getoptlong */
    static struct option long_options[] = {
        /* Opciones que no van a actuar sobre un flag */
        //{<nombre largo>, <recibe/no recibe argumento>, NULL, <nombre corto>}
        {"user", required_argument, NULL, 'u'},
        {"group", required_argument, NULL, 'g'},
        {"active", no_argument, NULL, 'a'},
        {"maingroup", no_argument, NULL, 'm'},
        {"allgroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        /* Necesario para indicar el final de las opciones */
        {0, 0, 0, 0} 
    };

    //Estas variables servirán para almacenar el resultado de procesar la línea de comandos 
    char *uvalue = NULL; //almacenamos el valor de u
    char *gvalue = NULL; //almacenamos el valor de g
    bool aflag = false; //almacenamos el valor de a
    bool mflag = false; //almacenamos el valor de m
    bool sflag = false; //almacenamos el valor de s
    bool hflag = false; //almacenamos el valor de h
    bool errorflag = false; //almacenamos el valor si se introduce una opcion no valida

    while((c = getopt_long(argc, argv, "u:g:amsh", long_options, NULL)) != -1) { //en el while se activan las flags
        //ponemos : para que se active la flag al tener un argumento
        switch(c) {
            case 'u':
                uvalue=optarg;
                break;
            
            case 'g':
                gvalue=optarg;
                break;
            
            case 'a':
                aflag=true;
                break;
            
            case 'm':
                mflag=true;
                break;
            
            case 's':
                sflag=true;
                break;
            
            case 'h':
                hflag=true;
                break;

            case '?':
                errorflag=true; //si se introduce una opcion no valida, se activa la flag linea 265


        }
    }
    
    //entramos a este if si se activa el valor de h, da igual las demas flags
    if(hflag == true) {
        Opciones(); 
        exit(0);
    }
      //entramos a este if si no se activa ningun valor
    if((uvalue == NULL)&&(gvalue == NULL)&&(hflag == false)&&(aflag == false)&&(mflag == false)&&(sflag == false)&&(errorflag == false)) {
        if((nombre=getenv("USER"))==NULL || (pw=getpwnam(nombre))==NULL) { //si no existe el login
            printf("Error al intentar acceder a la información de usuario.\n");
            exit(-1);
        } else {
            Usuario(pw); //si existe el login, imprimimos la info
        }
        if((gr=getgrgid(pw->pw_gid))==NULL) { //si no existe el gid
            printf("Error al intentar acceder a la información de grupo.\n");
            exit(-1);
        } else {
            Grupo(gr); //si existe el gid, imprimimos la info
            exit(0);
        }
    }
    
    //entramos a este if si se activa el valor de u
    if((uvalue != NULL)&&(gvalue == NULL)&&(hflag == false)&&(aflag == false)&&(sflag == false)) {
        if(isdigit(*uvalue)!=0) { //comprobamos que uvalue sea el uid y no el login
            uid=atoi(uvalue); //convertimos el uid a int
            if((pw=getpwuid(uid))==NULL) { //si no existe el uid
                printf("Error al intentar acceder a la información de usuario.\n");
                exit(-1);
            } else {
                Usuario(pw); //si existe el uid, imprimimos la info
            }
        } else { //si uvalue es el login
            nombre=uvalue;//guardamos el login en nombre
            if((pw=getpwnam(nombre))==NULL) { //si no existe el login
                printf("Error al intentar acceder a la información de usuario.\n");
                exit(-1);
            } else {
                Usuario(pw); //si existe el login, imprimimos la info
            }
        }
        if(mflag == true) { //si se activa el valor de m, imprimimos la info del grupo principal
            if((gr=getgrgid(pw->pw_gid))==NULL) { //si no existe el gid
                printf("Error al intentar acceder a la información de grupo.\n");
                exit(-1);
            } else {
                Grupo(gr); //si existe el gid, imprimimos la info
                exit(0);
            }
        }
        exit(0);
    }

    //entramos a este if si se activa el valor de a
    if((uvalue == NULL)&&(gvalue == NULL)&&(hflag == false)&&(aflag == true)&&(sflag == false)) {
        if((nombre=getenv("USER"))==NULL || (pw=getpwnam(nombre))==NULL) { //si no existe el login
            printf("Error al intentar acceder a la información de usuario.\n");
            exit(-1);
        } else {
            Usuario(pw); //si existe el login, imprimimos la info
        }
        if(mflag==true) { //si se activa el valor de m, imprimimos la info del grupo principal
            if((gr=getgrgid(pw->pw_gid))==NULL) { //si no existe el gid
                printf("Error al intentar acceder a la información de grupo.\n");
                exit(-1);
            } else {
                Grupo(gr); //si existe el gid, imprimimos la info
                exit(0);
            }
        }
        exit(0);
    }


    //entramos a este if si se activa el valor de s
    if((uvalue == NULL)&&(gvalue == NULL)&&(mflag == false)&&(hflag == false)&&(aflag == false)&&(sflag == true)) {
        FILE *f;
        f=fopen("/etc/group", "r"); //PUEDE VARIAR SEGUN EL SO
        if(f==NULL) {
            printf("Error al intentar acceder a la información de usuario.\n");
            exit(-1);
        }
        char buffer[256]; //buffer para almacenar la linea
        char *nombre;
        char *gid;
        char *miembros;
        printf("Grupo:\n\n");

        while(fgets(buffer, 256, f) != NULL) {
            nombre=strtok(buffer, ":"); //separamos el nombre del grupo
            strtok(NULL, ":"); //saltamos el password            
            gid=strtok(NULL, ":"); //separamos el gid
            miembros=strtok(NULL, ":"); //separamos los miembros
            printf("Nombre del grupo principal: %s\n", nombre);
            printf("GID: %s\n", gid);
            printf("Miembros secundarios: %s\n", miembros);
        }
        fclose(f);
        exit(0);
    }


  
        //entramos a este if si se activa el valor de g
    if((uvalue == NULL)&&(gvalue != NULL)&&(mflag == false)&&(hflag == false)&&(aflag == false)&&(sflag == false)) {
        if(isdigit(*gvalue)!=0) { //comprobamos que gvalue sea el gid y no el nombre del grupo
            gid=atoi(gvalue);
            if((gr=getgrgid(gid))==NULL) { //si no existe el gid
                printf("Error al intentar acceder a la información de grupo.\n");
                exit(-1);
            } else {
                Grupo(gr); //si existe el gid, imprimimos la info
                exit(0);
            }
        } else { //si gvalue es el nombre del grupo
            gname=gvalue;
            if((gr=getgrnam(gname))==NULL) { //si no existe el grupo
                printf("Error al intentar acceder a la información de usuario.\n");
                exit(-1);
            } else {
                Grupo(gr); //si existe el grupo, imprimimos la info
                exit(0);
            }
        }
    }
    Opciones();//para mostrar opciones
}
