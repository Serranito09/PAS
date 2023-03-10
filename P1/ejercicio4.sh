#Desarrolla un script que permita listar todos los ficheros de un directorio con una extension
#concreta sin mostrar los subdirectorios pero incluyendo los ficheros que estos puedan contener.
#El script recibira dos argumentos: el directorio y la extension. El nombre del fichero debera
#mostrarse sin su ruta, solo incluyendo el nombre. Ademas, se debera anadir un numero que
#indicara el orden de cada fichero y tambien otro numero que indicara el numero de caracteres
#del mismo asi como el numero de veces que aparece un determinado caracter que se le solicita al
#usuario. Si el usuario no indica el caracter en 5 segundos, utiliza la letra "a".

#!/bin/bash
i=0

if [ $# -ne 2 ] #control de argumentos
then
    echo "Argumentos incorrectos. Uso: ./ejercicio4.sh <ruta_directorio><extension_fichero>"
    exit
fi

echo Que caracter quieres contar? #preguntamos por el caracter que queremos contar
read -n1 -t5 letra #n1 sirve para leer la variable letra, -n1 solo permite la entrada de un caracter

if [ -z $letra ] #controlamos que la variable no este vacia. -z comprueba que la longitud sea igual a cero
then
    letra=a
fi

ficheros=$(find $1 -name "*.$2" ) #buscamos en el directorio introducido-->$1,-maxdepth nos sirve para indicar la profundidad
echo -e "\n"FICHEROS:"\n"         #en la que queremos buscar con una extension en concreto que se indica por linea de argumentos


for fichero in $ficheros #recorremos la variable fichero para mostrar su informacion
do
    fichero=$(basename $fichero)
    caracteres=$(echo -n $fichero | wc -m) #contar el numero de caracteres
    num_veces=$(echo $fichero | grep -o $letra | wc -l) #contar el numero de veces que aparece el caracter introducido en cada nombre de fichero
    
    echo -e  '  ' $i '\t ' $fichero ' \t' $caracteres '\t' $num_veces #imprimir por pantalla

    num_veces=0 #reiniciar la variable global
    i=$[$i+1] #i++
done

# comandos utilizados
# -ne indica si es igual o no 
# read -n1 variable nos limita la entrada por consola a un caracter
# find var nos sirve para buscar algo en concreto
# maxdepth numero nos sirve para indicar a la profundida a la que queremos mostrar
# -type f -> le dice al find que solo imprima ficheros, no directorios o subdirectorios
# printf "%f\n" sabemos que sirve para separar los ficheros mostrados pero no sabemos como
# para contar el numero de caracteres de uno o varios ficheros -> wc -m
# para contar el numero de lineas de uno o varios ficheros -> wc -l
# para poder poner '\n' y otras expresiones tipicas de c -> -e
# para imprimir sin salto de linea -> -n -> lo usamos para no contar el salto de linea como un caracter
# grep -o $letra ->nos sirve para buscar los emparajemientos que coincidan con esa letra
# para sumar un numero a una variable se debe poner la operacion dentro de un $[] -> i=$[$i+1]