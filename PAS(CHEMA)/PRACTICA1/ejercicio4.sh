#!/bin/bash
#./ejer4.sh ejemplo
cont=0

if [ $# -eq 1 ]; # $#numero de argumentos en linea de comandos, $n comando nº n, $* todos los argumentos de la linea, $! pid del ultimo proceso, $? ver ultima exit
#Para comparar cadenas se utiliza ==, !=, -n s (>0)m -z s(=0)
#-lt (menor que), -gt (mayor que) -le(menor o igual), -ge(mayor o igual), -eq (igual), -ne (distinto)
then
	if [ -d $1 ]; # $1 se refiere al primer argumento de la linea
	#-e existe fichero?, -s tiene tamaño 0?, -f es fichero normal?, -d es directorio?, -l enlace simbolico?, -r permiso de lectura?, -w permiso de escritura?, -x permiso de ejecucion?
	then	
	echo "Formato correcto. "	
	for x in $(find $1) 
	#find carpeta -name "patron" busca fichero que cumplan patron guardados en la carpeta, find carp -size N cuyo tamaño sea N (+N o -N), find carp -user usuario, busca ficheros cuyo nombre usuario propietario sea usuario. 
	do
		if [ -f $x ];
		then
			let cont=cont+1
			#permite realizar operaciones aritmeticas $[expresion] o $((expresion))
	        	nombre_sin_ruta=$(basename $x) #basename devuelve el nombre del fichero sin la ruta donde se encuentra
	        	echo -n "$cont    $nombre_sin_ruta      "	
			#printf "%10s            %10s" $cont $nombre_sin_ruta
	        	caracteres=$(echo -n $nombre_sin_ruta | wc -m ) #wc muestra el numero de lineas, palabras o caracteres de uno o varios ficheros
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



