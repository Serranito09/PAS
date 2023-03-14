#Desarrolla un script que permita realizar una copia de seguridad de un determinado directorio
#y almacenarla en un fichero comprimido. El programa debera recibir dos argumentos:
#1. Directorio que se va a copiar.
#2. Directorio donde se almacenara la copia comprimida.
#El nombre del fichero de copia resultante debera seguir el formato:
#nombredirectoriooriginal usuario fecha.tar.gz, donde usuario, es el nombre del usuario que esta
#realizando la copia y fecha es la fecha en segundos desde el 1 de enero de 1970.
#Por ejemplo, si el usuario i72jivem hace una copia del directorio carpetadeejemplo el dia
#20 de febrero de 2022, el fichero resultante se llamara carpetadeejemplo i72jivem 1676910
#481.tar.gz. Para comprimir el fichero, deberas utilizar la herramienta tar. Consulta los argu-
#mentos necesarios para comprimir un directorio.
#Si el directorio de destino de la copia no existe, deberas crearlo.
#Al invocar al script, todos los ficheros de la carpeta donde se guarden 
#los tar con una antiguedad mayor a 200 segundos, deberan ser borrados Ademas, deberas realizar los controles de
#errores que estimes oportunos.

#!/bin/bash  #inicio



if [ $# -ne 2 ] #control de argumentos
then
    echo "Argumentos incorrectos. Uso: ./ejercicio3.sh <directorio_origen> <directorio_destino>"
    exit
fi

if [ ! -e $1 ] #controlamos que exista el directorio que queremos comprimir
then
    echo "No existe el directorio a comprimir"
    exit
fi

if [ ! -d $2 ] #controlamos si existe el directorio de destino
then
    echo "No existe el directorio de destino, se crea"
    mkdir $2
fi

nombre=$1_$USER'_'$(date +%s) #creamos el nombre del tar. poner entre comillas
tar -cvf  $nombre.tar.gz $1 #creamos el tar
mv $nombre.tar.gz ./$2 #movemos el tar al directorio de destino

num=200

for i in $(find $2) #buscamos cada archivo en el directorio de destino
do
    fechademodificacion=$(date -r $i +%s) #fecha de modificacion del archivo
    fechaactual=$(date +%s) #fecha actual
    res=$[$fechaactual-$fechademodificacion] 

    if [ ! -d $i ] #comprobamos que no sea un directorio, es decir, que sea un archivo
    then
        echo $i #mostramos el archivo
        echo "mostrando $res" #mostramos el tiempo desde que se modifico el archivo
        if [ $res -gt $num ] #si han pasado mas de 200 segundos desde la modificacion del archivo. -gt es greater than (mayor que)
        then
            rm -r $i #para borrar el archivo
            echo borrado
        fi
    fi
done

# comandos utilizados
# para comprimir un archivo --> tar -czvf nombre-directorio.tar.gz nombre-directorio 
# para mover un archivo --> mv $archivo ./$directorio_destino
# para borrar un archivo --> rm -r $nombre-archivo o nombre-direcotorio 
# -gt significa greater than - mayor que
# -lt signica less than - menor que
# para mostrar la fecha de modificacion de un archivo --> $(date -r $i +%s)
# para mostrar la fecha actual --> $(date +%s)
# para crear un directorio --->mkdir nombre-directorio
# para poner un simbolo en un nombre se pone entre comillas simples (' ') --> nombre=$1_$USER'_'$(date +%s)