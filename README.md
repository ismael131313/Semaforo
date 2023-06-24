# Semaforo
En el siguiente proyecto se desarrolla una solucion a los requerimientos presentados. El hardware implementado corresponde a 3 leds y dos pulsantes con su respectiva conexion al arduino de nuestra preferencia.
El funcionamiento se describe de la siguiente forma: Inicialmente se tiene una secuencia de encendido de los leds, dicha secuencia se ve modificada según la interracción con el pulsante 1,
cuya finalidad es cambiar la velocidad de la secuencia a x0.5, x1 y x2, para lo cual se ha implementado una maquina de estados. El funcionamiento del pulsante 2 es cambiar el modo del funcionamiento del semaforo, en donde se tiene 3 estados, 
uno corresponde al funcionamiento normal, otro en el led amarillo se encuentra parpadeando a una cierta frecuencia, y un estado final en el que el led rojo se encuentra parpadeando con otra frecuencia.
Para el funcionamiento de los pulsantes se ha creado una funcion que se encarga de controlar el antirebote, de esta forma se asegura una lectura fiable de las pulsaciones.
De igual forma, las funciones correspondientes a los requerimientos han sido incluidas en archivos .h y .c, con la finalidad de hacer el código más manejable.
Se presentan dos codigos .ino, uno que funciona en el entorno de Arduino IDE; sin modularización (AntireboteArduinoIDE), y otro creado para Eclipse con la modularización correspondiente (antirebot3).

Como recomendación, para la ejecución del programa en entorno de Sloeber o Eclipse; se sugiere revisar la ubicación de las librerias de arduino, por ejemplo la de Serial, fueron comunes problemas de ejecución de la orden Serial.print() debido a la incorrecta ubicación de las librerías necesarias.
