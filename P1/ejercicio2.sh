#Desarrolla un script que permita configurar los permisos de los ficheros y subdirectorios de
#una determinada carpeta de la siguiente forma:
#El directorio y todos los subdirectorios deberan tener todos los permisos para el usuario,
#lectura y ejecucion para el grupo y ninguno para otros.
#Los archivos cuya extension sea .sh deberan recibir permisos de ejecucion para el usuario.
#Los ficheros con extension .key deberan asegurarse, restringiendo los permisos de manera
#que solo el usuario propietario pueda acceder a ellos.
#Ademas, al finalizar debe mostrar una lista ordenada alfabeticamente de los usuarios que
#hay logeados en el sistema en el instante en el que se ejecuta el script, eliminando los usuarios
#repetidos (Consulta los comandos who y uniq).


# notas: los permisos se escriben de la manera: -rwxrwxrwx
#        - indica que es un archivo. si es d significa directorio
#        u: el primer rwx son los permisos del dueño del archivo
#        g: el segundo rwx son los permisos del grupo
#        o: el tercer rwx son los permisos del resto de usuarios

#! /bin/bash #inicio

if [ $# -ne 1 ]  #control de argumentos. controla que el numero de argumentos que se pasa es el correcto
then
    echo "Argumentos incorrectos. Uso: bash ejercicio2.sh <ruta_directorio>"
    exit
fi

if [ ! -d $1 ]; #control de argumentos. controla que el directorio existe
then 
    echo "El directorio introducido no existe"
    exit
fi
echo "cambiando permisos de directorios"

for i in $(find  $1) #esto nos sirve para buscar todo lo que haya dentro del directorio que nos pasan por lineas de argumentos

do
    if [ -d $i ] #Comporbamos si es un directorio lo que se ha encontrado
        then
        chmod u+rwx $i #Al usuario le añadimos permisos de escritura,lectura y ejecucion
        chmod g+rx-w $i #Al grupo le añadamios permisos de lectura y ejecuccion,y le hemos quitado escritura
        chmod o-rwx $i #A otros usuarios le hemos quitado todos los permisos   fi
done

echo "Añadiendo permisos de ejecuccion a scripts"

for i in $(find -name "*.sh") #buscamos los archivos .sh
do
    chmod u+rwx $i #Al usuario le añadimos permisos de escritura,lectura y ejeccucion
done

echo "Restringiendo permisos de ficheros de claves"

for i in $(find -name "*.key") #buscamos los archivos .key
do
    chmod u+rwx $i #Al usuario le añadimos permisos de escritura,lectura y ejeccucion
    chmod g-rwx $i #Al grupo no le concedemos ningun permiso
    chmod o-rwx $i #A otros no le concedemos ningun permiso
done

#comandos utilizados:
#find para buscar todo el contenido de un directorio --> for i in $(find $directorio)
#find para buscar archivos de un tipo determinado --> for i in $(find -name "*.key")
# -d nos sirve para ver si existe un directorio --> if[ -d $nombredirectorio ]
# -e nos sirve para ver si existe un fichero --> if[ -e $fichero ]
# -ne significa not equal --> if [ -ne $variable ]
#chmod para cambiar los permisos -->chmod u+rwx nombreArchivo o directorio
#exit para salir del script