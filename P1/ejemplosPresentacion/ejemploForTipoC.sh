#!/bin/bash

read -p "Introduzca un número" num

sum=$[0]

for (( i=1; $i<=$num; i=$i+1 ))
do
	let "sum=$sum + $i"
done

echo "La suma de los primeros $num es: $sum"
