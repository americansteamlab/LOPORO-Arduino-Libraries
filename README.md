# 🤖 LOPORO – Librería Arduino para Robótica Educativa

**LOPORO** es una librería Arduino diseñada para la **enseñanza de robótica educativa**, permitiendo que los alumnos programen robots de forma **clara, estructurada y progresiva**, usando funciones en **español** y lógica con `if`, sin enfrentarse a código complejo.

👉 Toda la complejidad (PID, control, filtros, parsing Serial, antirrebote) vive **dentro de la librería**  
👉 Los sketches quedan **limpios, cortos y entendibles**

---

## 🎯 Objetivo educativo

Esta librería está pensada para:

- Secundaria  
- Bachillerato / Preparatoria  
- Clubes de robótica  
- Introducción a sensores, control y lógica  

Los alumnos:

- ✅ Sí usan funciones  
- ✅ Sí escriben decisiones con `if`  
- ✅ Sí modifican variables y PID  
- ❌ No se pierden en electrónica ni matemáticas avanzadas  

---

## 🧩 ¿Qué incluye la librería?

## 🔹 1. Control de Motores – **TB6612FNG**

**Archivos**
- `TB6612.h`
- `TB6612.cpp`

Permite controlar **dos motores DC** usando el driver **TB6612FNG**.

### Funciones disponibles
```cpp
motorA(velocidad);
motorB(velocidad);

drive(velocidad, giro);

forward(velocidad);
backward(velocidad);
turnLeft(velocidad);
turnRight(velocidad);

brake();
stop();
```

---

## 🔹 2. Ultrasonidos (3 sensores) – **Ultrasonic3**

**Archivos**
- `Ultrasonic3.h`
- `Ultrasonic3.cpp`

Funciones:
```cpp
distanceCm(sensor);
presence(sensor, umbral_cm);
```

Convención:
- U1 Izquierda
- U2 Frente
- U3 Derecha

---

## 🔹 3. Barra de 6 sensores – **LineBar6**

Funciones:
```cpp
resetCalibration();
calibrateStep();
readRaw();
readCalibrated();
readLinePosition();
lineDetected(umbral);
```

---

## 🔹 4. Botón y LED – **LoporoIO**

Funciones:
```cpp
click();
esperarBoton();
encenderLed();
apagarLed();
parpadear(veces);
```

---

## 🔹 5. Control PID – **LoporoPID**

Variables:
```cpp
pid.Kp;
pid.Ki;
pid.Kd;
```

---

## 🔹 6. Acciones en Español – **LoporoAcciones**

Funciones principales:
```cpp
seguir_pared(lado);
seguir_linea();
buscar_contrincante();
atacar();
```

---

## 📂 Ejemplos incluidos

- Motores normal
- Motores por Serial
- Ultrasonidos
- Barra de sensores
- Laberinto
- Seguidor de línea
- Sumo
  
