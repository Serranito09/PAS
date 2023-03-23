#!/bin/bash
#Antes de todo crea un fcihero x.txt con algo escrito dentro para que lo lea y saque las palabras.

if [ $# -ne 1 ] #control de argumentos
then
	echo "Argumentos incorrectos. Inserte algo parecido a: ./ejer3.sh <fichero_de_texto>"
	exit
fi

cd FicherosPract2 #cambiamos a la carpeta donde se encuentran los ficheros necesarios para la practica

texto=$(sed -e 's/[.,]//g' $1 | sed 's/ /\n/g' | tr "[A-Z]" "[a-z]" | sort -u) #sustituimos los puntos y comas por nada, y los espacios por saltos de linea


for palabra in $texto #recorremos la variable texto y guardamos en palabra
do
    
    count=$(grep -oiw $palabra $1 | wc -l) #contamos el numero de veces que aparece la palabra buscada,para ello lo primero que hacemos es buscar la palabra en el texto,-oiw nos sirve para
	#-o para que nos muestre solo lo que coincide en vez de la linea completa,-i para que encuentre mayusculas o minusculas,-w para indicar que tiene que ser la a tal cual y que no enuentre
	#tambien las que se encuentre dentro de una cadena,y u na vez hecho mandamos eso mediante una tuberia a wc que cuenta el numero de lineas

    echo -e " $count $palabra" #mostramos la informacion del fichero

done | column -t |nl #nl sirve para numerar. 

# COMANDOS UTILIZADOS
# sort -u -> u significa unique
# tr -> para traducir
# nl -> para mostrar un contador
# column -t -> para mostrar la salida en columnas separadas por un espacio
# grep -w -> para que encuentre solo la palabra, no otras palabras que contengan esa cadena. ej: a a ac -> cuenta a 2 veces, no 3