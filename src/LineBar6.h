#pragma once
#include <Arduino.h>

// Barra de 6 sensores analógicos:
// - readRaw: 0..1023
// - calibrateStep: actualiza min/max
// - readCalibrated: 0..1000 (normalizado)
// - readLinePosition: 0..5000 (ponderado)
// - lineDetected: true/false según umbral
class LineBar6 {
public:
  LineBar6(const uint8_t pins[6], bool blackLineIsHigh = true);

  void begin();

  void readRaw(uint16_t out[6]);

  void calibrateStep(uint8_t samples = 1, uint16_t sampleDelayMs = 0);
  void resetCalibration(uint16_t initMin = 1023, uint16_t initMax = 0);

  void readCalibrated(uint16_t out[6]);
  uint16_t readLinePosition(uint16_t calibrated[6] = nullptr);

  bool lineDetected(uint16_t threshold = 200);

  void setBlackLineIsHigh(bool v) { _blackHigh = v; }

  const uint16_t* minVals() const { return _minV; }
  const uint16_t* maxVals() const { return _maxV; }

private:
  uint8_t _pins[6];
  bool _blackHigh;
  uint16_t _minV[6];
  uint16_t _maxV[6];
  uint16_t _lastPos = 2500;

  uint16_t _mapCal(uint16_t raw, uint16_t mn, uint16_t mx);
};
