#!/bin/bash

#-o: en lugar de imprimir las líneas completas que cumplen el patrón, solo muestra el emparejamiento del patrón.


#Estructura de corchetes con ^ dentro coge todo menos lo que haya dentro
echo "1) Grupos que contengan al menos 1 usuario además del usuario principal del grupo"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[^ ]+:[^ ]+')"
				# "^([^;]+:){3}[^:]"
echo
echo "2) Grupos cuyo nombre empiece por u y acabe por s"
echo
echo "$(cat /etc/group | grep -Eo '^u.s:[^_]:.$')"
#echo "$(cat /etc/group | grep -Eo '^u*s$:[^_]:.$')"
echo
echo "3) Grupos que no contengan ningún usuario adicional"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[^ ]+:$')"
echo
echo "4) Grupos con GID menor que 100"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[0-9]{2}:.*$')"
