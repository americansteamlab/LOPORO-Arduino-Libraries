#pragma once
#include <Arduino.h>

// Botón + LED con antirrebote.
// - click(): regresa true una sola vez por pulsación
// - esperarBoton(): espera hasta pulsar (opcional parpadeo)
class LoporoIO {
public:
  LoporoIO(uint8_t pinBoton, uint8_t pinLed, uint16_t debounceMs = 35)
  : _btn(pinBoton), _led(pinLed), _debounce(debounceMs) {}

  void begin() {
    pinMode(_led, OUTPUT);
    apagarLed();

    pinMode(_btn, INPUT_PULLUP); // botón a GND
    _lastRead = digitalRead(_btn);
    _stable = _lastRead;
    _tChange = millis();
  }

  // LED
  void encenderLed() { digitalWrite(_led, HIGH); }
  void apagarLed()   { digitalWrite(_led, LOW);  }
  void toggleLed()   { digitalWrite(_led, !digitalRead(_led)); }

  void parpadear(uint8_t veces, uint16_t onMs = 120, uint16_t offMs = 120) {
    for (uint8_t i = 0; i < veces; i++) {
      encenderLed(); delay(onMs);
      apagarLed();   delay(offMs);
    }
  }

  // Botón (antirrebote)
  bool click() {
    bool r = digitalRead(_btn);
    unsigned long now = millis();

    if (r != _lastRead) {
      _lastRead = r;
      _tChange = now;
    }

    if ((now - _tChange) > _debounce) {
      if (r != _stable) {
        _stable = r;
        if (_stable == LOW) return true; // activo LOW
      }
    }
    return false;
  }

  void esperarBoton(bool parpadearMientras = true, uint16_t periodoBlinkMs = 250) {
    unsigned long tBlink = millis();
    bool ledState = false;

    // Espera a que esté liberado
    while (digitalRead(_btn) == LOW) delay(5);

    while (true) {
      if (parpadearMientras && (millis() - tBlink) >= periodoBlinkMs) {
        tBlink = millis();
        ledState = !ledState;
        digitalWrite(_led, ledState ? HIGH : LOW);
      }

      if (click()) {
        apagarLed();
        return;
      }
    }
  }

private:
  uint8_t _btn, _led;
  uint16_t _debounce;

  bool _lastRead = HIGH;
  bool _stable   = HIGH;
  unsigned long _tChange = 0;
};
