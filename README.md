# LOPORO (Arduino Library)

Librería educativa para el robot LOPORO (ATmega328P / AVR).

Incluye:
- TB6612FNG (motores)
- 3 ultrasonidos (distancia y presencia)
- Barra de 6 sensores (calibración min/max, normalizado, posición ponderada)
- PID configurable (Kp, Ki, Kd)
- Acciones en español: `seguir_pared`, `seguir_linea`, `buscar_contrincante`, `atacar`
- Control de motores por Serial (comandos en español)
- Ejemplos en español y limpios para alumnos

## Instalación
1. Descarga este repo como ZIP
2. Arduino IDE → **Sketch → Include Library → Add .ZIP Library**
3. Abre un ejemplo: **File → Examples → LOPORO → ...**

## Pinout (LOPORO / ATmega328P)
- LED: D13
- Botón: D12 (INPUT_PULLUP)
- TB6612FNG:
  - BIN2 D4, AIN1 D5, AIN2 D6, BIN1 D7, PWMA D10, PWMB D11
  - STBY no definido (255). En tu PCB puede estar fijo a HIGH.
- Ultrasonidos:
  - U1: trig D8, echo D9
  - U2: trig D2, echo D3 (frente fijo)
  - U3: trig A0, echo A1
- Barra 6 sensores:
  - {A7, A6, A2, A3, A4, A5} (solo A0/A1 cambian en tu PCB)

## Comandos Serial (Motores)
- `AYUDA`
- `VEL 180`
- `GIRO -60` (usa drive(velocidad_base, giro))
- `MANUAL A 200`
- `MANUAL B -120`
- `STOP`

## Ejemplos
- Motores normal
- Motores por Serial
- Lectura ultrasonidos
- Lectura barra 6
- Laberinto seguir pared (botón cambia lado)
- Seguidor de línea (con calibración por botón)
- Sumo (buscar y atacar)

## Uso rápido (Sumo)
```cpp
#include "LoporoAcciones.h"
LoporoAcciones robot;

void setup() {
  robot.begin();
  robot.esperar_boton();
  robot.umbral_rival_cm = 45;
}

void loop() {
  if (robot.contrincante_encontrado()) robot.atacar();
  else robot.buscar_contrincante();
}
