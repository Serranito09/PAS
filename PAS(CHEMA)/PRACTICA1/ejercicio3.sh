#!/bin/bash
#chmod u+x nombre.sh

if [ -d ${1} ] #El primer elemento debe existir y ser un directorio
then
	echo "correcto"
else
	echo "No existe ${1}" #Si no es directorio o no existe sale del programa
	exit
fi

if [ $# -ne 2 ] #Comprueba que se han pasado dos elementos por linea de comandos
then
		echo "Uso: ./ejercicio3.sh <directorio_origen> <directorio_destino>"
		exit
fi

nombre=`date +"${1}_%Y%m%d"` #Se crea el nombre del .tar.gz
fechamodificacion=`date -r ${1} +"%Y%m%d"` #Fecha de modicicacion del primer directorio introducido
fechadehoy=`date +"%Y%m%d"` #Fecha de hoy para comparar con la fecha de la ultima modicacion

if [ $fechamodificacion -eq $fechadehoy ] #Se compara la fecha de la ultima modificacion con la de hoy y si coincide se produce un error
then
	echo "Ya se ha realizado una modiciacion hoy"
	exit
fi

if [ ! -e ${2} ] #Si el segundo elemento no existe, se crea dicho directorio con la direccion introducida
then 
	mkdir ${2}
fi

tar -cvf ${1}.tar.gz ${1} #Si no hay error se comprime
if [ -e ${1}.tar.gz ] #Si el elemento se ha creado correctamente se cambia el nombre por la variable nombre y se mueve al directorio indicado
then
	mv -i ${1}.tar.gz $nombre.tar.gz
	mv $nombre.tar.gz ${2}
	echo "Copia realizada en ${2}"
fi

