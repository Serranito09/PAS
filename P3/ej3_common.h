#ifndef EJ3_COMMON_H
#define EJ3_COMMON_H

#define SERVER_QUEUE "/server_queue"
#define CLIENT_QUEUE "/client_queue"
#define MAX_SIZE 1024
#define MSG_STOP "exit"

#endif 

/*
Los ficheros de código de este ejercicio se llamarán ((ej3 servidor.c)), ((ej3 cliente.c))
y ((ej3 common.h)).

Implemente un programa en C que utilice colas de mensajes y comunique dos procesos,
de forma que cumpla los siguientes requisitos (puede utilizar como base el código de los fi-
cheros common.h, servidor.c y cliente.c que se le han proporcionado como ejemplo):

1.  Hay un proceso cliente que enviará cadenas leı́das desde teclado y las envı́a mediante
    mensajes a un proceso servidor cada vez que pulsamos INTRO.

2.  El servidor recibirá los mensajes y contará el número de caracteres recibidos excep-
    tuando el fin de cadena (un espacio en blanco se considerará un carácter). Tras esto, el
    servidor mandará un mensaje al cliente, por otra cola distinta, con la cadena “Número
    de caracteres recibidos: X”, siendo X el número de caracteres calculados.

    Por tanto habrá dos colas, ambas creadas por el servidor:

    a) Una cola servirá para que el cliente le envı́e al servidor las cadenas de texto.
    De esta cola leerá el servidor para obtener dichas cadenas y analizarlas para contar
    el número de caracteres que tienen.

    b) Otra cola por la que el servidor enviará al cliente el número de caracteres calcula-
    dos en la cadena de texto recibida por la primera cola.
    De esta segunda cola leerá el cliente para mostrar el número de caracteres calcu-
    lados que le ha enviado el servidor.

    Se han de tener en cuenta los siguientes items:

    La cola de mensajes para el texto “Número de caracteres recibidos: X”, enviados
    desde el servidor al cliente, se creará y eliminará por parte del servidor (que siem-
    pre es el primero en lanzarse) y la abrirá el cliente.

    Si el servidor tiene cualquier problema en su ejecución deberá mandar el mensaje
    de salida, para forzar al cliente a parar.

3.  Asegurar que el nombre de las colas sea diferente para su ejecución en un sistema
    compartido. Puede usar la idea de anexar el login al nombre de la cola.

4. En el código de que se dispone en Moodle (ficheros common.h, servidor.c y cliente.c),
    tanto el cliente como el servidor tienen incluidas unas funciones de log. Estas funciones
    implementan un pequeño sistema de registro o log. Utilizándolas se registran en fiche-
    ros de texto los mensajes que los programas van mostrando por pantalla (log-servidor.txt
    y log-cliente.txt).

    Por ejemplo, si queremos registrar en el cliente un mensaje simple, harı́amos la siguien-
    te llamada:

    funcionLog("Error al abrir la cola del servidor");

    Si quisiéramos registrar un mensaje más complejo (por ejemplo, donde incluimos el
    mensaje recibido a través de la cola), la llamada podrı́a hacerse del siguiente modo:
    
    char msgbuf[100];
    ...
    sprintf(msgbuf,"Recibido el mensaje: %s\n", buffer);
    funcionLog(msgbuf);

    Utilice estas llamadas para dejar registro en fichero de texto de todos los mensajes que
    se muestren por pantalla en la ejecución del cliente y el servidor, incluidos los errores
    que se imprimen por consola. 

5.  El programa cliente capturará las señales SIGTERM y SIGINT para gestionar adecua-
    damente el fin del programa servidor y de él mismo. Puede asociar estas señales con
    una misma función que pare el programa.

    Dicha función deberá, en primer lugar, registrar la señal capturada (y su número
    entero) en el fichero de log del cliente.

    El cliente, antes de salir, deberá mandar a la cola correspondiente, un mensaje de
    fin de sesión (que debe interpretar el servidor), que hará que el otro extremo deje
    de esperar mensajes. Este mensaje también se registrará en los logs.

    Se deberá cerrar, en caso de que estuvieran abiertas, aquellas colas que se estén
    utilizando y el fichero de log.
*/