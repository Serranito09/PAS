#!/bin/bash
# stat fichero muestra las propiedades sobre un fichero determinado


entorno=$(pwd)

function crearUsuario(){
	nombreUsuario=$1
	if [ -d "$homes"/"$nombreUsuario" ]
	then
		echo "El usuario ya existe."
		exit
	fi
	echo -e "$nombreUsuario" >> users.txt
	mkdir "$homes"/"$nombreUsuario"
	cp $entorno/skel/* $entorno/"$homes"/$nombreUsuario/
}

if [ ! -d $entorno/homes ]
then
	echo "Creando directorio homes...."
	mkdir homes
	echo "Hecho."
fi

if [ ! -d $entorno/skel ]
then
	echo "Creando directorio skel...."
	mkdir skel
	echo "Hecho."
fi
#Se tienen que crear unos cuantos .txt dentro de skel

if [ $# -ne 1 ]
then
	echo "Argumentos mal metidos. Inserte algo parecido a: 
./ejer6.sh <nombreUsuario>"
	exit 
fi
homes=homes

if [ ! -f users.txt ]
then 
	touch users.txt
fi
crearUsuario ${1}
echo "Usuario ${1} creado correctamente."
