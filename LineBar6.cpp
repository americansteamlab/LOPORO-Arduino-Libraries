#include "LineBar6.h"

LineBar6::LineBar6(const uint8_t pins[6], bool blackLineIsHigh)
: _blackHigh(blackLineIsHigh) {
  for (int i = 0; i < 6; i++) _pins[i] = pins[i];
  resetCalibration();
}

void LineBar6::begin() {
  // analog pins are inputs by default
}

void LineBar6::readRaw(uint16_t out[6]) {
  for (int i = 0; i < 6; i++) {
    out[i] = analogRead(_pins[i]);
  }
}

void LineBar6::resetCalibration(uint16_t initMin, uint16_t initMax) {
  for (int i = 0; i < 6; i++) {
    _minV[i] = initMin;
    _maxV[i] = initMax;
  }
  _lastPos = 2500;
}

void LineBar6::calibrateStep(uint8_t samples, uint16_t sampleDelayMs) {
  for (uint8_t s = 0; s < samples; s++) {
    for (int i = 0; i < 6; i++) {
      uint16_t v = analogRead(_pins[i]);
      if (v < _minV[i]) _minV[i] = v;
      if (v > _maxV[i]) _maxV[i] = v;
    }
    if (sampleDelayMs) delay(sampleDelayMs);
  }
}

uint16_t LineBar6::_mapCal(uint16_t raw, uint16_t mn, uint16_t mx) {
  if (mx <= mn) return 0;
  long x = (long)(raw - mn) * 1000L / (long)(mx - mn);
  if (x < 0) x = 0;
  if (x > 1000) x = 1000;
  return (uint16_t)x;
}

void LineBar6::readCalibrated(uint16_t out[6]) {
  uint16_t raw[6];
  readRaw(raw);

  for (int i = 0; i < 6; i++) {
    uint16_t v = _mapCal(raw[i], _minV[i], _maxV[i]);
    // Si línea negra es "alto" dejamos v; si es "bajo" invertimos
    out[i] = _blackHigh ? v : (1000 - v);
  }
}

bool LineBar6::lineDetected(uint16_t threshold) {
  uint16_t cal[6];
  readCalibrated(cal);
  for (int i = 0; i < 6; i++) {
    if (cal[i] > threshold) return true;
  }
  return false;
}

uint16_t LineBar6::readLinePosition(uint16_t calibrated[6]) {
  uint16_t calLocal[6];
  uint16_t* cal = calibrated ? calibrated : calLocal;

  if (!calibrated) readCalibrated(calLocal);

  long sum = 0;
  long weighted = 0;

  for (int i = 0; i < 6; i++) {
    int w = i * 1000; // 0,1000,2000,3000,4000,5000
    sum += cal[i];
    weighted += (long)cal[i] * w;
  }

  if (sum < 50) {
    // si se pierde, regresamos última posición
    return _lastPos;
  }

  uint16_t pos = (uint16_t)(weighted / sum);
  _lastPos = pos;
  return pos;
}
