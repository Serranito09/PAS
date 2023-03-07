#!/bin/bash

read -p "Introduzca un número (1 <= x < 10): " num

if [ $num -ge 1 ];
then
	if [ $num -lt 10 ];
	then
		echo "El número $num es correcto!"
	else
		echo "El número queda fuera de rango."
	fi
else
	echo "El número queda fuera de rango."
fi
