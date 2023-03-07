#!/bin/bash

function check() {
	if [ -e $1 ]
	then
		return 0
	else
		return 1
	fi
}

read -p "Introduce el nombre de un fichero: " fichero

if check $fichero
then 
	echo "El fichero $fichero existe."
else
	echo "El fichero $fichero no existe."
fi
