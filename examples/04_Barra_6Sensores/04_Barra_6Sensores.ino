#include "LoporoAcciones.h"

LoporoAcciones robot;

void setup() {
  Serial.begin(115200);
  robot.begin();

  Serial.println("BARRA: Presiona boton para iniciar calibracion, presiona otra vez para terminar.");
  robot.calibrar_linea_con_boton();
}

void loop() {
  robot.imprimir_barra(Serial);

  if (robot.ve_linea()) robot.led_on();
  else robot.led_off();

  delay(120);
}
