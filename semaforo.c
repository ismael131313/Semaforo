/*
 * semaforo.c
 *
 *  Created on: Jun 18, 2023
 *      Author: ISMAEL
 */
#include "semaforo.h"
const int PIN_TECLA_1 = 2;
const int PIN_TECLA_2 = 3;
const int PIN_LED_VERDE = 4;
const int PIN_LED_AMARILLO = 5;
const int PIN_LED_ROJO = 6;
unsigned long tiempoAnteriorTecla1 = 0;
unsigned long tiempoAnteriorTecla2 = 0;
unsigned long tiempoBase = 1000;  // Tiempo base en milisegundos
unsigned long tiempoAnterior = 0;
const int secuenciaNormal[] = {4, 5, 6}; //pin verde, pin amarillo, pin rojo
int indiceSecuencia = 0;

void semaforoNormal() {
  // Secuencia de LEDs en modo normal
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= tiempoBase) {
    tiempoAnterior = tiempoActual;

    digitalWrite(secuenciaNormal[indiceSecuencia], LOW);  // Apagar el LED actual

    indiceSecuencia = (indiceSecuencia + 1) % 3;//sizeof(secuenciaNormal);  // Avanzar al siguiente LED

    digitalWrite(secuenciaNormal[indiceSecuencia], HIGH);  // Encender el siguiente LED
  }
};
void semaforoDesconectado() {
  // LED amarillo intermitente cada 500 ms
  unsigned long tiempoActual = millis();
  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_ROJO, LOW);
  if (tiempoActual - tiempoAnterior >= 500) {
    tiempoAnterior = tiempoActual;

    static bool estadoLED = false;

    if (estadoLED) {
      digitalWrite(PIN_LED_AMARILLO, HIGH);
      estadoLED = false;
    } else {
      digitalWrite(PIN_LED_AMARILLO, LOW);
      estadoLED = true;
    }
  }
};
void semaforoAlarma() {
  // LED rojo intermitente cada 1 s
  unsigned long tiempoActual = millis();
  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_AMARILLO, LOW);
  if (tiempoActual - tiempoAnterior >= 1000) {
    tiempoAnterior = tiempoActual;

    static bool estadoLED = false;

    if (estadoLED) {
      digitalWrite(PIN_LED_ROJO, HIGH);
      estadoLED = false;
    } else {
      digitalWrite(PIN_LED_ROJO, LOW);
      estadoLED = true;
    }
  }
};



