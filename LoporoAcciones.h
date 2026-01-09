#pragma once
#include <Arduino.h>
#include "LoporoPins_328P.h"
#include "LoporoIO.h"
#include "TB6612.h"
#include "Ultrasonic3.h"
#include "LineBar6.h"
#include "LoporoPID.h"

// Para seguir pared
enum LadoPared : uint8_t { PARED_IZQUIERDA = 0, PARED_DERECHA = 1 };

class LoporoAcciones {
public:
  // Dispositivos
  LoporoIO io;
  TB6612 motores;
  Ultrasonic3 ultra;
  LineBar6 barra;

  LoporoAcciones();
  void begin();

  // ===== Variables fáciles (editables por alumnos) =====
  uint8_t velocidad_base = 170;

  // Pared (laberinto)
  float pared_objetivo_cm = 18.0f;
  float umbral_frente_cm  = 14.0f;   // obstáculo frontal (U2)

  // Sumo
  float umbral_rival_cm = 45.0f;

  // Línea
  uint16_t umbral_linea = 200;       // 0..1000 (calibrado)

  // PID editables
  LoporoPID pid_pared;
  LoporoPID pid_linea;

  // ===== Funciones de IO =====
  void esperar_boton();
  void led_on();
  void led_off();
  void parpadear(uint8_t veces);

  // ===== Sensores (para if) =====
  bool hay_obstaculo_frente();            // U2
  float distancia_frente_cm();            // U2
  float distancia_pared_cm(LadoPared lado); // U1 o U3

  bool ve_linea();
  uint16_t posicion_linea();

  // ===== Acciones básicas =====
  void avanzar(uint8_t vel);
  void retroceder(uint8_t vel);
  void girar_izquierda(uint8_t vel);
  void girar_derecha(uint8_t vel);
  void detener();

  // ===== Comportamientos =====
  void seguir_pared(LadoPared lado);
  void seguir_linea();

  // Sumo
  bool contrincante_encontrado();
  int  direccion_contrincante();     // -1 izq, 0 frente, +1 der
  void buscar_contrincante();
  void atacar();

  // Línea: calibración guiada
  void calibrar_linea_con_boton();

  // ===== Lectura y demos =====
  void imprimir_ultrasonicos(Stream& out);
  void imprimir_barra(Stream& out);
  void prueba_motores_basica();

  // Serial motor control (comandos en español)
  void control_serial_paso(Stream& s);

private:
  bool _linea_lista = false;

  float _distSegura(uint8_t idx, float fallback = 200.0f);
};
