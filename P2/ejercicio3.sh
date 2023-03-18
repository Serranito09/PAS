#!/bin/bash
#Antes de todo crea un fcihero x.txt con algo escrito dentro para que lo lea y saque las palabras.

if [ $# -ne 1 ]
then
	echo "Argumentos incorrectos. Inserte algo parecido a: ./ejer3.sh <fichero_de_texto>"
	exit
fi

cd FicherosPract2

#imprimo el fcihero. Los 2 primeros sed borran los puntos, las comas y las barras. El ultimo sed se recorre todo lo pasa por \L para cambiar todo a minusculas y \1 es el primer argumento.
for i in $(cat $1|sed 's/\,//g'|sed 's/\.//g'|sed 's/\s\+/\n/g'|sed -e 's/\(.*\)/\L\1/')
# s/ -> modo sustitución  (p/ imprimir)
#\, -> cuando encuentre una coma
#/  -> lo sustituye por nada(borra)
#/g -> para todas las comas
do
	echo "$i ${#i}" #Se imprime la i y el tamaño de i
	
	
#k1 y k2 son las columnas, despues de las comas la prioridad. Después la N para numero y la R para reverse. El uniq hace que si dos palabras son iguales las elimina. Column lo que hace es seperarlo 
done| sort -k1,1 -k2,2nr|uniq|column -t -s " "|nl #nl enumera lineas
