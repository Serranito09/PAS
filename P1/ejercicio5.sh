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
fi
ficheros=$(find $1 -type f) #buscamos en el directorio introducido-->$1,-maxdepth nos sirve para indicar la profundidad
for x in $ficheros 
do
   tamano=$(stat -c "%s" $x)
   fecha=$(stat -c "%w" $x)
   permisos=$(stat -c "%A" $x)
   ejecucion=$(stat -c "%T" $x)
    if [ $tamano -gt $2 ]
    then
        echo $(basename $x)"; "$fecha"; "$tamano"; "$permisos"; "$ejecucion
    fi 
done