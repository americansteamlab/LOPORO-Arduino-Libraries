#include "LoporoAcciones.h"

LoporoAcciones robot;
bool encendido = false;

void setup() {
  Serial.begin(115200);
  robot.begin();
  robot.velocidad_base = 170;
  Serial.println("MOTORES: Boton = iniciar/detener");
}

void loop() {
  if (robot.io.click()) {
    encendido = !encendido;
    if (!encendido) {
      robot.detener();
      robot.led_off();
      Serial.println("STOP");
    } else {
      robot.led_on();
      Serial.println("RUN");
    }
    delay(120);
  }

  if (encendido) {
    robot.prueba_motores_basica();
  }
}
