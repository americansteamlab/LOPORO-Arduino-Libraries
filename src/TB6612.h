#pragma once
#include <Arduino.h>

struct TB6612Pins {
  uint8_t AIN1, AIN2, PWMA;
  uint8_t BIN1, BIN2, PWMB;
  uint8_t STBY;        // 255 si no existe
  bool invertA = false;
  bool invertB = false;
};

class TB6612 {
public:
  explicit TB6612(const TB6612Pins& p);

  void begin();

  void motorA(int16_t speed); // -255..255
  void motorB(int16_t speed);

  // v = velocidad base, w = giro. Convención: w>0 gira a la derecha.
  void drive(int16_t v, int16_t w);

  void forward(uint8_t spd);
  void backward(uint8_t spd);
  void turnLeft(uint8_t spd);
  void turnRight(uint8_t spd);

  void brake();
  void stop();

  void standby(bool enableStandby);

private:
  TB6612Pins _p;

  void _apply(uint8_t in1, uint8_t in2, uint8_t pwm, bool invert, int16_t speed);
  int16_t _clamp(int16_t v, int16_t lo, int16_t hi);
};
