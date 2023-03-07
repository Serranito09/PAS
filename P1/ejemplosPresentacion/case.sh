#!/bin/bash

read -p "Introduce un número (1 <= x < 10): " num

case $num in
	1) echo "Se ha introducido el valor 1. Es correcto.";;
	2) echo "Se ha introducido el valor 2. Es correcto.";;
	3 | 4 | 5 | 6 | 7 | 8 | 9) echo "Es correcto.";;
	0) echo "Es incorrecto. Es a partir de 1.";;
	10) echo "Es incorrecto. Es menor que 10.";;
	*) echo "Atiende a las opciones.";;
esac
