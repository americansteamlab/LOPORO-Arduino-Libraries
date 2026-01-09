#include "LoporoAcciones.h"

LoporoAcciones robot;

void setup() {
  robot.begin();
  robot.esperar_boton();

  robot.umbral_rival_cm = 45;
}

void loop() {
  if (robot.contrincante_encontrado()) {
    robot.led_on();

    int dir = robot.direccion_contrincante();
    if (dir == 0) {
      robot.atacar();
    } else if (dir < 0) {
      robot.girar_izquierda(220);
    } else {
      robot.girar_derecha(220);
    }
  } else {
    robot.led_off();
    robot.buscar_contrincante();
  }
}
