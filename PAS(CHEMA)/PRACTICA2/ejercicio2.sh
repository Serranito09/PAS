#posibles alternativas para tener la latencia media
#ping -c 4 www.stackoverflow.com | tail -1| awk '{print $4}' | cut -d '/' -f 2
#ping -c 4 www.stackoverflow.com | tail -1| awk -F '/' '{print $5}'
#ping -c 4 www.stackoverflow.com | sed '$!d;s|./\([0-9.]\)/.*|\1|'

fichero="$1"
numero_pings="$2"
timeout="$3"

if [ $# -ne 3 ] || [ ! -e $fichero ] #Comprueba los argumentos pasados
then
    echo "Argumentos incorrecto. Uso: ./ejercicio2.sh <archivo_ips> <número_ping> <timeout>"
    exit
fi

#IFS= read -r line
for ip in $(cat $fichero) #guarda en $ip cada linea del fichero $fichero
do
    #el comando ping nos da mucha informacion con tail -1 nos quedamos solo con la ultima linea
    #awk te permite sacar la columna que quieras separada por el caracter que esta entre comillas
        #si tienes rtt min/avg/max/mdev = 15.392/23.753/42.119/10.922
        #         |---$1--|$2-|-$3|-----$4------|--$5--|--$6--|--$7--|
    pig=$(ping -c $numero_pings -W $timeout $ip | tail -1| awk -F '/' '{print $5}')

    if [[ $pig < $timeout ]] #hay que poner dobles corchetes #si el ping es menor que el timeout, la ip no responde
    then
        echo "La IP $ip no respondió en $timeout segundos"
    else
        echo "$ip $pig ms"
    fi
done
