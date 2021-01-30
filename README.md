# Curiosity-LPC-with-LabView
Adquisición de 5 señales analógicas mediante la plataforma Curiosity LPC de Microchip y sus respectivas gráficas en LabView.

El módulo Curiosity utiliza el pic 16F18446. La programacion del módulo se lo realizó mediante el ide MPLABX y el compilador MPLAB XC. Se utilizan 5 canales adc para la adquision de las señales analǵicas. Para generar un tiempo base para controlar los muestreos se utiliza el itmer con interrupción cada 1 segundo. Los peridos de muestreo se establecidos mediante LabView, donde el usuario digita el tiempo de muestreo para cada sensor. 

La comunicación entre el pic y LabView se los realiza mediante comunicación serial. El pic esta conifgurado para escuchar la comunicacion serial en el pin rx con interrupción, de tal manera que solo lee el serial cuando LabvIew envia los tiempos de muestreo. El tiempo por defecto es 1 segundo, sin mebargo, cuando el usuario modifica los tiempos de muestreo en LabView, estos se envian al pic el cual modifica unos contadores para controlar los nuevos tiempos de muestreo.

En la interfaz LabView todas las graficas muestran el voltaje de la señal. Ahora bien, si los sensores son de temperatura, luminosidad, distancia, etc., solo hay que cambiar los factores de converisn en LabView y obviamente las escalas de las gráficas.

Todos los datos recibidos por en LabvIew son guardadso en archivos de texto como registro.

Para distinguir los valores de cada sensor, el pic envia la letra A seguido del valor entero leido por el ADC para el primer sensor y asi respectivamente con las letras B_C_D_E para el resto de sensores.
Así por ejemplo:
A234
B4545
C90
D457
E987

En este caso, los canales del ADC tienen una resolución de 12bits, es decir que el ADC va a leer valores entre 0-2¹²(4096),en donde 4096 es 5V.
Así, para el ejemplo anterior, al llegar el valor A234 a Labview, este separa el primer caracter del numero, así identifica el sensor y convierte el numero a voltaje, en done en este caso correspondera a.
234*5V/4096 =0.28V.
