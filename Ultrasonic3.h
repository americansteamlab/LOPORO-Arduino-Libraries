#pragma once
#include <Arduino.h>

struct UltrasonicPins {
  uint8_t trig;
  uint8_t echo;
};

class Ultrasonic3 {
public:
  Ultrasonic3(const UltrasonicPins& u1,
              const UltrasonicPins& u2,
              const UltrasonicPins& u3);

  void begin();

  // index: 1..3
  float distanceCm(uint8_t index, uint32_t timeoutUs = 30000UL);
  bool presence(uint8_t index, float thresholdCm, uint32_t timeoutUs = 30000UL);

private:
  UltrasonicPins _u[3];
  float _measure(const UltrasonicPins& p, uint32_t timeoutUs);
};
