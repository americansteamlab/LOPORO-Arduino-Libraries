#include "TB6612.h"

TB6612::TB6612(const TB6612Pins& p) : _p(p) {}

void TB6612::begin() {
  pinMode(_p.AIN1, OUTPUT); pinMode(_p.AIN2, OUTPUT); pinMode(_p.PWMA, OUTPUT);
  pinMode(_p.BIN1, OUTPUT); pinMode(_p.BIN2, OUTPUT); pinMode(_p.PWMB, OUTPUT);

  if (_p.STBY != 255) {
    pinMode(_p.STBY, OUTPUT);
    digitalWrite(_p.STBY, HIGH);
  }

  stop();
}

int16_t TB6612::_clamp(int16_t v, int16_t lo, int16_t hi) {
  if (v < lo) return lo;
  if (v > hi) return hi;
  return v;
}

void TB6612::_apply(uint8_t in1, uint8_t in2, uint8_t pwm, bool invert, int16_t speed) {
  int16_t s = speed;
  if (invert) s = -s;
  s = _clamp(s, -255, 255);

  uint8_t p = (uint8_t)abs((int)s);

  if (s == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(pwm, 0);
    return;
  }

  bool fwd = (s > 0);
  digitalWrite(in1, fwd ? HIGH : LOW);
  digitalWrite(in2, fwd ? LOW : HIGH);
  analogWrite(pwm, p);
}

void TB6612::motorA(int16_t speed) { _apply(_p.AIN1, _p.AIN2, _p.PWMA, _p.invertA, speed); }
void TB6612::motorB(int16_t speed) { _apply(_p.BIN1, _p.BIN2, _p.PWMB, _p.invertB, speed); }

void TB6612::drive(int16_t v, int16_t w) {
  int16_t a = _clamp((int16_t)(v + w), -255, 255);
  int16_t b = _clamp((int16_t)(v - w), -255, 255);
  motorA(a);
  motorB(b);
}

void TB6612::forward(uint8_t spd)  { drive((int16_t)spd, 0); }
void TB6612::backward(uint8_t spd) { drive(-(int16_t)spd, 0); }
void TB6612::turnLeft(uint8_t spd) { drive(0, -(int16_t)spd); }
void TB6612::turnRight(uint8_t spd){ drive(0, (int16_t)spd); }

void TB6612::brake() {
  digitalWrite(_p.AIN1, HIGH); digitalWrite(_p.AIN2, HIGH); analogWrite(_p.PWMA, 0);
  digitalWrite(_p.BIN1, HIGH); digitalWrite(_p.BIN2, HIGH); analogWrite(_p.PWMB, 0);
}

void TB6612::stop() {
  motorA(0);
  motorB(0);
}

void TB6612::standby(bool enableStandby) {
  if (_p.STBY == 255) return;
  digitalWrite(_p.STBY, enableStandby ? LOW : HIGH);
}
