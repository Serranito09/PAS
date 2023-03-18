#!/bin/bash



#grep -E para usar ERE, que viene siendoe el +, {n,m}, ...
echo "1) Usuarios del grupo 46"
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[^ ]+:46"
echo "2) Usuarios de los grupos 33,34 o 38"
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[^ ]+:(33|34|38)"
echo "3) Usuarios con un UID de 4 digitos"
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[0-9]{4}:"
echo "4) Usuarios con nombres de 4 caracteres"
cat /etc/passwd|grep -E "^[^ :]{4,4}:"

