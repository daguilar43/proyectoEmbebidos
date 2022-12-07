Estos archivos contienen las funciones básicas para el funcionamiento de la Amiplanta.

El archivo adc.c contiene la lógica para la inicialización y lectura de cada uno de los sensores excepto el sensor de luz.
Estos sensores en general son adcs y gpios.

El archivo sensorLuz.c contiene la lógica para inicializar y controlar el sensor de luz utilizado. Este utiliza funciones base de i2c, lo que permite calibrar la 
resolución necesaria y prender el dispositivo para tomar lecturas.

El archivo carasOled.c contiene los mapas de bit de cada una de las emociones utilizadas por el programa. Además maneja la pantalla escribiendo los mapas de bits y 
calcula las emociones en funcion de la lectura de los diferentes sensores.
