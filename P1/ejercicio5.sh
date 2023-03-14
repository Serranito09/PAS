#Crear un script que reciba como argumento un parametro que sera un directorio y un segundo
#argumento que sera un numero (numero en bytes). El script debe buscar todos los ficheros que
#esten alojados en la carpeta que se pasa como primer argumento cuyo tamaño total en bytes
#sea mayor o igual que el numero pasado como segundo argumento. Para cada fichero debera
#mostrar:
#1. El nombre del fichero sin la ruta
#2. La fecha de creacion (legible)
#3. Tamaño en bytes
#4. La cadena de permisos del fichero
#5. Un 1 si el fichero es ejecutable y un 0 sino lo es

if [ $# -ne 2 ] #control de argumentos
then
    echo "Argumentos incorrectos. Uso: ./ejercicio5.sh <ruta_directorio> <tam_bytes>"
    exit
fi

ficheros=$(find $1 -type f) #buscamos los ficheros (-type f) en el directorio introducido-->$1
for fichero in $ficheros 
do
    tamano=$(stat -c "%s" $fichero) #stat te devuelve informacion sobre los ficheros. stat -c "%s" te devuelve solo el tamaño
    fecha=$(stat -c "%w" $fichero) #w para la fecha de creacion (legible)
    permisos=$(stat -c "%A" $fichero) #A para la cadena de permisos
    if [ -x $fichero ] #comprobamos si el fichero puede ejecutarlo el usuario
    then 
        ejecucion=1
    else
        ejecucion=0
    fi
    if [ $tamano -ge $2 ] #comprobamos si el fichero es mas grande que el tamaño pasado por argumento
    then
        echo "$(basename $fichero); $fecha; $tamano; $permisos; $ejecucion"
    fi
done | sort -nr -k3 -t ";" #con el sort -k3 ordenamos por la tercera columna, con -t ";" le decimos que las comillas se separan por ;

# OTRA FORMA DE HACERLO:
# done | column -t | sort -k5 -nr
# explicacion de la otra forma:
# utilizamos tuberias, primero para ordenarlo por columnas y
# con -t especificamos que deben de tener el mismo ancho y lo mandamos mediante a una tuberia para que 
# ordene de mayor a menor, con el -k indicamos la columna que queremos ordenar en este caso la 5 y  
# con el -rn de mayor a menor. si quitamos la r es de menor a mayor

# comandos utilizados
# stat -c "%caracter" -> para mostrar un campo determinado de un fichero. para ver que caracter poner -> man stat
# basename $directorio/fichero -> mostrar el nombre sin su ruta
# sort -knumero -t ";" -> para ordenar por una columna, -t ";" para decir como se separan las columnas
# -n -> ordenar numericamente

# PARA VER COMANDOS PARA COMPARAR FICHEROS, ETC: man test