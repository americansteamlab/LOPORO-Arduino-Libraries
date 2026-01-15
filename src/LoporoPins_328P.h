#pragma once
#include <Arduino.h>

// ===== LOPORO PINOUT (ATmega328P / UNO/Nano) =====

// LED / Botón
static constexpr uint8_t LOPORO_LED    = 13; // PB5
static constexpr uint8_t LOPORO_BUTTON = 12; // PB4 (INPUT_PULLUP)

// TB6612FNG
static constexpr uint8_t LOPORO_TB_BIN2 = 4;   // PD4
static constexpr uint8_t LOPORO_TB_AIN1 = 5;   // PD5
static constexpr uint8_t LOPORO_TB_AIN2 = 6;   // PD6
static constexpr uint8_t LOPORO_TB_BIN1 = 7;   // PD7
static constexpr uint8_t LOPORO_TB_PWMA = 10;  // PB2 (PWM)
static constexpr uint8_t LOPORO_TB_PWMB = 11;  // PB3 (PWM)
static constexpr uint8_t LOPORO_TB_STBY = 255; // 255 = no definido (o fijo a HIGH en PCB)

// Ultrasonidos
static constexpr uint8_t LOPORO_U1_TRIG = 9; // PB0
static constexpr uint8_t LOPORO_U1_ECHO = 8; // PB1

static constexpr uint8_t LOPORO_U2_TRIG = 3; // PD2
static constexpr uint8_t LOPORO_U2_ECHO = 2; // PD3  (FRONTAL)

static constexpr uint8_t LOPORO_U3_TRIG = A1; // PC0
static constexpr uint8_t LOPORO_U3_ECHO = A0; // PC1

// Barra 6 sensores (NOTA: A0 y A1 están ocupados por U3, por eso la barra usa A7,A6,A2,A3,A4,A5)
static constexpr uint8_t LOPORO_LINE_PINS[6] = { A7, A6, A2, A3, A4, A5 };
