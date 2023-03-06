#!/bin/bash
#./ejer4.sh ejemplo

#Listar fichero de un drectorio sin mostrar subdirectorios, nombre fichero sin ruta y numero de 
#caracteres de cada fichero


cont=0

if [ $# -eq 1 ]; #Comprobamos los argumentos
then
	if [ -d $1 ]; # $1 se refiere al primer argumento de la linea
	then	
	echo "Formato correcto. "	
	
	for x in $(find $1) 
	do
		if [ -f $x ]; #Si x es un fichero normal
		then
			let cont=cont+1 #Sumamos 1 al contador
	        	nombre_sin_ruta=$(basename $x) #basename devuelve el nombre del fichero sin la ruta donde se encuentra
	        	echo -n "$cont    $nombre_sin_ruta      " #Se imprime sin salto de linea	
			#printf "%10s            %10s" $cont $nombre_sin_ruta

	        	caracteres=$(echo -n $nombre_sin_ruta | wc -m ) #wc -m nos cuenta el numero de caracteres del nombre del fichero	
	        	if [ $caracteres -eq 1 ] #comparacion singular o plural
	        	then
	        		#echo "$caracteres caracter"
				printf "%10s %10s \n" $caracteres "caracter" 
	        	else
	            		#echo "$caracteres caracteres"
				printf "%10s %10s \n" $caracteres "caracteres" 
	        	fi
	        fi   
    	done
	fi
else
   echo "Formato incorrecto. Tiene que insertar algo como: ./ejer4.sh nombre_directorio  "
   exit 1
fi 



