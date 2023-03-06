#Desarrollar un script que permita generar un directorio con ficheros y subdirectorios de ejemplo 
#que podras utilizar en futuros ejercicios de esta practica. El script recibira 4 argumentos:
#1. Ruta del nuevo directorio que se va a crear.
#2. Numero de subdirectorios que se crearan dentro del directorio principal.
#3. Longitud mınima de los nombres de los ficheros (sin extensi  ́on) y subdirectorios.
#4. Longitud maxima de los nombres de los ficheros (sin extensi  ́on) y subdirectorios.
#Al ejecutarlo, deber ́a crear un directorio principal en la ruta que se haya especificado en el primer
#parametro. Dentro de ese directorio, se deber ́an crear N subdirectorios (indicado por el segundo
#parametro) con nombres aleatorios y de longitud aleatoria entre el m ́ınimo y el m ́aximo especificados 
#como argumentos. Por  ́ultimo, dentro de cada uno de estos subdirectorios, se crearan 4
#ficheros (vac ıos) con nombres aleatorios y las extensiones .sh, .html, .key y .txt.
#Por ejemplo, si el n  ́umero de subdirectorios es 2 y la longitud del nombre debe estar entre 4 y 6


#! /bin/bash
if [ $# -ne 4 ]; #control de argumentos si es distinto de 4 el script se cierra. -ne significa not equal
then             # $# es el numero de argumentos que pasamos por la terminal
echo "Debe introducir estos 4 argumentos"
echo "Ruta del nuevo directorio que se va a crear."
echo "Numero de subdirectorios que se crearan dentro del directorio principal."
echo "Longitud minima de los nombres de los ficheros (sin extension) y subdirectorios"
echo "Longitud maxima de los nombres de los ficheros (sin extension) y subdirectorios."
exit  

fi

if [ -d $1 ]; #controlamos si existe el directorio, -d nos sirve para ver si existe un directorio
then
    echo "Este directorio ya existe"
    echo "Desea borrarlo s/n"
    read -t5 respuesta #si en 5 segundos no se responde no se borra, -tX controla el tiempo que debe pasar para responder, X=segundos
    if [ $respuesta == "s" ]
    then 
        rm -r $1   #rm -r para eliminar un directorio, en este caso se elimina el directo que se ha pasado por el primer argumento
        echo "El directorio se ha eliminado"
        mkdir $1 #mkdir para crear un directorio
    fi
    
fi
for i in $(seq $2) #$(seq $n) es como poner for(i=0; i<n; i++)
do
longitud=$((RANDOM%($4-$3+1)+$3)) #volcamos en la variable longitud un numero ramdom que este comprendido entre el 4 argumento y el 3 (longitud maxima y minima)
nombre=$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $longitud) #generamos un nombre aleatorio con una longitud concreta 
mkdir $1/$nombre #creamos un directorio en la ruta 
touch $1/$nombre/$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $((RANDOM%($4-$3+1)+$3))).sh #creamos ficheros con nombres y longitud random ademas de añadirle al final una extension
touch $1/$nombre/$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $((RANDOM%($4-$3+1)+$3))).key
touch $1/$nombre/$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $((RANDOM%($4-$3+1)+$3))).html
touch $1/$nombre/$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $((RANDOM%($4-$3+1)+$3))).txt 
done

#comandos utilizados:  
# touch nos sirve para crear ficheros --> touch nombreFichero
# mkdir para crear un directorio --> mkdir nombreDirectorio
# -d nos sirve para ver si existe un directorio --> if[ -d $nombredirectorio ]
# -ne significa not equal --> if [ -ne $variable ]
# para salir del script--> exit
# -tX controla el tiempo que debe pasar para responder, X=segundos
# rm -r para eliminar un directorio --> rm -r $directorio