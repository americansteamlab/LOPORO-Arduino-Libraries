#include "Ultrasonic3.h"

Ultrasonic3::Ultrasonic3(const UltrasonicPins& u1,
                         const UltrasonicPins& u2,
                         const UltrasonicPins& u3) {
  _u[0] = u1; _u[1] = u2; _u[2] = u3;
}

void Ultrasonic3::begin() {
  for (int i = 0; i < 3; i++) {
    pinMode(_u[i].trig, OUTPUT);
    pinMode(_u[i].echo, INPUT);
    digitalWrite(_u[i].trig, LOW);
  }
}

float Ultrasonic3::_measure(const UltrasonicPins& p, uint32_t timeoutUs) {
  digitalWrite(p.trig, LOW);
  delayMicroseconds(2);
  digitalWrite(p.trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(p.trig, LOW);

  unsigned long dur = pulseIn(p.echo, HIGH, timeoutUs);
  if (dur == 0) return NAN;

  return (dur * 0.0343f) * 0.5f;
}

float Ultrasonic3::distanceCm(uint8_t index, uint32_t timeoutUs) {
  if (index < 1 || index > 3) return NAN;
  return _measure(_u[index - 1], timeoutUs);
}

bool Ultrasonic3::presence(uint8_t index, float thresholdCm, uint32_t timeoutUs) {
  float d = distanceCm(index, timeoutUs);
  if (isnan(d)) return false;
  return d <= thresholdCm;
}
