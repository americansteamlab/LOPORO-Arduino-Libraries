LOPORO – Librería Arduino para Robótica Educativa
================================================

LOPORO es una librería Arduino diseñada para la enseñanza de robótica educativa,
permitiendo que los alumnos programen robots de forma clara, estructurada y
progresiva, usando funciones en español y lógica con if, sin enfrentarse a código
complejo ni confuso.

Toda la complejidad (PID, control, filtros, parsing Serial, antirrebote) vive
DENTRO de la librería.
Los sketches quedan LIMPIOS, CORTOS y ENTENDIBLES para los alumnos.


OBJETIVO EDUCATIVO
------------------

Esta librería está pensada para:

- Secundaria
- Bachillerato / Preparatoria
- Clubes de robótica
- Introducción a sensores, control y lógica

Los alumnos:
- Sí usan funciones
- Sí escriben decisiones con if
- Sí modifican variables y PID
- NO se pierden en electrónica ni matemáticas avanzadas


QUE INCLUYE LA LIBRERIA
----------------------


1) CONTROL DE MOTORES – TB6612FNG
--------------------------------

Archivos:
- TB6612.h
- TB6612.cpp

Permite controlar dos motores DC usando el driver TB6612FNG.

Funciones disponibles:

motorA(velocidad);
motorB(velocidad);

drive(velocidad, giro);

forward(velocidad);
backward(velocidad);
turnLeft(velocidad);
turnRight(velocidad);

brake();
stop();

Usado en:
- Laberinto
- Seguidor de línea
- Sumo
- Control por Serial
- Pruebas de motores


2) ULTRASONIDOS (3 SENSORES) – Ultrasonic3
------------------------------------------

Archivos:
- Ultrasonic3.h
- Ultrasonic3.cpp

Permite manejar 3 sensores ultrasónicos simultáneamente.

Funciones:

distanceCm(sensor);
presence(sensor, umbral_cm);

distanceCm devuelve la distancia en centímetros.
presence devuelve true o false.

Convención de sensores:
- U1 = Izquierda
- U2 = Frente (fijo)
- U3 = Derecha

Usado en:
- Laberinto (seguir pared)
- Sumo
- Lectura de sensores


3) BARRA DE 6 SENSORES – LineBar6
--------------------------------

Archivos:
- LineBar6.h
- LineBar6.cpp

Incluye:
- Lectura cruda (RAW)
- Calibración mínima y máxima
- Lectura normalizada (0–1000)
- Promedio ponderado (posición de la línea)
- Detección de línea como booleano

Funciones:

resetCalibration();
calibrateStep();

readRaw();
readCalibrated();
readLinePosition();

lineDetected(umbral);

Usado en:
- Seguidor de línea
- Lectura de barra


4) BOTON Y LED – LoporoIO
-------------------------

Archivo:
- LoporoIO.h

Manejo simple de botón con antirrebote y LED indicador.

Funciones:

click();
esperarBoton();

encenderLed();
apagarLed();
parpadear(veces);

Uso educativo:
- Iniciar robot
- Cambiar modos
- Calibrar sensores
- Retroalimentación visual para alumnos


5) CONTROL PID CONFIGURABLE – LoporoPID
---------------------------------------

Archivo:
- LoporoPID.h

PID simple con:
- Anti-windup
- Límites de salida
- Reset interno

Variables que los alumnos pueden modificar:

pid.Kp
pid.Ki
pid.Kd

Usado en:
- Seguir pared
- Seguidor de línea


6) ACCIONES EN ESPAÑOL – LoporoAcciones (NÚCLEO)
------------------------------------------------

Archivos:
- LoporoAcciones.h
- LoporoAcciones.cpp

Este módulo une TODOS los sensores y actuadores y expone funciones
claras en español para que los alumnos programen con lógica.


FUNCIONES DE SENSORES (PARA USAR EN IF)
---------------------------------------

hay_obstaculo_frente();
distancia_frente_cm();
distancia_pared_cm(lado);

ve_linea();
posicion_linea();

contrincante_encontrado();
direccion_contrincante();


ACCIONES BASICAS
----------------

avanzar(velocidad);
retroceder(velocidad);

girar_izquierda(velocidad);
girar_derecha(velocidad);

detener();


COMPORTAMIENTOS COMPLETOS
-------------------------

seguir_pared(lado);
seguir_linea();

buscar_contrincante();
atacar();


UTILIDADES EDUCATIVAS
--------------------

esperar_boton();
calibrar_linea_con_boton();

imprimir_ultrasonicos(Serial);
imprimir_barra(Serial);

prueba_motores_basica();
control_serial_paso(Serial);


FILOSOFIA DE DISEÑO
------------------

Dentro de la librería:
- PID
- Control
- Antirrebote
- Parsing Serial
- Electrónica
- Detalles técnicos

En el sketch del alumno:
- if
- decisiones
- parámetros
- ideas
- lógica

El alumno razona, experimenta y aprende,
sin copiar código complejo.


EJEMPLOS INCLUIDOS
------------------

01_Motores_Normal
- Uso básico de motores

02_Motores_Serial
- Control por comandos Serial

03_Ultrasonicos
- Lectura de distancia y presencia

04_Barra_6Sensores
- Calibración y lectura de línea

10_Laberinto_SeguirPared
- Uso de if + seguir pared

11_Seguidor_De_Linea
- PID y seguimiento de línea

12_Sumo
- Lógica de combate


EJEMPLO MINIMO (LABERINTO)
-------------------------

#include "LoporoAcciones.h"

LoporoAcciones robot;
LadoPared lado = PARED_DERECHA;

void setup() {
  robot.begin();
  robot.esperar_boton();
}

void loop() {
  if (robot.io.click()) {
    lado = (lado == PARED_DERECHA) ? PARED_IZQUIERDA : PARED_DERECHA;
  }

  if (robot.hay_obstaculo_frente()) {
    robot.girar_izquierda(200);
  } else {
    robot.seguir_pared(lado);
  }
}
