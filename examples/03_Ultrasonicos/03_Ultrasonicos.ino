#include "LoporoAcciones.h"

LoporoAcciones robot;

void setup() {
  Serial.begin(115200);
  robot.begin();

  robot.umbral_rival_cm = 30; // objeto cerca
  robot.umbral_frente_cm = 20;

  Serial.println("ULTRASONICOS: LED se prende si hay algo enfrente (U2).");
}

void loop() {
  robot.imprimir_ultrasonicos(Serial);

  if (robot.hay_obstaculo_frente()) robot.led_on();
  else robot.led_off();

  delay(200);
}
