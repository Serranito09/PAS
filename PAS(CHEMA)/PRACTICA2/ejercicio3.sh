#!/bin/bash
#ejercicio3.sh

if [ $# -ne 1 ] #Se debe incluir un fichero de texto
then
	echo "Argumentos incorrectos. Inserte algo parecido a: 
./ejer3.sh <fichero_de_texto>"
	exit
fi

for i in $(cat ${1}|sed 's/\,//g'|sed 's/\.//g'|sed 's/\s\+/\n/g'|sed -e 's/\(.*\)/\L\1/') #Este comando permite obtener todas las palabras del documento
do
	echo "$i ${#i}"
done| sort -k1,2 -k2,2nr|uniq|column -t -s " "|nl #Coloca el valor numerico y lo ordena por orden alfabetico ademas de contar cuantas letras lo conforman
#ln permite el alineamiento a la izquierda y rn a la derecha
#-k2,2 lo ordena por cantidad de letras 
#-k2,1 lo ordena por cantidad de letras a la inversa
#-k1,1 orden alfabetico

