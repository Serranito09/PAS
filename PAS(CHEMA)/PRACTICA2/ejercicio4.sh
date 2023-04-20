#!/bin/bash
#ejercicio4.sh

echo "1) Usuarios del grupo 46" #Usuarios del grupo 46
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[^ ]+:46"
echo ""

echo "2) Usuarios de los grupos 33,34 o 38" #Usuarios del grupo 33,34,38
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[^ ]+:(33|34|38)"
echo ""

echo "3) Usuarios con un UID de 4 digitos" #Usuario con un UID de 4 digitos
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[0-9]{4}:"
echo ""

echo "4) Usuarios con nombres de 4 caracteres" #Usuarios que tenga especificamente 4 caracteres y si se modifica el rango cambiara
cat /etc/passwd|grep -E "^[^ :]{4,4}:"
echo ""
