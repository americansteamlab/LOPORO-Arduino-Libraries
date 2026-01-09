#include "LoporoAcciones.h"

LoporoAcciones robot;

void setup() {
  Serial.begin(115200);
  robot.begin();
  Serial.println("MOTORES SERIAL: escribe AYUDA");
}

void loop() {
  robot.control_serial_paso(Serial);

  // STOP rápido con botón
  if (robot.io.click()) {
    robot.detener();
    robot.parpadear(1);
  }
}
