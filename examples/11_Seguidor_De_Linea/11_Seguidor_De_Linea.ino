#include "LoporoAcciones.h"

LoporoAcciones robot;

void setup() {
  Serial.begin(115200);
  robot.begin();

  // Ajustes de PID para línea (los alumnos pueden probar)
  robot.velocidad_base = 160;
  robot.pid_linea.Kp = 0.08;
  robot.pid_linea.Ki = 0.0;
  robot.pid_linea.Kd = 0.15;

  Serial.println("SEGIDOR DE LINEA: calibra con boton (inicia y termina).");
  robot.calibrar_linea_con_boton();
}

void loop() {
  // IF: si pierde línea, detener
  if (!robot.ve_linea()) {
    robot.detener();
    robot.parpadear(1);
    delay(60);
  } else {
    robot.seguir_linea();
  }
}
