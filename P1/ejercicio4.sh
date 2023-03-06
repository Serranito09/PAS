#Desarrolla un script que permita listar todos los ficheros de un directorio con una extension
#concreta sin mostrar los subdirectorios pero incluyendo los ficheros que estos puedan contener.
#El script recibira dos argumentos: el directorio y la extension. El nombre del fichero debera
#mostrarse sin su ruta, solo incluyendo el nombre. Ademas, se debera anadir un numero que
#indicara el orden de cada fichero y tambien otro numero que indicara el numero de caracteres
#del mismo asi como el numero de veces que aparece un determinado caracter que se le solicita al
#usuario. Si el usuario no indica el caracter en 5 segundos, utiliza la letra "a".
#A continuacion se muestra un ejemplo de ejecucion
#!/bin/bash

if [ $# -ne 2 ] #control de argumentos
then
    echo "Argumentos incorrectos. Uso: ./ejercicio4.sh <ruta_directorio><extension_fichero>"
    exit
fi

for i in $(find $1)
do
    for j in $(find -name "*.sh")
    do
        ls
    done
done