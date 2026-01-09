#include "LoporoAcciones.h"

// Helpers Serial
static String _leerLinea(Stream& s) {
  static String buf;
  while (s.available()) {
    char c = (char)s.read();
    if (c == '\r') continue;
    if (c == '\n') {
      String line = buf;
      buf = "";
      line.trim();
      return line;
    }
    if (buf.length() < 80) buf += c;
  }
  return "";
}

static int _toIntClamped(const String& t, int lo, int hi) {
  long v = t.toInt();
  if (v < lo) v = lo;
  if (v > hi) v = hi;
  return (int)v;
}

LoporoAcciones::LoporoAcciones()
: io(LOPORO_BUTTON, LOPORO_LED),
  motores({
    LOPORO_TB_AIN1, LOPORO_TB_AIN2, LOPORO_TB_PWMA,
    LOPORO_TB_BIN1, LOPORO_TB_BIN2, LOPORO_TB_PWMB,
    LOPORO_TB_STBY,
    false, false
  }),
  ultra(
    {LOPORO_U1_TRIG, LOPORO_U1_ECHO},
    {LOPORO_U2_TRIG, LOPORO_U2_ECHO},
    {LOPORO_U3_TRIG, LOPORO_U3_ECHO}
  ),
  barra(LOPORO_LINE_PINS, true) // negro=alto por defecto
{
  // PID sugeridos por defecto (los alumnos pueden cambiarlos)
  pid_pared.Kp = 6.0f; pid_pared.Ki = 0.0f; pid_pared.Kd = 0.0f;
  pid_pared.outMin = -120; pid_pared.outMax = 120;

  pid_linea.Kp = 0.08f; pid_linea.Ki = 0.0f; pid_linea.Kd = 0.15f;
  pid_linea.outMin = -180; pid_linea.outMax = 180;
}

void LoporoAcciones::begin() {
  io.begin();
  motores.begin();
  ultra.begin();
  barra.begin();
}

float LoporoAcciones::_distSegura(uint8_t idx, float fallback) {
  float d = ultra.distanceCm(idx);
  return isnan(d) ? fallback : d;
}

// IO
void LoporoAcciones::esperar_boton() { io.esperarBoton(true); io.parpadear(2); }
void LoporoAcciones::led_on() { io.encenderLed(); }
void LoporoAcciones::led_off() { io.apagarLed(); }
void LoporoAcciones::parpadear(uint8_t v) { io.parpadear(v); }

// Sensores
float LoporoAcciones::distancia_frente_cm() { return _distSegura(2); } // U2
bool LoporoAcciones::hay_obstaculo_frente() { return distancia_frente_cm() < umbral_frente_cm; }

float LoporoAcciones::distancia_pared_cm(LadoPared lado) {
  return (lado == PARED_DERECHA) ? _distSegura(3) : _distSegura(1);
}

bool LoporoAcciones::ve_linea() {
  if (!_linea_lista) return false;
  return barra.lineDetected(umbral_linea);
}

uint16_t LoporoAcciones::posicion_linea() {
  return barra.readLinePosition();
}

// Acciones
void LoporoAcciones::avanzar(uint8_t vel) { motores.forward(vel); }
void LoporoAcciones::retroceder(uint8_t vel) { motores.backward(vel); }
void LoporoAcciones::girar_izquierda(uint8_t vel) { motores.turnLeft(vel); }
void LoporoAcciones::girar_derecha(uint8_t vel) { motores.turnRight(vel); }
void LoporoAcciones::detener() { motores.stop(); }

// Comportamientos
void LoporoAcciones::seguir_pared(LadoPared lado) {
  float dP = distancia_pared_cm(lado);
  float error = dP - pared_objetivo_cm;

  float w = pid_pared.update(error);

  // Convención: w>0 gira a la derecha
  // Si seguimos izquierda, invertimos
  if (lado == PARED_IZQUIERDA) w = -w;

  motores.drive((int16_t)velocidad_base, (int16_t)w);
}

void LoporoAcciones::seguir_linea() {
  if (!_linea_lista) { motores.stop(); return; }

  uint16_t pos = barra.readLinePosition(); // 0..5000
  float error = (float)((int16_t)pos - 2500);

  float w = pid_linea.update(error);
  motores.drive((int16_t)velocidad_base, (int16_t)w);

  if (!barra.lineDetected(umbral_linea)) {
    motores.brake();
    delay(35);
  }
}

// Sumo
bool LoporoAcciones::contrincante_encontrado() {
  return ultra.presence(1, umbral_rival_cm) ||
         ultra.presence(2, umbral_rival_cm) ||
         ultra.presence(3, umbral_rival_cm);
}

int LoporoAcciones::direccion_contrincante() {
  bool izq = ultra.presence(1, umbral_rival_cm);
  bool fre = ultra.presence(2, umbral_rival_cm);
  bool der = ultra.presence(3, umbral_rival_cm);

  if (fre) return 0;
  if (izq && !der) return -1;
  if (der && !izq) return +1;
  return 0;
}

void LoporoAcciones::buscar_contrincante() {
  motores.turnRight(150);
}

void LoporoAcciones::atacar() {
  motores.forward(255);
}

// Calibración línea
void LoporoAcciones::calibrar_linea_con_boton() {
  barra.resetCalibration();
  io.esperarBoton(true); // iniciar

  while (true) {
    barra.calibrateStep(1);
    io.toggleLed();
    delay(60);
    if (io.click()) break;
  }

  io.apagarLed();
  _linea_lista = true;
  io.parpadear(2);
}

// Debug
void LoporoAcciones::imprimir_ultrasonicos(Stream& out) {
  float d1 = _distSegura(1);
  float d2 = _distSegura(2);
  float d3 = _distSegura(3);

  out.print("U1(izq)="); out.print(d1, 1); out.print("cm  ");
  out.print("U2(frente)="); out.print(d2, 1); out.print("cm  ");
  out.print("U3(der)="); out.print(d3, 1); out.print("cm  ");

  out.print(" presencias[");
  out.print(ultra.presence(1, umbral_rival_cm) ? 1 : 0); out.print(",");
  out.print(ultra.presence(2, umbral_rival_cm) ? 1 : 0); out.print(",");
  out.print(ultra.presence(3, umbral_rival_cm) ? 1 : 0); out.print("]");
  out.println();
}

void LoporoAcciones::imprimir_barra(Stream& out) {
  uint16_t raw[6];
  uint16_t cal[6];

  barra.readRaw(raw);
  barra.readCalibrated(cal);
  uint16_t pos = barra.readLinePosition();
  bool det = barra.lineDetected(umbral_linea);

  out.print("raw=[");
  for (int i=0;i<6;i++){ out.print(raw[i]); if(i<5) out.print(","); }
  out.print("] cal=[");
  for (int i=0;i<6;i++){ out.print(cal[i]); if(i<5) out.print(","); }
  out.print("] pos="); out.print(pos);
  out.print(" detecta="); out.println(det ? 1 : 0);
}

void LoporoAcciones::prueba_motores_basica() {
  avanzar(velocidad_base); delay(800);
  detener(); delay(300);

  retroceder(velocidad_base); delay(800);
  detener(); delay(300);

  girar_izquierda(velocidad_base); delay(550);
  detener(); delay(300);

  girar_derecha(velocidad_base); delay(550);
  detener(); delay(500);
}

// Serial
void LoporoAcciones::control_serial_paso(Stream& s) {
  String line = _leerLinea(s);
  if (line.length() == 0) return;

  String u = line;
  u.toUpperCase();

  if (u == "AYUDA") {
    s.println("Comandos:");
    s.println("  VEL n        (0..255)");
    s.println("  GIRO n       (-255..255)");
    s.println("  MANUAL A n   (-255..255)");
    s.println("  MANUAL B n   (-255..255)");
    s.println("  STOP");
    return;
  }

  if (u == "STOP") {
    detener();
    s.println("OK STOP");
    return;
  }

  int sp1 = u.indexOf(' ');
  String cmd = (sp1 == -1) ? u : u.substring(0, sp1);
  String rest = (sp1 == -1) ? "" : u.substring(sp1 + 1);
  rest.trim();

  if (cmd == "VEL") {
    int v = _toIntClamped(rest, 0, 255);
    velocidad_base = (uint8_t)v;
    s.print("OK VEL="); s.println(velocidad_base);
    return;
  }

  if (cmd == "GIRO") {
    int w = _toIntClamped(rest, -255, 255);
    motores.drive((int16_t)velocidad_base, (int16_t)w);
    s.print("OK GIRO="); s.println(w);
    return;
  }

  if (cmd == "MANUAL") {
    int sp2 = rest.indexOf(' ');
    if (sp2 == -1) { s.println("ERR"); return; }
    String m = rest.substring(0, sp2); m.trim();
    String tv = rest.substring(sp2 + 1); tv.trim();
    int v = _toIntClamped(tv, -255, 255);

    if (m == "A") { motores.motorA((int16_t)v); s.println("OK A"); return; }
    if (m == "B") { motores.motorB((int16_t)v); s.println("OK B"); return; }
    s.println("ERR");
    return;
  }

  s.println("ERR");
}
