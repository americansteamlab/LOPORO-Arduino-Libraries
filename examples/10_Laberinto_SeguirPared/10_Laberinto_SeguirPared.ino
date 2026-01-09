#include "LoporoAcciones.h"

LoporoAcciones robot;
LadoPared lado = PARED_DERECHA;

void setup() {
  robot.begin();
  robot.esperar_boton();

  // Ajustes que los alumnos pueden probar
  robot.velocidad_base = 170;
  robot.pared_objetivo_cm = 18;
  robot.umbral_frente_cm = 14;

  // PID de pared (probar Kp 4..9)
  robot.pid_pared.Kp = 6.0;
  robot.pid_pared.Ki = 0.0;
  robot.pid_pared.Kd = 0.0;
}

void loop() {
  // Botón cambia pared derecha/izquierda
  if (robot.io.click()) {
    lado = (lado == PARED_DERECHA) ? PARED_IZQUIERDA : PARED_DERECHA;
    robot.parpadear(lado == PARED_DERECHA ? 2 : 1);
  }

  // IF de seguridad: si hay obstáculo enfrente, girar
  if (robot.hay_obstaculo_frente()) {
    robot.led_on();
    robot.detener();
    robot.girar_izquierda(200);
    delay(220);
  } else {
    robot.led_off();
    robot.seguir_pared(lado);
  }
}
