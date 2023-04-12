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

#include <getopt.h>
#include <stdbool.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {

    int c;
    char *lgn;
    struct passwd *pw;
    struct group *gr;

    /* Estructura a utilizar por getoptlong */
    static struct option long_options[] = {
        /* Opciones que no van a actuar sobre un flag */
        //  {<nombre largo>, <recibe/no recibe argumento>, NULL, <nombre corto>}
        {"user", required_argument, NULL, 'u'},
        {"group", no_argument, NULL, 'g'},
        {"active", required_argument, NULL, 'a'},
        {"maingroup", no_argument, NULL, 'm'},
        {"allgroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        /* Necesario para indicar el final de las opciones */
        {0, 0, 0, 0}
    };

    while ((c = getopt_long(argc, argv, "u:ga:msh", long_options, NULL)) != -1) {
        
        switch(c) {
            case 'u':
                lgn = argv[2];
                if((pw = getpwnam(lgn)) == NULL) {// DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(1);
                }
                printf("Usuario:\n");
                printf("Nombre: %s\n", pw->pw_gecos); // No es lo mismo el nombre de usuario asociado a un login que el propio login
                printf("Login: %s\n", pw->pw_name);
                printf("Password: %s\n", pw->pw_passwd);
                printf("UID: %d\n", pw->pw_uid);
                printf("Home: %s\n", pw->pw_dir);
                printf("Shell: %s\n", pw->pw_shell);
                printf("Número de grupo principal: %d\n", pw->pw_gid);
                break;
            
            case 'g':
                lgn = argv[2];
                if((pw = getpwnam(lgn)) == NULL) {// DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(1);
                }
                
                break;
            
            case 'a':
                break;
            
            case 'm':
            printf ("hola\n");
                break;
            
            case 's':
                break;
            
            case 'h':
                break;
            
            case '?':
                break;
            
            default:
                abort();

        }
    }


}