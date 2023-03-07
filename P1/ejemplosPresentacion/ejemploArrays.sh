#!/bin/bash

read -p "¿Cuántos valores quieres introducir? " numVal

for (( i=1; $i<=$numVal; i=$i+1 ))
do
	read -p "Introduce el valor que quieras en la pos $i: " array[$i]
done

echo "La longitud del array \"${array[*]}\" es ${#array[@]}."
