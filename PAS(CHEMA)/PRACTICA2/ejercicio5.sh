#!/bin/bash
#ejercicio5.sh

echo "1) Grupos que contengan al menos 1 usuario además del usuario principal del grupo"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[^ ]+:[^ ]+')" #Indica el grupo y los usuarios que contiene
echo
echo "2) Grupos cuyo nombre empiece por u y acabe por s"
echo
echo "$(cat /etc/group | grep -Eo '^u.s:[^_]:.$')" #Creo que no funciona
echo
echo "3) Grupos que no contengan ningún usuario adicional"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[^ ]+:$')" #Grupos con ningun usuario adicional
echo
echo "4) Grupos con GID menor que 100"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[0-9]{2}:.*$')" #Grupos con GID menor que 100
