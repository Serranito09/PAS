#!/bin/bash
# sort ficher ordena la entrada o un fichero por orden alfabetico, -r por orden inverso, -n numerico, -t c cambia el caracter separador al caracter c, -k 3 cambia la clave de ordenacion a la tercera columna -> EJEMPLO: echo -e "12\n31\n5" | sort -n


if [ $# -ne 3 ];
then
  echo "Debe introducir estos tres argumentos:"
  echo "1 ruta del nuevo directorio que se va a crear"
  echo "2 numero de subdirectorios que se crearan dentro del directorio principal"
  echo "3 longitud de los nombres de los ficheros y subdirectorios"
  exit 1
fi

if [ -d $1 ]; #En caso de que exista el escritorio
then
  echo "El directorio ya existe"
  echo "Desea borrarlo s/n"
  read respuesta2
  # read -s no hace echo de la entrada, read -nN solo acepta N caracteres, -p "mensaje" muestra el mensaje al pedir la informacion, read -tT acepta la entrada durante T segundos
  
  if [ $respuesta == "s" ]
  then #Si la respuesta es si, se elimina y se creará de nuevo
     rm -r $1
     echo "El directorio se ha eliminado"
     ./ejercicio1.sh $1 $2 $3
  fi
  exit 2
fi

mkdir $1 #Se crea el directorio
for (( i=1; $i<=$2; i=$i+1))
do
  nombre=$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $3)
  mkdir $1/$nombre
  touch $1/$nombre/$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $3).sh #head muestra las n primeras lineas de un fichero, tail es el caso inverso
  touch $1/$nombre/$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $3).html
  touch $1/$nombre/$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $3).key
  touch $1/$nombre/$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $3).txt
  #fichero que crea en su interior con nombres random -> comando numeros random -> $RANDOM
done


# $HOSTNAME
# $MACHTYPE
# $PS1 \t time \d fecha \w directorio actual \u usuario
# $UID id del usuario
# $SHLVL nivel de anidamiento
# $RANDOM numero aleatorio
# $SECONDS segundos que la bash esta en marcha

