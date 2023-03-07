#!/bin/bash

read -p "Introduzca su nombre de usuario: " nombre

if [ $nombre == 'Isa' ];
then
	echo "Bienvenida $nombre"
else
	echo "Eso es mentira!"
fi


