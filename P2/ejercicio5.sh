#!/bin/bash

#-o: en lugar de imprimir las líneas completas que cumplen el patrón, solo muestra el emparejamiento del patrón.


#Estructura de corchetes con ^ dentro coge todo menos lo que haya dentro
echo "1) Grupos que contengan al menos 1 usuario además del usuario principal del grupo"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[^ ]+:[^ ]+')" #para que tenga al menos un usario ademas del principal debe tener 4 apartados, por lo que mostramos los grupos con 4 apartados
echo
echo "2) Grupos cuyo nombre empiece por u y acabe por s"
echo
cat /etc/group | grep -E '^[uU][^:]*[sS]:' #indicamos que empieze por u/U que tenga cualquier caracte que no sea dos puntos 0 o muchas veces y que termineen s/S:
echo
echo "3) Grupos cuyo nombre contenga dos letras iguales seguidas"
echo
cat /etc/group | grep -E '[^:]*([a-zA-Z])\1[^:]*:' #decimos que no empieze por : y que contenga un caracter (el que esta entre parentesis) y el \1 indica que es mismo caracter se debe 
echo 											   #repetir a continuacion, y que hayan los caracteres que sean hasta llegar a los :
echo "4) Grupos que no contengan ningún usuario adicional"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[^ ]+:$')" #un grupo contiene un usuario adicional en el ultimo: hay algo escrito  ej audio:x:29:pulse 
echo                                                       #entonces debemos comprobar que al final no haya escrito ningun caracter o que : sea el final de la cadena de caracter
echo "5) Grupos con GID menor que 100"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[0-9]{2}:.*$')" #indicamos con el [0-9] que sea un unmero del 0 al 9 y con el {2} que sean consecutivos
