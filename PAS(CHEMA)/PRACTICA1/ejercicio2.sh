#!/bin/bash
#ejercicio2.sh

if [ -d ${1} ] #El primer elemento debe existir y ser un directorio
then
	echo "El elemento introducido es correcto"
else
	echo "No existe ${1}" #Si no es directorio o no existe sale del programa
	exit
fi

if [ $# -ne 1 ] #Comprueba que se han pasado dos elementos por linea de comandos
then
		echo "Uso: ./ejercicio3.sh <directorio>"
		exit
fi

for file in $(ls ${1})
do
	echo "$file"
done

echo "Cambiando permisos de directorios..."
for file in $(ls ${1}) 
do
	if [ -d $file ]
	then
	echo "$file"
	chmod u+rw "$file"
	chmod g+rw "$file"
	chmod o-rwx "$file"
	fi
done

echo "Añadiendo permisos de ejecución a scripts..."
for file in $(ls ${1})
do
	if [ -e $file "*.sh" ]
	then
	echo "$file"
	chmod u+x "$file"
	fi
done

echo "Restringiendo permisos de ficheros de claves..."
for file in $(ls ${1})
do
	if [ $file *.key ]
	then
	echo "$file"
	chmod u+rw $file
	chmod g-rwx $file
	chmod o-rwx $file
	fi
done
