#pragma once
#include <Arduino.h>

// PID simple con límites y anti-windup.
struct LoporoPID {
  float Kp = 0.0f;
  float Ki = 0.0f;
  float Kd = 0.0f;

  float integral = 0.0f;
  float lastError = 0.0f;

  float outMin = -255.0f;
  float outMax =  255.0f;
  float iMin   = -200.0f;
  float iMax   =  200.0f;

  void reset() { integral = 0; lastError = 0; }

  float update(float error) {
    integral += error;
    if (integral < iMin) integral = iMin;
    if (integral > iMax) integral = iMax;

    float deriv = error - lastError;
    lastError = error;

    float out = (Kp * error) + (Ki * integral) + (Kd * deriv);
    if (out < outMin) out = outMin;
    if (out > outMax) out = outMax;
    return out;
  }
};
