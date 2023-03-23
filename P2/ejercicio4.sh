#!/bin/bash



#grep -E para usar ERE, que viene siendoe el +, {n,m}, ...
echo "1) Usuarios del grupo 46"
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[^ ]+:46" #miramos que el cuarto apartado sea 46 (cada apartado es una seccion entre dos puntos)
echo
echo "2) Usuarios cuyo nombre empiece y acabe con la misma letra"
cat /etc/passwd|grep  -E "^([a-zA-Z])[^:]*\1:" #decimos que empieze por una letra, que haya en medio cualquier caracter menos : (* significa que puede haber 0, 1 o + caracteres,
echo                                           #en este caso que no sean :), y \1 indica que debe repetirse el caracter entre parentesis antes de los :
echo "3) Usuarios cuyo nombre no contenga la letra a/A"
cat /etc/passwd|grep  -E "^[^aA]*:" #indicamos que no puede empezar por ningun caraccter que sea la a/A 0 o muchas veces y que el ultimo caracter sea :
echo
echo "4) Usuarios con UID de 4 digitos"
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[0-9]{4}:" #el UID esta en el tercer apartado, con el {4} indicamos que tiene que ser 4 numeros consecutivos
echo
echo "5) Usuarios con nombres entre 3 y 5 caracteres" 
cat /etc/passwd|grep -E "^[^ :]{3,5}:" #indicamos que debe tener entre 3 o 5 caracteres que no sea espacio o :

#echo "2) Usuarios de los grupos 33,34 o 38"
#cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[^ ]+:(33|34|38)"